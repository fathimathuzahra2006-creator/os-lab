#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, min, pos;
    int req[100], visited[100] = {0};
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence: %d ", head);

    for(i = 0; i < n; i++) {
        min = 9999;

        for(j = 0; j < n; j++) {
            if(!visited[j] && abs(req[j] - head) < min) {
                min = abs(req[j] - head);
                pos = j;
            }
        }

        visited[pos] = 1;
        total += abs(req[pos] - head);
        head = req[pos];

        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time = %d\n", total);

    return 0;
}