/**
 * @file 13-cond.c
 * @author your name (you@domain.com)
 * @brief 条件变量
 * 
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
#include<errno.h>
#include<pthread.h>


void sys_err(int flag, char *message, int ret)
{
  if (flag) {
    fprintf(stderr, "%s:%s\n", message, strerror(ret));
    pthread_exit(NULL);
  }
}
struct message 
{
  struct message *next;
  int num;
};

struct message *head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 定义初始化互斥量
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER; // 定义初始化信号量

void* producer(void* arg)
{
  int k = 1;
  do {
    pthread_mutex_lock(&mutex);
    struct message *temp = (struct message *)malloc(sizeof(struct message));
    temp->num = rand() % 1000 + 1;
    temp->next = head;
    head = temp;
    printf("----------num %d producer data %d\n", k, temp->num);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&has_data);
    sleep(rand() % 3);
    k++;
  } while(k < 10);
  return NULL;
}

void* consumer(void* arg)
{
  int k = 1;
  do{
    pthread_mutex_lock(&mutex);
    struct message *temp;
    while (head == NULL) {
      // 阻塞等待
      printf(".....\n");
      pthread_cond_wait(&has_data, &mutex); // 阻塞会丢掉锁 所以判断head==NULL使用while循环
    }
    temp = head;
    head = head->next;
    printf("num %d consumer data %d\n", k, temp->num);

    free(temp);
    pthread_mutex_unlock(&mutex);
    sleep(rand() % 3);
    k++;
  } while(k < 10);
  return NULL;
}

int main(int argc, char const *argv[])
{
  int ret;
  pthread_t pid, cid;
  srand(time(NULL));
  ret = pthread_create(&pid, NULL, producer, NULL);
  sys_err(ret != 0, "create producer error", ret);

  ret = pthread_create(&cid, NULL, consumer, NULL);
  sys_err(ret != 0, "create consumer error", ret);

  pthread_join(pid, NULL);
  pthread_join(cid, NULL);

  pthread_mutex_destroy(&mutex);
  return 0;
}
