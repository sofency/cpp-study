/**
 * @file 03-multiple-process.c
 * @author your name (you@domain.com)
 * @brief 多进程服务器-服务端代码
 * @version 0.1
 * @date 2023-12-27
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
#include<pthread.h>

#define THREAD_PORT 9257
struct thread_info {
  int cfd;
  struct sockaddr_in client;
};

void sys_err(int flag, const char* message) {
  if(flag) {
    perror(message);
    exit(1);
  }
}

void sys_err_thread(int flag, char *message, int ret)
{
  if(flag) {
    fprintf(stderr, message, strerror(ret));
    exit(1);
  }
}

/**
 * @brief 线程内的任务
 * 
 * @param args 
 * @return void* 
 */
void* do_work(void * args) {

  struct thread_info *info = (struct thread_info*) args;

  char buf[1024], ip[INET_ADDRSTRLEN];
  int i;
  while(1) {
    int length = read(info->cfd, buf, sizeof(buf));

    if (length <= 0) {
      printf("the connect side has broken \n");
      break;
    }
    printf("receive message from client ip:port  %s:%d\n", inet_ntop(AF_INET, &info->client.sin_addr, ip, sizeof(ip)), ntohs(info->client.sin_port));
    for (i = 0; i< length; i++) {
        buf[i] = toupper(buf[i]);
    }
    write(STDOUT_FILENO, buf, length);
    write(info->cfd, buf, length);
  }
  close(info->cfd);
  return (void *)0;
}

int main(int argc, char const *argv[])
{
  int ret;
  pid_t pid;
  pthread_t tid;

  int sfd = socket(AF_INET, SOCK_STREAM, 0); /*创建socket流*/
  sys_err(sfd==-1, "create socket error");

  struct sockaddr_in sock, client;
  bzero(&sock, sizeof(sock));
  sock.sin_family = AF_INET;
  sock.sin_port = htons(THREAD_PORT);
  sock.sin_addr.s_addr = htonl(INADDR_ANY);

  /*绑定端口和ip信息*/
  ret = bind(sfd, (struct sockaddr*)&sock, sizeof(sock));
  sys_err(ret == -1, "bind error");

  /*主要设置listen的个数*/
  ret = listen(sfd, 128);
  sys_err(ret == -1, "listen error");
  struct thread_info info[128];
  int i = 0;
    
  while(1) {
    socklen_t client_len = sizeof(client);
    printf("accepting...\n");
    int cfd = accept(sfd, (struct sockaddr*)&client, &client_len);
    sys_err(cfd==-1, "accept error");
    printf("accept ..... %d\n", cfd);
    info[i].cfd = cfd;
    info[i].client = client;

    ret = pthread_create(&tid, NULL, do_work, (void*)&info[i]);
    sys_err_thread(ret==-1, "create thread error", ret);
    pthread_detach(tid);
    i++;
  }
  return 0;
}

