/**
 * @file 14-semphore.c
 * @author your name (you@domain.com)
 * @brief 信号量模型
 * 注意 mac上编写时 逻辑和Linux不一样，macox上实现函数和linux不一样 详细看如下
 * https://stackoverflow.com/questions/4136181/program-using-semaphores-runs-fine-on-linux-unexpected-results-on-mac-osx
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
void sys_err(int flag, char *message, int ret)
{
  if (flag) {
    fprintf(stderr, "%s:%s\n", message, strerror(ret));
    pthread_exit(NULL);
  }
}

#define NUM 5
int queue[NUM];
sem_t blank_number, product_num; // 空格子信号量 产品信号量

void* produce(void *arg)
{
  int i = 0;
  while(1) {
    sem_wait(&blank_number); // 生产者将空格数--，为0则阻塞ç 4
    queue[i] = rand() % 100 + 1;
    printf("----produce %d  -------------index: %d\n", queue[i], i);
    i = (i+1) % NUM;
    sem_post(&product_num); // 产品数++ 1

    sleep(rand() % 3);
  }
}

void* consumer(void *arg)
{
  int i = 0;
  while(1) {
    sem_wait(&product_num); // 消费者将产品数--，为0则阻塞 
    printf(">> index %d ------- consumer: %d\n", i, queue[i]);
    queue[i] = 0; //产品消费完置0
    i = (i+1) % NUM;
    sem_post(&blank_number); // 空产品数++

    sleep(rand() % 3);
  }
}

int main(int argc, char const *argv[])
{
  pthread_t pid, cid;
  /*第二个参数为0时 表示线程间共享 为1时表示线程和进程间共享*/ 
  /*第三个参数 是多少信号量*/ 
  int ret = sem_init(&blank_number, 0, NUM);
  sys_err(ret !=0, "init blank error", ret);
  sem_init(&product_num, 0, 0);
  sys_err(ret !=0, "init product error", ret);

  pthread_create(&pid, NULL, produce, NULL);
  pthread_create(&cid, NULL, consumer, NULL);

  pthread_join(pid, NULL);
  pthread_join(cid, NULL);

  sem_destroy(&blank_number);
  sem_destroy(&product_num);

  return 0;
}
