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
  int ret,i;
  char buf[1024], ip[1024];
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  sys_err(fd==-1, "create socket error");

  // 重定义 传入的参数
  struct sockaddr_in address, client_addr;
  address.sin_family = AF_INET;
  address.sin_port = htons(SERVER_PORT);
  address.sin_addr.s_addr = htonl(INADDR_ANY);

  ret = bind(fd, (struct sockaddr *)&address, sizeof(address));
  sys_err(ret==-1, "bind error");
  ret = listen(fd, 128);
  sys_err(ret==-1, "listen error");
  socklen_t client_addr_len = sizeof(client_addr);
  int connect_fd = accept(fd, (struct sockaddr *)&client_addr, &client_addr_len);
  sys_err(connect_fd == -1, "accept error");

  printf("client info: ip %s, port:%d\n", 
          inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip, sizeof(ip)), 
          ntohs(client_addr.sin_port)  // 将网络端口号转换为本地端口号
  );

  int length = read(connect_fd, buf, sizeof(buf));
  write(STDOUT_FILENO, buf, length);


  for (i=0; i<length; i++) {
    buf[i]=toupper(buf[i]);
  }
  /*write back*/
  write(connect_fd, buf, length);

  close(connect_fd);
  close(fd);
  return 0;
}