#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100

int pageFrames[MAX_PAGES], pageFrameSize, referenceString[MAX_PAGES], referenceStringLength;

void initializePageFrames() {
    for (int i = 0; i < pageFrameSize; i++) pageFrames[i] = -1;
}

void displayPageFrames() {
    printf("Page Frames: ");
    for (int i = 0; i < pageFrameSize; i++)
        printf(pageFrames[i] == -1 ? "[ ] " : "[%d] ", pageFrames[i]);
    printf("\n");
}

bool isPageInFrames(int page) {
    for (int i = 0; i < pageFrameSize; i++)
        if (pageFrames[i] == page) return true;
    return false;
}

void performFIFO() {
    int pageFaults = 0, rear = -1;

    for (int i = 0; i < referenceStringLength; i++) {
        int currentPage = referenceString[i];

        if (!isPageInFrames(currentPage)) {
            pageFaults++;
            rear = (rear + 1) % pageFrameSize;
            pageFrames[rear] = currentPage;
            displayPageFrames();
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    printf("Enter the number of page frames: ");
    scanf("%d", &pageFrameSize);

    initializePageFrames();

    printf("Enter the length of the reference string: ");
    scanf("%d", &referenceStringLength);

    printf("Enter the reference string:\n");
    for (int i = 0; i < referenceStringLength; i++) scanf("%d", &referenceString[i]);

    performFIFO();

    return 0;
}
