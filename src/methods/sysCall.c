#include "../headers/hello.h"

inline void systemOpenFile(struct router *of) {
  int fd = open(of->path, O_RDWR | O_CREAT, 0777);
  if (fd == -1) {
    printf("Error: Could not open file %s\n", of->path);
    exit(EXIT_FAILURE);
    of->fd = fd;
  } else {
    printf("File %s opened successfully\n", of->path);
    of->fd = fd;
  }
}

inline void systemReadFile(struct router *of) {
  ssize_t bytes_read;
  while ((bytes_read = read(of->fd, of->buffer, sizeof(of->buffer))) > 0) {
    write(STDOUT_FILENO, of->buffer, bytes_read);
  }

  if (bytes_read == -1) {
    perror("read");
    close(of->fd);
    exit(EXIT_FAILURE);
  }
  close(of->fd);
}

inline void forkFd(struct router *of) {
  if (of->fd == -1) {
    perror("Error: Could not open file \n");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) {
    strcpy(of->buffer, "Child process\n");
  } else {
    sleep(1);
    strcpy(of->buffer, "Parent process\n");
  }

  ssize_t bytes_write = write(of->fd, of->buffer, strlen(of->buffer));


  if (bytes_write == -1) {
    perror("write");
    close(of->fd);
    exit(EXIT_FAILURE);
  }

  printf("File  written to sucessfully\n");

  close(of->fd);

  if (pid == 0) {
    printf("Child process completed release file flas\n");
  } else {
    printf("Parent process completed release file flas\n");
  }
}
