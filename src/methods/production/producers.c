#include "../../headers/hello.h"

void producers() {
  struct mq_attr attr;

  struct timespec time_info;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_curmsgs = 0;
  attr.mq_msgsize = 100;

  char *mq_name = "/p_c_mq";

  mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0777, &attr);

  if (mqdes == (mqd_t)-1) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  char write_buffer[100];
  while (1) {
    memset(write_buffer, 0, 100);
    ssize_t read_count = read(STDIN_FILENO, write_buffer, 100);
    clock_gettime(0, &time_info);
    time_info.tv_sec += 5;
    if (read_count == -1) {
      perror("read:");
      continue;

    } else if (read_count == 0) {
      printf("EOF, exit...\n");
      char eof = EOF;
      if (mq_timedsend(mqdes, &eof, 1, 0, &time_info) == -1) {
        perror("mq_timedsend");
      }
      break;
    }

    if (mq_timedsend(mqdes, write_buffer, strlen(write_buffer), 0,
                     &time_info) == -1) {
      perror("mq_timedsend");
    }
    printf("Take data in command line already send to message on data list\n");
  }

  close(mqdes);

  // mq_unlink(mq_name);
}
