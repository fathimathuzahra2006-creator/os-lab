#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message {
    long type;
    char text[100];
};

int isPalindrome(char str[]) {
    int i, j;
    int len = strlen(str);

    for (i = 0, j = len - 1; i < j; i++, j--) {
        if (str[i] != str[j])
            return 0;
    }

    return 1;
}

int main() {

    int msgid;
    pid_t pid;

    struct message msg;

    key_t key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    pid = fork();

    if (pid == 0) {

        // Child process

        msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);

        printf("Received string: %s\n", msg.text);

        if (isPalindrome(msg.text))
            printf("It is a Palindrome\n");
        else
            printf("It is Not a Palindrome\n");
    }

    else {

        // Parent process

        msg.type = 1;

        printf("Enter a string: ");
        scanf("%s", msg.text);

        msgsnd(msgid, &msg, sizeof(msg.text), 0);

        wait(NULL);

        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}