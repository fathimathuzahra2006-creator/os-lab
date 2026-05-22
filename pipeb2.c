#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

    int fd[2];
    pid_t pid;

    int a, b, c;
    int result;

    printf("Enter values of a, b and c: ");
    scanf("%d %d %d", &a, &b, &c);

    pipe(fd);

    pid = fork();

    if (pid == 0) {

        // Child process

        close(fd[0]);

        result = (b * b) - (4 * a * c);

        write(fd[1], &result, sizeof(result));

        close(fd[1]);
    }

    else {

        // Parent process

        wait(NULL);

        close(fd[1]);

        read(fd[0], &result, sizeof(result));

        printf("Value of b^2 - 4ac = %d\n", result);

        close(fd[0]);
    }

    return 0;
}