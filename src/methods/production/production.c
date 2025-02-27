#include "../../headers/hello.h"

void production() {
  struct mq_attr attr;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 100;
  attr.mq_flags = 0;
  attr.mq_curmsgs = 0;

  char* mq_name = "/p_c_mq";
  mqd_t mqdes = mq_open(mq_name, O_RDWR | O_CREAT, 0777, &attr);

  if (mqdes == (mqd_t)-1) {
    perror("mq_open");
    exit(EXIT_FAILURE);
  }

  char read_buffer[100];
  struct timespec time_info;

  while (1) {
    clock_gettime(0, &time_info);
    time_info.tv_sec += 15;

    if (mq_timedreceive(mqdes, read_buffer, 100, NULL, &time_info) == -1)
      perror("mq_timedreceive");

    if (read_buffer[0] == EOF) {
      printf("EOF received\n");
      break;
    }

    printf("%s\n", read_buffer);
  }

  close(mqdes);

  mq_unlink(mq_name);
}
