// system_info.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main()
{
    FILE *fp;
    char line[256];

    int cpu_cores = 0;
    long mem_total = 0, mem_free = 0;
    int running = 0, blocked = 0;
    long total_processes = 0;

    // -------------------------------
    // (a) Number of CPU cores
    // -------------------------------
    fp = fopen("/proc/cpuinfo", "r");

    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "processor", 9) == 0)
            cpu_cores++;
    }

    fclose(fp);

    printf("Number of CPU Cores : %d\n\n", cpu_cores);

    // -------------------------------
    // (b) Total and Free Memory
    // -------------------------------
    fp = fopen("/proc/meminfo", "r");

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "MemTotal: %ld kB", &mem_total);
        sscanf(line, "MemFree: %ld kB", &mem_free);
    }

    fclose(fp);

    printf("Total Memory : %ld kB\n", mem_total);
    printf("Free Memory  : %ld kB\n", mem_free);

    printf("Fraction of Free Memory : %.2f\n\n",
           (float)mem_free / mem_total);

    // -------------------------------
    // (c), (d), (e)
    // -------------------------------
    fp = fopen("/proc/stat", "r");

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "procs_running %d", &running);
        sscanf(line, "procs_blocked %d", &blocked);
        sscanf(line, "processes %ld", &total_processes);
    }

    fclose(fp);

    // Count current processes
    DIR *dir;
    struct dirent *entry;
    int current_processes = 0;

    dir = opendir("/proc");

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] >= '0' &&
            entry->d_name[0] <= '9')
        {
            current_processes++;
        }
    }

    closedir(dir);

    printf("Currently Running Processes : %d\n\n",
           current_processes);

    printf("Processes in Running State : %d\n",
           running);

    printf("Processes in Blocked State : %d\n\n",
           blocked);

    printf("Processes Forked Since Boot : %ld\n\n",
           total_processes);

    // -------------------------------
    // (f) Context Switches
    // -------------------------------
    int pid;

    printf("Enter PID to check context switches: ");
    scanf("%d", &pid);

    char path[100];

    sprintf(path, "/proc/%d/status", pid);

    fp = fopen(path, "r");

    if (fp == NULL)
    {
        printf("Invalid PID\n");
        return 1;
    }

    int voluntary = 0, nonvoluntary = 0;

    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line,
               "voluntary_ctxt_switches: %d",
               &voluntary);

        sscanf(line,
               "nonvoluntary_ctxt_switches: %d",
               &nonvoluntary);
    }

    fclose(fp);

    printf("\nVoluntary Context Switches     : %d\n",
           voluntary);

    printf("Nonvoluntary Context Switches  : %d\n",
           nonvoluntary);

    printf("Total Context Switches         : %d\n",
           voluntary + nonvoluntary);

    return 0;
}