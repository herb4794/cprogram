#include "../headers/hello.h"

void mq_open_method() {
  struct mq_attr attr;
  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 100;
  attr.mq_curmsgs = 0;

  char *mq_name = "/father_son_mq";

  mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0777, &attr);

  if (mqdes == (mqd_t)-1) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    char read_buffer[100];
    struct timespec time_info;
    for (size_t i = 0; i < 10; i++) {
      memset(read_buffer, 0, 100);
      clock_gettime(0, &time_info);
      time_info.tv_sec += 15;
      if (mq_timedreceive(mqdes, read_buffer, 100, 0, &time_info) == -1) {
        perror("mq_timedreceive");
      }
      printf("son process have received message: %s\n", read_buffer);
    }
  } else {
    char send_buffer[100];
    struct timespec time_info;

    for (size_t i = 0; i < 10; i++) {
      memset(send_buffer, 0, 100);
      sprintf(send_buffer, "father process No. %ld\n", (i + 1));
      clock_gettime(0, &time_info);
      time_info.tv_sec += 5;
      if (mq_timedsend(mqdes, send_buffer, 100, 0, &time_info) == -1) {
        perror("mq_timedsend");
      }
      printf("father process have send one message then sleep 1 second\n");
      sleep(2);
    }
  }

  close(mqdes);

  if (pid > 0) {
    mq_unlink(mq_name);
  }
}
