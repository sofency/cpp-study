#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
// 只在linux有用
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>
#include<sys/stat.h>

#define MAX_LENGTH 10

void sys_err(int flag, const char* message) {
  if (flag) {
    perror(message);
    exit(1);
  }
}

void write_info(char *ch, int fd, char * buf) {
  int i;
  for (i = 0; i < MAX_LENGTH / 2; i++) {
    buf[i] = ch;
  }
  buf[i-1] = '\n';
  ch ++;
  for (; i < MAX_LENGTH ; i++) {
    buf[i] = ch;
  }
  buf[i-1] = '\n';

  write(fd, buf, sizeof(buf));
  sleep(5);
}
int main(int argc, char const *argv[])
{
  // 创建管道 0为读端 1为写端
  int fd[2];
  int res = pipe(fd);
  char message[64];
  char buf[1024];
  sprintf(message, "%s,%s","错误是:", strerror(errno));
  sys_err(ret == -1, message);
  char ch = 'a';

  // 创建子进程进程id
  pid_t pid = fork();
  if (pid == 0) {
    // 处理子进程业务
    close(fd[0]);
    while(1) {
      write_info(&ch, fd[1], buf);
    }
    close(fd[1]);
  } else if (pid > 0) {
    // 处理父进程业务
    struct epoll_event event, ready[10];
    close(fd[1]);
    int efd = epoll_create(10);
    // epoll 的ET模式，高效模式，但是只支持非阻塞模式
    // event.events = EPOLLIN | EPOLLET; // ET边沿触发 缓冲区剩余未读尽的数据不会导致epoll_wait返回 新的事件满足才会触发
    // event.data.fd = fd[0];
    // epoll_ctl(efd, EPOLL_CTL_ADD, fd[0], &event);
    // int flag = fcntl(fd[0], F_GETFL);
    // flg |= O_NONBLOCK;
    // fcntl(fd[0], F_SETFL, flg);

    event.events = EPOLLIN; // LT边缘触发 缓冲区未读尽的数据 会导致epoll_wait返回
    event.data.fd = fd[0];

    epoll_ctl(efd, EPOLL_CTL_ADD, fd[0], &event);

    while(1) {
      // 等待准备好的事件响应
      int res = epoll_wait(efd, ready, 10, -1);
      if (ready[0].data.id == fd[0]) {
        // 上述一次性写了10个字符 aaaa\nbbbb\n 这次读的话 仅5个一批次读 对于LT模式来说 缓冲区未读尽的数据epoll_wait可以返回
        int len = read(fd[0], buf, MAX_LENGTH / 2);
        write(STDOUT_FILENO, buf, len);
      }
      close(fd[0]);
      close(efd);
    }
  } else {
    perror("pid create error");
    exit(1);
  }
  return 0;
}
