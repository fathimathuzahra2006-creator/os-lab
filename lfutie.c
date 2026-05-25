#include <stdio.h>

int main()
{
    int pages[50], frames[10], freq[10], time[10];
    int n, f, i, j;
    int page_faults = 0;
    int found, min, pos;
    int counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for(i = 0; i < f; i++)
    {
        frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    for(i = 0; i < n; i++)
    {
        found = 0;

        // Check if page already exists
        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                freq[j]++;
                found = 1;
                break;
            }
        }

        // Page Fault
        if(found == 0)
        {
            min = freq[0];
            pos = 0;

            // Find LFU page
            // If tie occurs, use FIFO
            for(j = 1; j < f; j++)
            {
                if(freq[j] < min)
                {
                    min = freq[j];
                    pos = j;
                }
                else if(freq[j] == min)
                {
                    if(time[j] < time[pos])
                    {
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            freq[pos] = 1;
            time[pos] = counter++;

            page_faults++;

            printf("\nPage Fault: ");

            for(j = 0; j < f; j++)
            {
                if(frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
        }
    }

    printf("\n\nTotal Page Faults = %d\n", page_faults);

    return 0;
}