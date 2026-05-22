// systime.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main()
{
    time_t t;

    t = time(NULL);

    printf("Current System Time: %s", ctime(&t));

    // Delay so process exists for a short time
    sleep(5);

    return 0;
}