#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
  int fd = open("pid.ps", O_RDWR | O_CREAT | O_TRUNC, 0644);
  // 将标准输出的文件描述符赋值给文件描述符
  dup2(fd, STDOUT_FILENO);
  // execlp("ps", "ps", "aux", NULL);
  char * argv[] = {"ls", "la", NULL};
  execvp("ls", argv);
  perror("ps error");
  return 0;
}
