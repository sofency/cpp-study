/**
 * @file 12-mutex.c
 * @author your name (you@domain.com)
 * @brief 
 * 读写锁: 读共享 写独占 写锁优先级高 即同时来两个读请求一个写请求 则写操作会抢到 
 * @version 0.1
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

// 定义锁
pthread_mutex_t mutex;

void * execute(void * arg) 
{
  intptr_t i = (intptr_t) arg;
  int k = 1;
  if (i == 0) {
    do {
      pthread_mutex_lock(&mutex);
      printf("num %d hello ", k);
      k++;
      sleep(rand() % 3);
      printf("world \n");
      pthread_mutex_unlock(&mutex);
      sleep(rand() % 1);
    } while(k < 10);
  } else {
   do {
      pthread_mutex_lock(&mutex);
      printf("NUM %d HELLO ", k);
      k++;
      sleep(rand() % 3);
      printf("WORLD \n");
      pthread_mutex_unlock(&mutex);
      sleep(rand() % 1);
    }while(k < 10);
  }
}

/**
 * @brief 互斥锁
 * 
 */
void mutex_lock()
{
  int i;
  pthread_t tid[2];
  // 初始化互斥锁
  pthread_mutex_init(&mutex, NULL);
  srand(time(NULL));
  for (i = 0; i< 2; i++) {
    pthread_create(&(tid[i]), NULL, execute, (void *)i);
  }
  for (i = 0; i< 2; i++) {
    pthread_join(tid[i], NULL);
  }
  // 销毁互斥锁
  pthread_mutex_destroy(&mutex);
}

/**
 * @brief 读写锁
 * 
 */
// 定义读写锁
pthread_rwlock_t rwlock;
int money = 100;

void *read_info(void *arg)
{
  /* 获取坐标*/
  intptr_t i = (intptr_t) arg;
  int k = 1;
  do {
    pthread_rwlock_rdlock(&rwlock);
    printf("num %ld read money: %d\n", i, money);
    k++;
    usleep(1000);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  } while(k < 10);
  return NULL;
}

void *write_info(void *arg)
{
  /*获取坐标*/ 
  intptr_t i = (intptr_t) arg;
  int k = 1;
  do {
    pthread_rwlock_wrlock(&rwlock);
    money += 10;
    printf("---num %ld write money %d -----------------\n", i, money);
    k++;
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  } while(k < 10);
  return NULL;
}

void read_write_lock()
{
  int i;
  pthread_t tid[8];
  //不进行初始化操作 在mac平台会出现线程不安全现象 
  pthread_rwlock_init(&rwlock, NULL);  

  for (i = 0; i< 3; i++) {
    pthread_create(&(tid[i]), NULL, write_info, (void *)i);
  }
  for (i = 0; i< 5; i++) {
    pthread_create(&(tid[i+3]), NULL, read_info, (void *)(i+3));
  }

  /*阻塞等待*/ 
  for(i=0; i<8; i++) {
    pthread_join(tid[i], NULL);
  }

  /*销毁读写锁*/ 
  pthread_rwlock_destroy(&rwlock);
}

int main(int argc, char const *argv[])
{
  return 0;
}
