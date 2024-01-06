#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<event2/event.h>
#include<errno.h>
#include<stdlib.h>

void sys_err(int flag, char* message) {
  if (flag) {
    perror(message);
    exit(-1);
  }
}

int main(int argc, char const *argv[])
{
  int i;
  const char * buf;
  struct event_base *base = event_base_new();
  buf = event_base_get_method(base);
  printf("%s\n", buf);
  return 0;
}
