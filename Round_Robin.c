#include <stdio.h>

#define MAX_PROCESSES 10

void findTimes(int n, int bt[], int wt[], int tat[], int quantum) {
    int remaining_time[MAX_PROCESSES] = {0};

    for (int time = 0, done = 0; done != 1;) {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0;

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    wt[i] = time - bt[i];
                    remaining_time[i] = 0;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void displayTimes(int n, int bt[], int wt[], int tat[]) {
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\nAverage Waiting Time: %f\n", avgWT);
    printf("Average Turnaround Time: %f\n", avgTAT);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    int burst_time[MAX_PROCESSES], waiting_time[MAX_PROCESSES], turnaround_time[MAX_PROCESSES];

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    findTimes(n, burst_time, waiting_time, turnaround_time, quantum);
    displayTimes(n, burst_time, waiting_time, turnaround_time);

    return 0;
}
