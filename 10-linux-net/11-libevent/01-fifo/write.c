/**
 * @file write.c
 * @author your name (you@domain.com)
 * @brief 
 * 未决： 有资格被处理，但尚未被处理
 * 非未决：没有资格被处理
 * @version 0.1
 * @date 2024-01-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<pthread.h>
#include<event2/event.h>
#include<sys/stat.h>

void sys_err(int flag, char* message) {
  if (flag) {
    perror(message);
    exit(-1);
  }
}

void write_cb(evutil_socket_t fd, short what, void *arg) {
  char buf[] = "hello world";
  write(fd, buf, strlen(buf)+1);
  sleep(1);
  return;
}

int main(int argc, char const *argv[])
{
  // 打开fifo的读端
  int fd = open("test_fifo", O_WRONLY | O_NONBLOCK);
  sys_err(fd == -1, "open error");

  // 创建event_base
  struct event_base *base = event_base_new();
  
  // 创建事件
  // struct event *event_new(struct event_base *base, evutil_socket_t fd, short what, event_callback, void *arg) callback参数
  struct event *ev = event_new(base, fd, EV_WRITE | EV_PERSIST, write_cb, NULL);

  // 添加事件到event_base上
  // int event_add(struct event *ev, const struct timeval *tv)
  event_add(ev, NULL);

  // 启动循环
  // int event_base_dispatch(struct event_base * base);
  event_base_dispatch(base);

  // 销毁
  event_base_free(base);
  return 0;
}