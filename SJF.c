//Xavier Santiago
//CS470
//11/15/2025
//Honor Code: "I pledge that this submission is solely my work, and that I have neither given to nor received help from anyone other than the instructor or TA’s."
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int idx = -1;
    int min_remaining = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (proc[i].arrival_time <= current_time && !proc[i].is_completed &&
            proc[i].remaining_time < min_remaining && proc[i].remaining_time > 0) {
            min_remaining = proc[i].remaining_time;
            idx = i;
        }
    }
    return idx;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int completed = 0, current_time = 0;
    int execution_order[100], eo_index = 0;

    // Initialize remaining times and completion flags
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_completed = 0;
    }

    // Main scheduling loop
    while (completed < n) {
        int idx = findNextProcess(proc, current_time);
        if (idx != -1) {
            proc[idx].remaining_time--;
            execution_order[eo_index++] = proc[idx].process_id;

            if (proc[idx].remaining_time == 0) {
                proc[idx].is_completed = 1;
                completed++;
                proc[idx].turnaround_time = current_time + 1 - proc[idx].arrival_time;
                proc[idx].waiting_time = proc[idx].turnaround_time - proc[idx].burst_time;
            }
        }
        current_time++;
    }

    // Print execution order
    printf("\nExecution Order: ");
    for (int i = 0; i < eo_index; i++) {
        printf("P%d ", execution_order[i]);
    }
    printf("\n");
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;

}
