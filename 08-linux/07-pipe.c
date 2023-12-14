/**
 * @file 07-pipe.c
 * @author sofency (you@domain.com)
 * @brief 数据在管道中只能单向流动，且数据不能重复读
 * 允许存在多个写端 一个读端 只能用于父子进程，兄弟进程间通信
 * @version 0.1
 * @date 2023-12-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

void sys_err(int flag, const char* message)
{
  if(flag) {
    perror(message);
    exit(1);
  }
}

int send_message_by_pipe(char const *argv[])
{
  int fd[2];
  int ret = pipe(fd);
  char buffer[1024];
  char message[1024];
  sprintf(message, "%s,%s","错误是:", strerror(errno));
  sys_err(ret == -1, message);
  pid_t pid = fork();
  if (pid == 0) {
    printf("child pid %d start success, start read message to pipe\n", getpid());
    close(fd[1]); /*关闭管道的写*/
    int lenghth = 0;
    while((lenghth = read(fd[0], buffer, 1024)) > 0) {
      write(STDOUT_FILENO, buffer, lenghth);
    }
    
    write(STDOUT_FILENO, "\n", 1); /* 写个换行符 */
    close(fd[0]);
    printf("child stop success\n");
    exit(EXIT_SUCCESS);
  } else if (pid > 0) {
    printf("parent pid is running\n");
    close(fd[0]);          /* Close unused read end */
    write(fd[1], argv[1], strlen(argv[1]));
    close(fd[1]);          /* Reader will see EOF */
    wait(NULL);                /* Wait for child */
    printf("parent stop success\n");
    exit(EXIT_SUCCESS);
  }
  return 0;
}

void exec_commane_by_pipe()
{
  int fd[2];
  int ret = pipe(fd);
  char message[1024];
  sprintf(message, "%s,%s","错误是:", strerror(errno));
  sys_err(ret == -1, message);
  pid_t pid = fork();
  if (pid == 0) { /*父进程执行wc 子进程执行ls*/
    printf("parent pid \n");
    close(fd[0]); /* 停止读 */
    dup2(fd[1], STDOUT_FILENO); /*得到的结果输出到fd[1]描述的文件中*/
    execlp("ls", "ls", "-la", NULL);
    // wait(NULL); /* 等待子进程执行完毕 */
  } else if (pid > 0) {
    printf("child pid\n");
    close(fd[1]); /*关闭写*/
    dup2(fd[0], STDIN_FILENO); /*从fd[0]中读数据*/
    execlp("wc", "wc", "-l", NULL);
  }
}

void pipe_brother()
{
  int fd[2];
  int ret = pipe(fd);
  sys_err(ret == -1, "open pipe error");

  int i;
  pid_t pid;
  for (i = 0; i < 2; i++) {
    if((pid = fork())==0) {
      break;
    }
  }
  if (i == 2) {
    printf("I'm father\n");
    close(fd[0]);
    close(fd[1]);
    wait(NULL); /*等待两个子进程关闭*/
    wait(NULL);
  } else if (i == 0) {
    
    printf("xiongdi send message\n"); /*负责发送数据*/
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    execlp("ls", "ls", "-la", NULL);
  } else if (i==1) {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    execlp("wc", "wc", "-l", NULL);
  }
}

void pipe_multi_write_and_one_read()
{
  pid_t pid;
  int fd[2];
  int ret = pipe(fd);
  int i;
  sys_err(ret == -1, "create pipe error");
  for (i = 0; i< 2; i++) {
    if ((pid = fork()) == 0) {
      break;
    }
  }
  switch (i)
  {
  case 0:
    close(fd[0]);
    char buf[32];
    sprintf(buf, "hello from %d\n", 0);
    write(fd[1], buf, strlen(buf));
    close(fd[1]);
    break;
  case 1:
    close(fd[0]);
    char buf1[32];
    sprintf(buf1, "hello from %d\n", 2);
    write(fd[1], buf1, strlen(buf1));
    close(fd[1]);
    break;
  case 2:
    close(fd[1]);
    int lenghth;
    sleep(3);
    char buf2[64];
    while((lenghth = read(fd[0], buf2, 64)) > 0) {
      write(STDOUT_FILENO, buf2, lenghth);
    }
    int k;
    for(k = 0; k<2; k++) {
      wait(NULL);
    }
    break;
  default:
    break;
  }
}

/**
 * @brief 创建fifo文件 fifo文件不受父子进程的显示  可以在不同的进程间进行通信
 * 
 */
void make_fifo_file()
{
  int ret = mkfifo("fifo_file", 0644);
  sys_err(ret==-1, "make fifo error");
}
// 写操作
void write_fifo()
{
  int fd, i;
  char buffer[1024];
  fd = open("fifo_file", O_WRONLY);
  sys_err(fd<0, "open error");
  for (i = 0; i<5; i++) {
    sprintf(buffer, "hello from %d", i);
    write(fd, buffer, strlen(buffer));
    sleep(3);
  }
  close(fd);
}

void read_fifo()
{
  int length, i;
  char buffer[1024];
  while ((length = read("fifo_file", O_RDONLY, 1024)) > 0) {
    write(STDOUT_FILENO, buffer, length);
  }
}


int main(int argc, char const *argv[])
{

}