#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid;
    pid = fork();   // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) executing myadder...\n", getpid());

        // Arguments for myadder
        char *args[] = {"./myadder", "10", "20", NULL};

        // Replace current process with myadder
        execvp(args[0], args);

        // execvp returns only if it fails
        perror("execvp failed");
        exit(1);
    } 
    else {
        // Parent process
        printf("Parent process (PID: %d) created child (PID: %d)\n", getpid(), pid);
        wait(NULL);  // Wait for child to finish
        printf("Child completed execution.\n");
    }

    return 0;
}