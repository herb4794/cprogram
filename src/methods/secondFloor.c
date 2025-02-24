#include "../headers/hello.h"

int lifeCycle(int argc, char *argv[]) {

  if (argc < 2) {
    printf("Perameter is missing cannot proceed \n");
    return 1;
  }

  printf("It's %s number %d", argv[1], getpid());

  return 0;
}

int singleProcess(int argc, char *argv[]) {
  struct router mRouter;
  char *name = "lawrence";

  printf("I'am %s and my process id is %d\n", name, getpid());

  char *args[] = {"/home/lawrence/Desktop/CProgrammer/singlePro", name, NULL};
  char *envs[] = {"PATH=/bin", NULL};

  int result = execve(args[0], envs, NULL);

  if (result == -1) {
    perror("Error:");
    return 1;
  }

  return 0;
}
