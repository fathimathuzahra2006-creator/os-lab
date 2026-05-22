#include <stdio.h>

int main()
{
    int pages[50], frames[10], time[10];
    int n, f, i, j;
    int page_faults = 0, found;
    int counter = 0, pos, min;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");

    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;

                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            min = time[0];
            pos = 0;

            for(j = 1; j < f; j++)
            {
                if(time[j] < min)
                {
                    min = time[j];
                    pos = j;
                }
            }

            counter++;

            frames[pos] = pages[i];
            time[pos] = counter;

            page_faults++;

            printf("\nPage Fault: ");

            for(j = 0; j < f; j++)
                printf("%d ", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n",
           page_faults);

    return 0;
}