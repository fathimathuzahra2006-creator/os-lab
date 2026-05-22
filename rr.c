#include <stdio.h>

int main()
{
    int n, tq;
    int bt[20], rembt[20];
    int wt[20], tat[20];

    int time = 0, completed;

    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Burst Time for P%d: ", i + 1);

        scanf("%d", &bt[i]);

        rembt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    while(1)
    {
        completed = 1;

        for(int i = 0; i < n; i++)
        {
            if(rembt[i] > 0)
            {
                completed = 0;

                if(rembt[i] > tq)
                {
                    time += tq;
                    rembt[i] -= tq;
                }
                else
                {
                    time += rembt[i];

                    wt[i] = time - bt[i];

                    rembt[i] = 0;

                    tat[i] = wt[i] + bt[i];
                }
            }
        }

        if(completed == 1)
            break;
    }

    printf("\nPID\tBT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               i + 1,
               bt[i],
               wt[i],
               tat[i]);

        avgwt += wt[i];
        avgtat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f",
           avgwt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avgtat / n);

    return 0;
}