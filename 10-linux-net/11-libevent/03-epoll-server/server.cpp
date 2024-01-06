#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <unistd.h>
#include "wrap.h"

#define OPEN_MAX 5000

void sys_err(int flag, const char* message) {
  if (flag) {
    perror(message);
    exit(1);
  }
}

/*获取一行 \r\n 结尾的数据*/
int get_line(int cfd, char* buf, int size) {
  int i = 0;
  char c = '\0';
  int n;
  while ((i < size - 1) && (c != '\n')) {
    /*每次只读一个字符*/
    n = recv(cfd, &c, 1, 0);
    if (n > 0) {
      if (c == '\r') {
        n = recv(cfd, &c, 1, MSG_PEEK);
        if ((n > 0) && (c == '\n')) {
          recv(cfd, &c, 1, 0);
        } else {
          c = '\n';
        }
      }
      buf[i] = c;
      i++;
    } else {
      c = '\n';
    }
  }
  buf[i] = '\0';

  if (-1 == n)
    i = n;

  return i;
}

int init_listen_fd(int port, int efd) {
  int res, i;
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  sys_err(fd == -1, "socket error");

  struct sockaddr_in server, client;

  /*初始化server*/
  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  res = bind(fd, (struct sockaddr*)&server, sizeof(server));
  sys_err(res == -1, "bind error");

  res = listen(fd, 32);
  sys_err(res == -1, "listen error");

  struct epoll_event tep;
  /*事件 EPOLLIN EPOLLOUT EPOLLERR*/
  tep.events = EPOLLIN;
  tep.data.fd = fd;  // 指定lfd的监听时间为"读"

  res = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &tep);  // 将fd及对应的结构体设置到树上,efd可找到该树
  sys_err(res == -1, "epoll_ctl error");

  return fd;
}

/**
 * @brief sockfd节点从根结点删除
 *
 * @param efd
 * @param sockfd
 */
void disconnect(int efd, int sockfd) {
  int res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  // 将该文件描述符从红黑树摘除
  sys_err(res == -1, "epoll_ctl error");
  res = close(sockfd);  // 关闭与该客户端的链接
  sys_err(res == -1, "close error");
}

void send_respond(int cfd, int no, char* disp, char* type, int len) {
  char buf[4096] = {0};

  sprintf(buf, "HTTP/1.1 %d %s\r\n", no, disp);
  send(cfd, buf, strlen(buf), 0);

  sprintf(buf, "Content-Type: %s\r\n", type);
  sprintf(buf + strlen(buf), "Content-Length:%d\r\n", len);
  send(cfd, buf, strlen(buf), 0);

  send(cfd, "\r\n", 2, 0);  // 发送最后的一行
}

/*发送服务器本地文件 给浏览器*/
void send_file(int cfd, const char* file) {
  int n = 0, ret;
  char buf[4096] = {0};

  /*打开的服务器本地文件。  --- cfd 能访问客户端的 socket*/
  int fd = open(file, O_RDONLY);
  sys_err(fd == -1, "open error");

  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    ret = send(cfd, buf, n, 0);
    if (ret == -1) {
      printf("errno = %d\n", errno);
      if (errno == EAGAIN || errno == EINTR) {
        printf("errno %s\n", errno == EAGAIN ? "EAGAIN" : "EINTR");
        continue;
      } else {
        sys_err(1, "send error");
      }
    }

    if (ret < 4096)
      printf("-----send ret: %d\n", ret);
  }

  close(fd);
}

void handle_request(int sockfd, char* file) {
  struct stat file_state;
  int ret = stat(file, &file_state);
  sys_err(ret == -1, "error");
  if (S_ISREG(file_state.st_mode)) {
    /*回发http协议*/
    // send_respond(sockfd, 200, "OK", "Content-Type: text/plain; charset=iso-8859-1", file_state.st_size);
    // send_respond(cfd, 200, "OK", "audio/mpeg", -1); 发视频 存在问题
    send_respond(sockfd, 200, "OK", "Content-Type:image/jpeg", -1);

    send_file(sockfd, file);
  }
}

/**
 * @brief 处理 accept请求  并将请求到的数据放置到根节点中
 *
 * @param lfd
 */
void do_accept(int efd, int lfd) {
  struct sockaddr_in client;
  char ip[INET_ADDRSTRLEN];
  socklen_t client_length = sizeof(client);

  int connfd = Accept(lfd, (struct sockaddr*)&client, &client_length);  // 接受链接

  printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &client.sin_addr, ip, sizeof(ip)), ntohs(client.sin_port));

  struct epoll_event tep;
  tep.events = EPOLLIN;
  tep.data.fd = connfd;
  int res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);  // 加入红黑树
  sys_err(res == -1, "epoll_ctl error");
}

/**
 * @brief 从浏览器读取数据
 *
 * @param efd
 * @param event
 */
void do_read(int efd, struct epoll_event event) {
  int sockfd = event.data.fd;
  char line[1024];
  char method[16], path[256], protocol[16];
  int res;

  int len = get_line(sockfd, line, sizeof(line));

  if (len == 0) {  // 读到0,说明客户端关闭链接
    printf("client[%d] closed connection\n", sockfd);
    disconnect(efd, sockfd);
  } else {
    /*处理浏览器逻辑*/
    sscanf(line, "%[^ ] %[^ ]  %[^ ]", method, path, protocol);
    printf("method: %s path:%s protocol:%s\n", method, path, protocol);
    while (1) {
      char buf[1024];
      len = get_line(sockfd, buf, sizeof(buf));
      printf("current len %d, message: %s\n", len, buf);
      if (len == -1) {
        printf("i am breaking\n");
        break;
      } else if (len == 0) {
        printf("client disconnect\n");
        break;
      } else if (buf[0] == '\n') {
        printf("current is space\n");
        break;
      }
    }
    if (strncasecmp(method, "GET", 3) == 0) {
      char* file = path + 1;
      handle_request(sockfd, file);
      disconnect(efd, sockfd);
    }
  }
}

void epoll_run(int port) {
  int i;
  struct epoll_event tep, ep[OPEN_MAX];  // tep: epoll_ctl参数  ep[] : epoll_wait参数

  int efd = epoll_create(OPEN_MAX);
  sys_err(efd == -1, "error epoll create");

  /*添加lfd节点到epoll树上*/
  ssize_t nready;
  int lfd = init_listen_fd(port, efd);

  while (1) {
    /*等待事件响应*/
    nready = epoll_wait(efd, ep, OPEN_MAX, -1);
    sys_err(nready == -1, "wait error");
    for (i = 0; i < nready; i++) {
      if (!(ep[i].events & EPOLLIN))  // 如果不是"读"事件, 继续循环
        continue;

      if (ep[i].data.fd == lfd) {
        do_accept(efd, lfd);
      } else {
        do_read(efd, ep[i]);
      }
    }
  }
}

int main(int argc, char const* argv[]) {
  if (argc < 3) {
    printf("please input like this: ./server port path\n");
    exit(1);
  }
  int port = atoi(argv[1]);
  int ret = chdir(argv[2]);
  sys_err(ret == -1, "chdir error");
  epoll_run(port);
  return 0;
}
