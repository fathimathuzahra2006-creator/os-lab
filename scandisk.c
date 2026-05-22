#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int req[100], n, head, disk_size, i;
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for(i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    sort(req, n);

    int index;
    for(i = 0; i < n; i++) {
        if(req[i] > head) {
            index = i;
            break;
        }
    }

    printf("\nSeek Sequence: %d ", head);

    for(i = index; i < n; i++) {
        total += abs(req[i] - head);
        head = req[i];
        printf("-> %d ", head);
    }

    total += abs((disk_size - 1) - head);
    head = disk_size - 1;

    for(i = index - 1; i >= 0; i--) {
        total += abs(req[i] - head);
        head = req[i];
        printf("-> %d ", head);
    }

    printf("\nTotal Seek Time = %d\n", total);

    return 0;
}