#include <stdio.h>

struct Process
{
    int pid, at, bt, wt, tat;
};

int main()
{
    int n, time = 0;
    float avgwt = 0, avgtat = 0;

    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    p[0].wt = 0;
    time = p[0].bt;

    for(int i = 1; i < n; i++)
    {
        p[i].wt = time - p[i].at;

        if(p[i].wt < 0)
            p[i].wt = 0;

        time += p[i].bt;

        p[i].tat = p[i].wt + p[i].bt;
    }

    p[0].tat = p[0].bt;

    printf("\nPID\tAT\tBT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].wt,
               p[i].tat);

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f",
           avgwt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avgtat / n);

    return 0;
}