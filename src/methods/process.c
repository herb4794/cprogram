#include "../headers/hello.h"

// NOTE:
//  fork is a system call that is used to create a new process called child
//  process. The child process is an exact copy of the parent process except for
//  the process id
void processView(struct router *of) {
  int result = system(of->command);

  if (result != 0) {
    perror("Error:");
    exit(EXIT_FAILURE);
  }
}

void getProcessId(struct router *of) {
  printf("Process ID: %d\n", getpid());

  pid_t pid = fork();

  printf("sub Process ID %d\n ", pid);

  if (pid < 0) {
    perror("Error:");
  } else if (pid == 0) {
    printf("child process %d and parent process %d\n", getpid(), getppid());
  } else {
    printf("parent process %d and child process %d\n", getpid(), pid);
  }
}
