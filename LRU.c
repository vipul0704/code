#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100

int pageFrames[MAX_PAGES], pageFrameSize, referenceString[MAX_PAGES], referenceStringLength, pageLastUsed[MAX_PAGES];

void initialize() {
    for (int i = 0; i < pageFrameSize; i++) pageFrames[i] = -1, pageLastUsed[i] = 0;
}

void display() {
    printf("Page Frames: ");
    for (int i = 0; i < pageFrameSize; i++)
        printf(pageFrames[i] == -1 ? "[ ] " : "[%d] ", pageFrames[i]);
    printf("\n");
}

bool inFrames(int page) {
    for (int i = 0; i < pageFrameSize; i++)
        if (pageFrames[i] == page) return true;
    return false;
}

int findLRU() {
    int minIndex = 0;
    for (int i = 1; i < pageFrameSize; i++)
        if (pageLastUsed[i] < pageLastUsed[minIndex]) minIndex = i;
    return minIndex;
}

void performLRU() {
    int pageFaults = 0;

    for (int i = 0; i < referenceStringLength; i++) {
        int currentPage = referenceString[i];

        if (!inFrames(currentPage)) {
            pageFaults++;
            pageFrames[findLRU()] = currentPage;
        }

        for (int j = 0; j < pageFrameSize; j++)
            if (pageFrames[j] != -1) pageLastUsed[j]++;

        pageLastUsed[findLRU()] = 0;
        display();
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    printf("Enter the number of page frames: ");
    scanf("%d", &pageFrameSize);

    initialize();

    printf("Enter the length of the reference string: ");
    scanf("%d", &referenceStringLength);

    printf("Enter the reference string:\n");
    for (int i = 0; i < referenceStringLength; i++) scanf("%d", &referenceString[i]);

    performLRU();

    return 0;
}
