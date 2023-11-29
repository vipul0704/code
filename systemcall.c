#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    pid_t child_pid;
    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        // This code is executed by the child process

        // Display a message from the child process
        printf("Child process (PID=%d): I am the child!\n", getpid());

        // Execute a new program using exec
        execlp("ls", "ls", "-l", NULL);

        // If exec fails, the following code will be executed
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // This code is executed by the parent process

        // Display a message from the parent process
        printf("Parent process (PID=%d): I am the parent!\n", getpid());

        // Wait for the child process to complete
        wait(NULL);

        // Display a message after the child process completes
        printf("Parent process: Child process completed.\n");
    }
    return 0;
}
