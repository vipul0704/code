#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100

int pageFrames[MAX_PAGES], pageFrameSize, referenceString[MAX_PAGES], referenceStringLength;

void initialize() {
    for (int i = 0; i < pageFrameSize; i++) pageFrames[i] = -1;
}

void display() {
    printf("Page Frames: ");
    for (int i = 0; i < pageFrameSize; i++)
        printf(pageFrames[i] == -1 ? "[ ] " : "[%d] ", pageFrames[i]);
    printf("\n");
}

bool inFrames(int page, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++)
        if (pageFrames[i] == page) return true;
    return false;
}

int findOptimal(int currentIndex) {
    int farthestIndex = currentIndex;
    int farthestPage = -1;

    for (int i = 0; i < pageFrameSize; i++) {
        int nextPage = pageFrames[i];
        int nextIndex = currentIndex;

        while (nextIndex < referenceStringLength && referenceString[nextIndex] != nextPage)
            nextIndex++;

        if (nextIndex > farthestIndex) {
            farthestIndex = nextIndex;
            farthestPage = i;
        }
    }

    return farthestPage;
}

void performOptimal() {
    int pageFaults = 0;

    for (int i = 0; i < referenceStringLength; i++) {
        int currentPage = referenceString[i];

        if (!inFrames(currentPage, 0, pageFrameSize)) {
            pageFaults++;
            pageFrames[findOptimal(i)] = currentPage;
            display();
        }
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

    performOptimal();

    return 0;
}
