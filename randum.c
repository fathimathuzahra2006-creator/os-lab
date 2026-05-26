#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int frames[MAX_FRAMES];
int faults = 0;

/* Initialize frames */
void initializeFrames(int f) {
    for (int i = 0; i < f; i++)
        frames[i] = -1;
}

/* Check if page exists */
int findPage(int page, int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

/* Generate random frame index */
int getRandomFrame(int f) {
    return rand() % f;
}

/* Display frame table */
void displayTable(int page, int f, int hit) {
    printf("%d\t", page);
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("-\t");
        else
            printf("%d\t", frames[i]);
    }
    printf("%s\n", hit ? "Hit" : "Fault");
}

int main() {
    int pages[MAX_PAGES];
    int n, f;

    srand(time(NULL));  // Seed random generator

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    initializeFrames(f);

    /* Print table header */
    printf("\nPage\t");
    for (int i = 0; i < f; i++)
        printf("Frame%d\t", i + 1);
    printf("Status\n");

    /* Simulation */
    for (int i = 0; i < n; i++) {
        int pos = findPage(pages[i], f);

        if (pos != -1) {
            displayTable(pages[i], f, 1);
        } else {
            int replaceIndex = -1;

            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1)
                replaceIndex = getRandomFrame(f);

            frames[replaceIndex] = pages[i];
            faults++;

            displayTable(pages[i], f, 0);
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}
