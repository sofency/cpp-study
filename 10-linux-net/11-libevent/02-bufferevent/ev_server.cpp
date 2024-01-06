#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// 读缓冲区回调
void read_cb(struct bufferevent* bev, void* arg) {
  char buf[1024] = {0};
  bufferevent_read(bev, buf, sizeof(buf));
  printf("client say: %s\n", buf);

  char* p = "我是服务器, 已经成功收到你发送的数据!";
  // 发数据给客户端 +1是因为要加上'\0'
  bufferevent_write(bev, p, strlen(p) + 1);
  sleep(1);
}

// 写缓冲区回调
void write_cb(struct bufferevent* bev, void* arg) {
  printf("I'm服务器, 成功写数据给客户端,写缓冲区回调函数被回调...\n");
}

// 事件
void event_cb(struct bufferevent* bev, short events, void* arg) {
  if (events & BEV_EVENT_EOF) {
    printf("connection closed\n");
  } else if (events & BEV_EVENT_ERROR) {
    printf("some other error\n");
  }

  bufferevent_free(bev);
  printf("buffevent 资源已经被释放...\n");
}

// 客户端建立连接后的回调
void cb_listener(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* addr, int len, void* ptr) {
  printf("connect new client\n");

  // bind函数中的参数 传进来
  struct event_base* base = (struct event_base*)ptr;
  // 通信操作
  // 添加新事件
  struct bufferevent* bev;
  bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

  // 给bufferevent缓冲区设置回调 bev也是 read_cb 和其他两个函数的参数
  bufferevent_setcb(bev, read_cb, write_cb, event_cb, NULL);
  bufferevent_enable(bev, EV_READ);
}
/**
 * @brief
 * 1. 创建event基座
 * 2. 创建监听器 evconnlistener_new_bind 监听客户端连接
 *    2.1 有客户端进来 创建socket 处理对应的事件
 *    2.2 设置当前的回调事件 读写
 * 3. event_base_dispatch 基座
 * 4. 释放监听器 evconnlistener_free
 * 5. 释放事件基座
 *
 * @param argc
 * @param argv
 * @return int
 */

int main(int argc, const char* argv[]) {
  // init server
  struct sockaddr_in serv;

  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(9876);
  serv.sin_addr.s_addr = htonl(INADDR_ANY);

  struct event_base* base;
  base = event_base_new();
  // 创建套接字
  // 绑定
  // 接收连接请求
  // 36 就是listen函数第二个参数 即最大连接数
  struct evconnlistener* listener;
  listener = evconnlistener_new_bind(base, cb_listener, base, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, 36,
                                     (struct sockaddr*)&serv, sizeof(serv));

  event_base_dispatch(base);

  evconnlistener_free(listener);
  event_base_free(base);

  return 0;
}
