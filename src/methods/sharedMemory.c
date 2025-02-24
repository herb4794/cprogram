#include "../headers/hello.h"

void shmOpen() {
  // NOTE: craete shared memory object
  char* share;
  char shm_name[1024] = {0};
  int fd;
  sprintf(shm_name, "/letter%d", getgid());
  fd = shm_open(shm_name, O_RDWR | O_CREAT, 0777);
  if (fd < 0) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }
  // NOTE: set the size of the shared memory object
  ftruncate(fd, 1024);

  // TODO: map the shared memory object
  share = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (share == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }
  close(fd);

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork ");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    strcpy(share, "Hello, I am a child process\n");
    printf("child process write to shared memory\n");
  } else {
    waitpid(pid, NULL, 0);
    printf("parent process%d read from %d share memory: %s", getpid(), pid,
           share);
    int result = munmap(share, 1024);
    if (result == -1) {
      perror("munmap");
      exit(EXIT_FAILURE);
    }
  }

  // NOTE: release the shared memory object
  shm_unlink(shm_name);
};
