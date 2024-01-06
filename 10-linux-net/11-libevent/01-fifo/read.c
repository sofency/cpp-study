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

void read_cb(evutil_socket_t fd, short what, void *arg) {
  char buf[1024];
  int len = read(fd, buf, sizeof(buf));
  printf("what = %s, read from write %s \n", what & EV_READ ? "read satisfy":" read not", buf);
  sleep(1);
  return;
}

int main(int argc, char const *argv[])
{
  /* code */
  unlink("test_fifo");
  mkfifo("test_fifo", 0644);

  // 打开fifo的读端
  int fd = open("test_fifo", O_RDONLY | O_NONBLOCK);
  sys_err(fd == -1, "open error");

  // 创建event_base
  struct event_base *base = event_base_new();
  
  // 创建事件
  // struct event *event_new(struct event_base *base, evutil_socket_t fd, short what, event_callback, void *arg) callback参数
  struct event *ev = event_new(base, fd, EV_READ | EV_PERSIST, read_cb, NULL);

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
