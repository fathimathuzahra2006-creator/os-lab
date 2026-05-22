#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isPresent(int frames[], int frameCount, int page) {
    for (int i = 0; i < frameCount; i++)
        if (frames[i] == page)
            return i;
    return -1;
}

int fifo(int ref[], int n, int frameCount) {
    int frames[frameCount], front = 0, faults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (isPresent(frames, frameCount, ref[i]) == -1) {
            frames[front] = ref[i];
            front = (front + 1) % frameCount;
            faults++;
        }
    }

    return faults;
}

int lru(int ref[], int n, int frameCount) {
    int frames[frameCount], lastUsed[frameCount], faults = 0, time = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        time++;
        int pos = isPresent(frames, frameCount, ref[i]);

        if (pos != -1) {
            lastUsed[pos] = time;
        } else {
            int replace = -1;

            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            if (replace == -1) {
                replace = 0;
                for (int j = 1; j < frameCount; j++) {
                    if (lastUsed[j] < lastUsed[replace])
                        replace = j;
                }
            }

            frames[replace] = ref[i];
            lastUsed[replace] = time;
            faults++;
        }
    }

    return faults;
}

int optimal(int ref[], int n, int frameCount) {
    int frames[frameCount], faults = 0;

    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (isPresent(frames, frameCount, ref[i]) != -1)
            continue;

        int replace = -1;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == -1) {
                replace = j;
                break;
            }
        }

        if (replace == -1) {
            int farthest = -1;

            for (int j = 0; j < frameCount; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == ref[k])
                        break;
                }

                if (k == n) {
                    replace = j;
                    break;
                }

                if (k > farthest) {
                    farthest = k;
                    replace = j;
                }
            }
        }

        frames[replace] = ref[i];
        faults++;
    }

    return faults;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <reference-string-length> <number-of-frames>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int frameCount = atoi(argv[2]);

    if (n <= 0 || frameCount < 1 || frameCount > 7) {
        printf("Reference string length must be > 0 and frames must be from 1 to 7.\n");
        return 1;
    }

    int ref[n];

    srand(time(NULL));

    printf("Page Reference String:\n");
    for (int i = 0; i < n; i++) {
        ref[i] = rand() % 10;
        printf("%d ", ref[i]);
    }

    printf("\n\nNumber of Frames: %d\n", frameCount);
    printf("FIFO Page Faults:    %d\n", fifo(ref, n, frameCount));
    printf("LRU Page Faults:     %d\n", lru(ref, n, frameCount));
    printf("Optimal Page Faults: %d\n", optimal(ref, n, frameCount));

    return 0;
}