#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 200


int main() {

    int shmid;
    char *str;

    key_t key = ftok("shmfile", 65);

    shmid = shmget(key, SIZE, 0666 | IPC_CREAT);

    str = (char *)shmat(shmid, NULL, 0);

    pid_t pid = fork();

    if (pid > 0) {

        // Parent process

        char s1[100], s2[100];

        printf("Enter first string: ");
        scanf("%s", s1);

        printf("Enter second string: ");
        scanf("%s", s2);

        strcat(s1, s2);

        strcpy(str, s1);

        wait(NULL);

        printf("Final string after case flipping: %s\n", str);

        shmdt(str);

        shmctl(shmid, IPC_RMID, NULL);
    }

    else {

        // Child process

        sleep(1);

        for (int i = 0; str[i] != '\0'; i++) {

            if (islower(str[i]))
                str[i] = toupper(str[i]);

            else if (isupper(str[i]))
                str[i] = tolower(str[i]);
        }

        shmdt(str);
    }

    return 0;
}