/**
 * @file 06-orphan-process.c
 * @author your name (you@domain.com)
 * @brief 僵尸进程和孤儿进程
 * 孤儿进程: 子进程还未执行结束，父亲就挂了, 此时父进程称为init进程
 * 僵尸进程: 子进程全都执行完毕了，但是父进程迟迟不挂，导致无法回收子进程内存资源 无法kill 可以杀死父进程
 * @version 0.1
 * @date 2023-12-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/wait.h>
#include<stdlib.h>

/**
 * @brief 孤儿进程例子
 * ps ajx 可以显示出子进程的父进程是谁
 */
void orphan() {
  pid_t pid = fork();
  if (pid == -1) {
    perror("创建子进程失败");
    exit(1);
  } else if(pid == 0) {
    while (1) {
      printf("child pid is runing \n");
      sleep(1);
    }
  } else {
    printf("parent pid is running to die\n");
    sleep(1);
  }
}
//回收子进程 获取子进程异常退出信号
void wait_process()
{
  pid_t pid = fork();
  int status;
  if (pid == 0){
    printf("child pid %d, go to sleep 5s\n", getpid());
    sleep(5);
    printf("child to die\n");
    return 73;
  } else if (pid > 0) {
    // 等着将子进程回收掉 并且 传入参数接收从子进程收到的状态值
    // 如果子进程未终止，父进程阻塞
    // pid_t wpid = wait(NULL); 不关心子进程退出原因
    pid_t wpid = wait(&status);
    if (wpid == -1) {
      perror("wait error");
      exit(1);
    }
    // 如果为真，说明子进程正常终止
    if (WIFEXITED(status)) { 
      printf("child pid %d exit with %d\n", getpid(), WEXITSTATUS(status));
    }
    // 如果为真说明 子进程是信号中断
    if (WIFSIGNALED(status)) { 
      printf("child pid %d exit with signal %d\n", pid, WTERMSIG(status));
    }
    printf("parent pid finish %d\n", getpid());
  }
}

int main(int argc, char const *argv[])
{
  wait_process();
  return 0;
}
