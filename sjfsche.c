#include <stdio.h>

struct Process
{
    int pid, bt, wt, tat;
};

int main()
{
    int n, time = 0;
    float avgwt = 0, avgtat = 0;

    struct Process p[20], temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(p[i].bt > p[j].bt)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wt = 0;

    for(int i = 1; i < n; i++)
    {
        p[i].wt = p[i - 1].wt +
                  p[i - 1].bt;
    }

    for(int i = 0; i < n; i++)
    {
        p[i].tat = p[i].wt + p[i].bt;

        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    printf("\nPID\tBT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].bt,
               p[i].wt,
               p[i].tat);
    }

    printf("\nAverage Waiting Time = %.2f",
           avgwt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           avgtat / n);

    return 0;
}