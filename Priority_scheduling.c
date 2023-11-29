#include <stdio.h>

void findTimes(int n, int bt[], int priority[], int wt[], int tat[]) {
    wt[0] = 0;
    tat[0] = bt[0];

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
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

void priorityScheduling(int n, int bt[], int priority[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (priority[j] > priority[j + 1]) {
                int temp = bt[j], prioTemp = priority[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                priority[j] = priority[j + 1];
                priority[j + 1] = prioTemp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], priority[n], waiting_time[n], turnaround_time[n];

    printf("Enter burst times and priorities for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);

        printf("Priority for process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    priorityScheduling(n, burst_time, priority);
    findTimes(n, burst_time, priority, waiting_time, turnaround_time);
    displayTimes(n, burst_time, waiting_time, turnaround_time);

    return 0;
}
