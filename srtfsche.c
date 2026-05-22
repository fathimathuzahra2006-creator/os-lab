#include <stdio.h>

struct Process
{
    int pid, at, bt, wt, tat, rt;
};

int main()
{
    int n, complete = 0, time = 0;
    int min = 9999, shortest = 0;
    int finish_time, check = 0;

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

        p[i].rt = p[i].bt;
    }

    while(complete != n)
    {
        for(int j = 0; j < n; j++)
        {
            if((p[j].at <= time) &&
               (p[j].rt < min) &&
               p[j].rt > 0)
            {
                min = p[j].rt;
                shortest = j;
                check = 1;
            }
        }

        if(check == 0)
        {
            time++;
            continue;
        }

        p[shortest].rt--;

        min = p[shortest].rt;

        if(min == 0)
            min = 9999;

        if(p[shortest].rt == 0)
        {
            complete++;
            check = 0;

            finish_time = time + 1;

            p[shortest].wt =
                finish_time -
                p[shortest].bt -
                p[shortest].at;

            if(p[shortest].wt < 0)
                p[shortest].wt = 0;

            p[shortest].tat =
                p[shortest].bt +
                p[shortest].wt;
        }

        time++;
    }

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