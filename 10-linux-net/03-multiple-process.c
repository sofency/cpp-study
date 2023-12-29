/**
 * @file 03-multiple-process.c
 * @author your name (you@domain.com)
 * @brief 多进程服务器-服务端代码
 * @version 0.1
 * @date 2023-12-27
 * shutdown 在关闭多个文件描述符引用的文件时，采用全关闭方法。close是关闭一个
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<errno.h>
#include<signal.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<ctype.h>

#define PORT 9257

void sys_err(int flag, const char* message) {
  if(flag) {
    perror(message);
    exit(1);
  }
}

void do_action(int num){
  while(waitpid(0, NULL, WNOHANG) > 0);
}

int main(int argc, char const *argv[])
{
  int ret;
  pid_t pid;
  int sfd = socket(AF_INET, SOCK_STREAM, 0); /*创建socket流*/
  sys_err(sfd==-1, "create socket error");

  struct sigaction action;
  
  /*信号检测回收子进程资源*/
  action.sa_handler = do_action;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGCHLD, &action, NULL);

  /*允许本地地址复用，即进程结束后不用等待2MSL*/
  int opt = 1;
  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(opt));

  struct sockaddr_in sock, client;
  bzero(&sock, sizeof(sock));
  sock.sin_family = AF_INET;
  sock.sin_port = htons(PORT);
  sock.sin_addr.s_addr = htonl(INADDR_ANY);

  /*绑定端口和ip信息*/
  ret = bind(sfd, (struct sockaddr*)&sock, sizeof(sock));
  sys_err(ret == -1, "bind error");

  /*主要设置listen的个数*/
  ret = listen(sfd, 128);
  sys_err(ret == -1, "listen error");

  while(1) {
    socklen_t client_len = sizeof(client);
    printf("enter...\n");
    int cfd = accept(sfd, (struct sockaddr*)&client, &client_len);
    sys_err(cfd==-1, "accept error");
    printf("accept ..... %d\n", cfd);
    pid = fork();

    if (pid > 0) {
      close(cfd);
      printf("exit parent pid\n");
    } else if (pid == 0) {
      close(sfd); /* 父进程关闭通信*/

      while(1) {
        char buf[1024], ip[INET_ADDRSTRLEN];
        int length = read(cfd, buf, sizeof(buf));
        int i;

        if (length <= 0) {
          printf("the connect side has broken \n");
          break;
        }
        printf("receive message length %d from client ip:port  %s:%d\n", length, inet_ntop(AF_INET, &client.sin_addr, ip, sizeof(ip)), ntohs(client.sin_port));
        for (i = 0; i< length; i++) {
           buf[i] = toupper(buf[i]);
        }
        write(STDOUT_FILENO, buf, length);
        write(cfd, buf, length);
      }
      close(cfd);
      return 0;
    } else {
      sys_err(1, "fork child error");
    }
  }
  return 0;
}

