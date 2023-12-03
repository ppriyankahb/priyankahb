#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_strings>\n", argv[0]);
        return 1;
    }

    int numStrings = atoi(argv[1]);
    const int SHM_SIZE = 2048; // 2k segment size
    const char *shmName = "/shared_memory";

    int shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    char *shm = (char *)shmat(shmid, NULL, 0);
    if (shm == NULL) {
        perror("shmat");
        return 1;
    }

    printf("Enter %d strings (each separated by Enter):\n", numStrings);
    for (int i = 0; i < numStrings; ++i) {
        fgets(shm + (i * 100), 100, stdin);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process capitalizes the first character of each string
        for (int i = 0; i < numStrings; ++i) {
            shm[i * 100] = toupper(shm[i * 100]);
        }
        exit(0);
    } else {
        wait(NULL); // Wait for the child process to complete

        printf("Strings after capitalization:\n");
        for (int i = 0; i < numStrings; ++i) {
            printf("%s", shm + (i * 100));
        }

        // Detach and remove shared memory segment
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}