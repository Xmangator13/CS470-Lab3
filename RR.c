//Xavier Santiago
//CS470
//11/15/2025
//Honor Code: "I pledge that this submission is solely my work, and that I have neither given to nor received help from anyone other than the instructor or TA’s."
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;

//Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    int time = 0, completed = 0;
    int execution_order[100], eo_index = 0;

    //Initialize remaining times
    for (int i = 0; i < n; i++)
        proc[i].remaining_time = proc[i].burst_time;

    //Main Round Robin loop
    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= time) {
                done = 0;
                //Determine execution time for this quantum
                int exec_time = (proc[i].remaining_time > quantum) ? quantum : proc[i].remaining_time;
                time += exec_time;
                proc[i].remaining_time -= exec_time;
                //Record execution order
                execution_order[eo_index++] = proc[i].process_id;
                //If process completes, calculate turnaround and waiting times
                if (proc[i].remaining_time == 0) {
                    proc[i].turnaround_time = time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                    completed++;
                }
            }
        }
        //idle time if no process is ready
        if (done) time++;
    }

    //Print execution order
    printf("\nExecution Order: ");
    for (int i = 0; i < eo_index; i++) {
        printf("P%d ", execution_order[i]);
    }
    printf("\n");
}


//Wrapper function for Round Robin scheduling
void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
}

//Function to print process details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    //Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); //Number of processes
    int quantum = 4; //Time quantum for Round Robin scheduling

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;

}


