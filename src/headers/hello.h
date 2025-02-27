#ifndef __HELLO_H__

#define __HELLO_H__
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct router {
  char *path;
  char buffer[1024];
  int fd;
  char *command;
};

struct openFile {
  char *filename;
  FILE *file;
};

void openFiles(struct openFile *of);
void inputFile(struct openFile *of);
void closeFile(struct openFile *of);
void inputFileS(struct openFile *of);
void inputLongContent(struct openFile *of);
void getFileContentC(struct openFile *of);
void getFileContentS(struct openFile *of);
void fscanfFile(struct openFile *of);
void stdinOutErr(struct openFile *of);
void systemOpenFile(struct router *of);
void systemReadFile(struct router *of);
void processView(struct router *of);
void getProcessId(struct router *of);
void forkFd(struct router *of);
int lifeCycle(int argc, char *argv[]);
int singleProcess(int argc, char *argv[]);
void makefifoRead();
void makefifoWrite();
void shmOpen();
void mq_open_method();
void producers();
void production();
#endif  // !__HELLO_H__
