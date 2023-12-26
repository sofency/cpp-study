#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>

#define SERVER_PORT 9527


void sys_err(int flag, const char* message)
{
  if(flag)
  {
    perror(message);
    exit(1);
  }
}

int main(int argc, char const *argv[])
{
  int cfd, count=10;
  char buf[1024];
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr);

  cfd = socket(AF_INET, SOCK_STREAM, 0);
  sys_err(cfd==-1, "socket error");

  int ret = connect(cfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  sys_err(ret!=0, "connect error");

  while(--count){
    write(cfd, "hello world", 11);
    read(cfd, buf, sizeof(buf));
  }

  close(cfd);
  return 0;
}
