/**
 * @file 09-signal.c
 * @author your name (you@domain.com)
 * @brief
 * 与信号相关的事件和状态
 *   1.按键产生 Ctrl+c、Ctrl+z
 *   2.系统调用产生 如kill
 *   3.软件条件产生 如定时器
 *   4.硬件异常产生 非法访问内存（段错误）
 *   5.命令产生 kill
 * 信号的处理方式
 *   1. 执行默认动作
 *   2. 忽略
 *   3. 捕捉 调用户处理函数
 * 未决：产生与递达之间状态
 * 递达：产生并且送达到进程 直接被内核处理掉
 * 阻塞信号集： 本质是位图， 用来记录信号的屏蔽状态，一旦被屏蔽的信号，在解除屏蔽前，一直处于未决态。
 * 未决信号集，本质位图，用来记录信号的处理状态
 *
 * 信号的动作
 *  Term:终止进程
 *  Ign: 忽略信号
 *  Core: 终止进程，生成Core文件
 *  Stop: 停止进程
 *  Cont: 继续运行进程
 *
 * 信号集操作函数
 *  sigset_t set; 自定义信号集
 *  sigemptyset(sigset_t *set); 清空信号集
 *  sigfillset(sigset_t *set); 全部置1
 *  sigaddset(sigset_t *set, int signum); 将一个信号添加到集合中
 *  sigdelset(sigset_t *set, int signum); 将一个信号从集合中移除
 *  sigismember(const sigset_t *set, int signum); 判断一个信号是否在集合中 1在，0不在
 *
 * 设置信号屏蔽字和解除屏蔽
 *   int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
 *        how：SIG_BLOCK 设置阻塞；SIG_UNBLOCK 取消阻塞  SIG_SETMASK 用自定义的set替换mask
 *        set  自定义set
 *        oldset 旧有的mask
 *
 *   int sigpending(sigset_t *set)
 * @version 0.1
 * @date 2023-12-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
void sys_err(int flag, const char *message)
{
  if (flag)
  {
    perror(message);
    exit(1);
  }
}

void send_signal()
{
  pid_t pid = fork();
  if (pid == 0)
  {
    sleep(4);
    /* 发送杀死父进程的信号 */
    printf("child pid %d, parent pid %d\n", getpid(), getppid());
    kill(getppid(), SIGKILL);
  }
  else if (pid > 0)
  {
    while (1)
    {
      /* code */
      sleep(1);
      printf("do something \n");
    }
  }
}
void count()
{
  // 定时发送SIGALRM给当前进程 1s后结束当前进程
  alarm(1);
  int i;
  for (i = 0;; i++)
  {
    printf("%d\n", i);
  }
}

void print(int signo)
{
  printf("hello world\n");
}

void set()
{
  struct itimerval it, oldit;
  /*注册SIGALRM信号的捕捉处理函数，捕捉到信号就进行执行print操作*/
  signal(SIGALRM, print);

  // 第一个闹钟的间隔
  it.it_value.tv_sec = 2;
  it.it_value.tv_usec = 0;

  // 后续每次间隔
  it.it_interval.tv_sec = 5;
  it.it_interval.tv_usec = 0;

  if (setitimer(ITIMER_REAL, &it, &oldit) == -1)
  {
    perror("setitimer error");
    exit(1);
  }

  while (1)
    ;
}

void print_set(sigset_t *set)
{
  int i;
  for (i = 1; i < 32; i++)
  {
    if (sigismember(set, i))
    {
      putchar('1');
    }
    else
    {
      putchar('0');
    }
  }
  putchar('\n');
}

void sig_info()
{
  sigset_t set, oldset, pedset;
  int ret = 0;
  // 将所有的信号位置为0
  sigemptyset(&set);
  // 把信号加到set中 就是将指定位数 置为1
  sigaddset(&set, SIGINT);
  printf("current set info \n");
  print_set(&set);

  // 设置信号屏蔽 将set里面定义的信号集进行屏蔽操作
  ret = sigprocmask(SIG_BLOCK, &set, &oldset);
  sys_err(ret == -1, "sigprocmask error");

  while (1)
  {
    // 读出当前未决信号集
    ret = sigpending(&pedset);
    sys_err(ret == -1, "sigpending error");
    print_set(&pedset);
    sleep(1);
  }
}

void sig_catch(int signo)
{
  if (signo == SIGINT)
  {
    printf("catch you %d \n", signo);
    sleep(10);
  }
  else if (signo == SIGQUIT)
  {
    printf("------------- catch you !! %d \n", signo);
  }
}

/**
 * @brief 信号捕捉函数
 * 1. 进程正常执行，默认PCB中有一个信号屏蔽字，假定为m, 它决定了进程自动屏蔽哪些信号，当注册了某个信号捕捉函数，捕捉到该信号以后
 *    要调用该函数。而该函数有可能执行很长时间，在这期间所屏蔽的信号不由m来指定，而是有sa_mask指定，调用完信号处理函数，再恢复m
 * 2. XXX 信号捕捉函数执行期间，XXX信号自动被屏蔽，即执行Ctrl+c 处理函数期间 sleep(10)秒，那么10s在此收到该信号会被屏蔽
 * 3. 阻塞的常规信号不支持排队，产生多次，只记录一次
 *
 * 信号捕捉特性
 * 1. 捕捉函数执行期间，信号屏蔽字由mask->sa_mask,捕捉函数执行结束，恢复会mask
 * 2. 捕捉函数执行期间，本信号自动被屏蔽
 * 3. 捕捉函数执行期间，被屏蔽信号多次发送，解除屏蔽后只处理一次
 */
void sig_action()
{
  struct sigaction act, oldact;
  act.sa_handler = sig_catch; // 设置回调

  sigemptyset(&(act.sa_mask)); // 初始化屏蔽字 不加则在捕捉函数处理期间 有该信号的话 则直接停止 加上后 捕捉函数执行期间不会停止
  // 设置当前的mask
  sigaddset(&act.sa_mask, SIGQUIT);
  act.sa_flags = 0;

  int ret = sigaction(SIGINT, &act, &oldact); // 注册新号捕捉函数
  sys_err(ret == -1, "sig_action error");
  // ret = sigaction(SIGQUIT, &act, &oldact); 捕捉停止进程信号
  // sys_err(ret == -1, "sig_action error");
  while (1)
    ;
}

/**
 * @brief SIGCHLD
 * 产生条件: 子进程终止时；子进程接收到SIGSTOP信号停止时；子进程处于停止态，接受到SIGCONT后唤醒时
 *
 * 借助SIGCHLD信号回收子进程
 * 子进程结束运行时，其父进程会收到SIGCHLD信号，该信号的默认处理动作是忽略，可以捕捉该信号，在捕捉函数中完成子进程状态的回收
 */
void sys_err(int flag, const char *message)
{
  if (flag)
  {
    perror(message);
    exit(1);
  }
}

void collect(int signo)
{
  pid_t wpid;
  int status;
  // while((wpid = wait(NULL))!=-1) {
  while ((wpid = waitpid(-1, &status, 0)) != -1)
  {
    sys_err(wpid == -1, "wait error");
    if (WIFEXITED(status))
    {
      printf("num %d, collect pid %d\n", WEXITSTATUS(status), wpid);
    }
  }
}
int sig_child()
{
  int i;
  pid_t pid;
  for (i = 0; i < 5; i++)
  {
    if ((pid = fork()) == 0)
    {
      break;
    }
  }
  if (i == 5)
  {
    struct sigaction act;
    act.sa_handler = collect; // 设置回调
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGCHLD, &act, NULL);
    printf("parent read to collect resource ...\n");
    sleep(10);
  }
  else
  {
    printf("num %d: child pid is %d\n", i, getpid());
    return i;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  return sig_child();
}
