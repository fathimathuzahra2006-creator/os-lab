#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
    }

    else if (pid == 0) {
        // Child process
        printf("PCCSL407 ");
    }

    else {
        // Parent process waits for child
        wait(NULL);

        printf("Operating Systems Lab");
    }

    return 0;
}