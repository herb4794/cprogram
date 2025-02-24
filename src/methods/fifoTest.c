#include "../headers/hello.h"

// NOTE:
// fifo is a named pipe that is used for interprocess communication between
// processes file descriptor is used to read and write data to the pipe file
// pipe is a unidirectional communication channel that is used for interprocess
// communication
void makefifoWrite() {
  int fd;
  char* pipe_path = "/tmp/myfifo";

  if (mkfifo(pipe_path, 0777)) {
    perror("mkfifo");
    if (errno != EEXIST) {
      exit(EXIT_FAILURE);
    }
  }

  fd = open(pipe_path, O_RDWR, 0777);

  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  char buff[1024];
  ssize_t read_num;
  // NOTE: Read from stdin and write to fifo
  while ((read_num = read(STDIN_FILENO, buff, sizeof(buff))) > 0) {
    write(fd, buff, read_num);
  }

  if (read_num < 0) {
    perror("write");
    close(fd);
    exit(EXIT_FAILURE);
  }

  printf("send message to fifo complete\n");
  close(fd);
  // NOTE: release the pipe
  if (unlink(pipe_path)) {
    perror("unlink");
  }
};

void makefifoRead() {
  int fd;
  char* pipe_path = "/tmp/myfifo";

  // if (mkfifo(pipe_path, 0777) != 0) {
  //   perror("mkfifo");
  //   exit(EXIT_FAILURE);
  // }

  fd = open(pipe_path, O_RDONLY, 0777);

  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  char buff[1024];
  ssize_t read_num;
  // NOTE: Read from stdin and write to fifo
  while ((read_num = read(fd, buff, sizeof(buff))) > 0) {
    write(STDOUT_FILENO, buff, read_num);
  }

  if (read_num < 0) {
    perror("read ");
    close(fd);
    exit(EXIT_FAILURE);
  }

  printf("result message to fifo complete\n");
  close(fd);
};
