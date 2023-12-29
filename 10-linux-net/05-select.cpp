/**
 * @file 05-select.c
 * @author your name (you@domain.com)
 * @brief 多路I/O复用操作
 * @version 0.1
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "common.h"

#define SERVER_PORT 9999

struct action_list {
  int length;
  int action[1024];  // 最多存储多少个
};

void sys_err(int flag, const char* message) {
  if (flag) {
    perror(message);
    exit(1);
  }
}

int main(int argc, char const* argv[]) {
  /*记录函数返回值*/
  int ret, i, j;
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  sys_err(listenfd == -1, "socket error");

  /*设置可重用地址*/
  int opt = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  /*绑定协议族*/
  struct sockaddr_in server, client;
  socklen_t client_len;

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(SERVER_PORT);
  ret = bind(listenfd, (struct sockaddr*)&server, sizeof(server));
  sys_err(ret == -1, "bind error");

  /* 监听文件描述符结果 */
  ret = listen(listenfd, 128);
  sys_err(ret == -1, "listen error");

  char ip[INET_ADDRSTRLEN];
  int maxfd = listenfd;
  fd_set rset, allset;  // 定义读集合 以及备份集合
  char buf[1024];       // 定义缓冲区
  int length;           // 读取到数据的长度
  int connectfd;        // 连接的fd信息

  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);

  struct action_list actions;
  actions.length = 0;
  memset(actions.action, -1, sizeof(actions.action));  // 初始化所存的文件描述符列表

  while (1) {
    rset = allset;
    /*参数1: 最大文件描述符+1; 参数2: 既传入也传出，监听哪些端口，返回哪些的文件描述符是有多少个文件有事件响应*/
    printf("start select ...\n");
    ret = select(maxfd + 1, &rset, NULL, NULL, NULL);
    sys_err(ret < 0, "select error");
    printf("current ret %d\n", ret);
    /*判断客户端是否有连接请求过来*/
    if (FD_ISSET(listenfd, &rset)) {
      connectfd = accept(listenfd, (struct sockaddr*)&client, &client_len);
      sys_err(connectfd == -1, "accept error");
      printf("receive from %s at port %d", inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof(ip)),
             ntohs(client.sin_port));

      if (actions.length < 1024) {  // 记录连接的connectfd信息到结构体中
        actions.action[actions.length] = connectfd;
        actions.length++;
      } else {
        printf("to many connect clients\n");
        exit(1);
      }

      /*放置到allset中，让select管理事件的响应*/
      FD_SET(connectfd, &allset);
      if (maxfd < connectfd) {
        maxfd = connectfd;
      }
      if (ret == 1) {  // 说明返回的就是listenfd,后续不需要处理
        printf("current connectfd %d\n", connectfd);
        continue;
      }
    }
    printf("start deal message from client\n");
    /*处理后续文件的事件*/
    for (i = 0; i < actions.length; i++) {
      int actionfd = actions.action[i];
      if (FD_ISSET(actionfd, &rset)) {  // 找到满足读事件的fd
        length = read(actionfd, buf, sizeof(buf));
        if (length == 0) {
          close(actionfd);
          FD_CLR(actionfd, &allset);
        } else if (length == -1) {
          sys_err(1, "client error");
        }
        for (j = 0; j < length; j++) {
          buf[j] = toupper(buf[j]);
        }
        write(STDOUT_FILENO, buf, length); /*先在服务器端打印出来看看*/
        write(actionfd, buf, length);
      }
    }
  }

  ret = close(listenfd);
  sys_err(ret == -1, "close listenfd error");
  return 0;
}