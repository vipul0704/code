#include <stdio.h>
void findTimes(int n, int bt[], int wt[], int tat[]) {
    // Calculate waiting time for the first process
    wt[0] = 0;
    // Calculate waiting time for subsequent processes
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
    // Calculate turnaround time for each process
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
    // Calculate average waiting time and average turnaround time
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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burst_time[n], waiting_time[n], turnaround_time[n];
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }
    findTimes(n, burst_time, waiting_time, turnaround_time);
    displayTimes(n, burst_time, waiting_time, turnaround_time);
    return 0;
}