/**
 * @file 11-thread.c
 * @author your name (you@domain.com)
 * @brief 
 * 线程
 *    1. 线程没有单独的地址空间, cpu执行的最小单位
 *    2. 线程共享进程的三级页表 所以没有单独的地址空间
 * 进程:
 *    1. 分配资源的最小单位，有独立的进程地址空间，独立的pcb
 *    2. 
 * 避免在多线程中使用信号机制
 * @version 0.1
 * @date 2023-12-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void sys_err(int flag, const char *message)
{
  if (flag)
  {
    perror(message);
    exit(1);
  }
}

// 设置全局变量 父子线程共享全局变量
int var = 100;
// 线程具体执行的方法
void *tfn(void * arg)
{
  int i = (int) arg;
  if ( i== 3) {
    // 退出当前线程
    pthread_exit(NULL);
  }
  printf("num %d thread pid: %d, tid: %lu, var = %d\n", i++, getpid(), pthread_self(), var);
  return NULL;
}
/**
 * @brief 循环创建多个线程
 * 
 */
void threads()
{
  int i;
  pthread_t tid;
  // 参数传入线程tid,以及线程内部的处理函数
  for (i = 0; i< 5; i++) {
    // 第四个参数要值传递
    int ret = pthread_create(&tid, NULL, tfn, (void *)i);
    sys_err(ret == -1, "pthread_create error");
  }
  printf("main pid: %d, tid: %lu\n", getpid(), pthread_self()); //pthread_self() 获取当前线程id
  sleep(1);
}

struct student
{
  int id;
  char name[64];
};

void * execute(void * arg)
{
  // 如果声明变量 返回局部值的话会报错
  struct student *stu;
  stu = (struct student*)malloc(sizeof(*stu));
  stu->id = 21;
  strcpy(stu->name, "hello world");
  return (void *) stu;
}

void deal_retval()
{
  pthread_t tid;
  struct student stu;
  struct student *retval;
  int ret = pthread_create(&tid, NULL, execute, (void*)&stu);
  sys_err(ret != 0, "create thread error");

  // 默认阻塞回收子线程
  ret = pthread_join(tid, (void **)&retval);
  // ret = pthread_cancel(tid); 终止线程 如果线程出现死循环可以这样终止 
  // 线程内部需要有取消点 如果内部仅有while(1); 这样无法取消循环 我们也可以手动添加取消点 pthread_testcancel
  // 成功被pthread_cancel取消的线程返回-1，
  // 等待线程执行完毕获取线程返回值
  sys_err(ret != 0, "join thread error");
  printf("student id %d, name %s\n", retval->id, retval->name);
  pthread_exit(NULL);
}

void sys_err_thread(int flag, char *message, int ret)
{
  if(flag) {
    fprintf(stderr, message, strerror(ret));
    exit(1);
  }

}
void detach()
{
  pthread_t tid;
  // 创建子线程
  int ret = pthread_create(&tid, NULL, tfn, NULL);
  sys_err_thread(ret != 0, "create thread error: %s\n", ret);
  // 设置线程分离
  ret = pthread_detach(tid);
  sys_err_thread(ret != 0, "detach thread error: %s\n", ret);
  sleep(1);
  // 由于上面已经分离线程，即已经将线程回收处理，tid的资源已经被释放，再次join会失败
}

// 创建线程就指定为分离状态
void set_thread_detached_state()
{
  pthread_t tid;
  pthread_attr_t attr;
  int ret = pthread_attr_init(&attr);
  sys_err_thread(ret != 0, "attr init error %s\n", ret);
  // 设置线程属性为分离属性
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  // 创建子线程
  ret = pthread_create(&tid, &attr, tfn, NULL);
  sys_err_thread(ret != 0, "create thread error: %s\n", ret);
  
  ret = pthread_attr_destroy(&attr);
  sys_err_thread(ret != 0, "destory thread error: %s\n", ret);

  sleep(1);


  // 主要验证上述是否设置成功
  ret = pthread_join(tid, NULL);
  sys_err_thread(ret != 0, "join error: %s\n", ret); // join error: No such process
}

int main(int argc, char const *argv[])
{
  set_thread_detached_state();
  return 0;
}
