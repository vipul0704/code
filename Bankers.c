#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int n, m;
int current[MAX_PROCESSES][MAX_RESOURCES], max_claim[MAX_PROCESSES][MAX_RESOURCES], available[MAX_RESOURCES];
int work[MAX_RESOURCES], finish[MAX_PROCESSES];

void input() {
    printf("Enter processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter max claim matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max_claim[i][j]);

    printf("Enter current allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &current[i][j]);

    printf("Enter available resources: ");
    for (int j = 0; j < m; j++)
        scanf("%d", &available[j]);
}

void calculateNeedMatrix(int need[MAX_PROCESSES][MAX_RESOURCES]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max_claim[i][j] - current[i][j];
}

int isSafe() {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeedMatrix(need);

    for (int j = 0; j < m; j++)
        work[j] = available[j];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    for (int count = 0; count < n;) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m && need[i][j] <= work[j]; j++);

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += current[i][k];

                    finish[i] = 1;
                    found = 1;
                    printf("%d ", i);
                    count++;
                }
            }
        }

        if (found == 0) {
            printf("\nSystem is not in safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in safe state.\n");
    return 1;
}

int main() {
    input();
    isSafe();

    return 0;
}
