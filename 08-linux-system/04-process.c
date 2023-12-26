#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/wait.h>

/**
 * @brief waitpid函数 指定一个进程进行回收
 * pid_t waitpid(pid_t pid, int * status, int options)
 *  pid 指定回收的子进程 
 *      0 回收和当前调用waitpid一个组的所有子进程；
 *     >0 回收指定id的子进程，-1回收任意子进程。
 *     -1 meaning wait for any child process.
 *    <-1 回收指定进程组内任意子进程 -1000 是回收进程组1000的子进程
 *  status 传输回收子进程的状态
 *  options: WNOHANG 指定回收方式为非阻塞
 * 返回值：
 * 
 */
void loop_fork_wait_one()
{
  int i;
  pid_t pid, temp_pid, wpid;
  for (i = 0; i < 5; i++) {
    pid = fork();
    if(pid == 0) {
      break;
    }
    if (i == 2) {
      temp_pid = pid;
    }
  }
  if (i==5) {
    sleep(5);
    printf("before waitpid %d\n", temp_pid);
    wpid = waitpid(temp_pid, NULL, WNOHANG);
    if(wpid == -1) {
      printf("wait pid error");
      exit(1);
    }
    printf("I'm parent, wait child pid %d finish\n", temp_pid);
  } else {
    sleep(i);
    printf("num %d child pid: %d\n", i, getpid());
  }
}

void loop_fork_wait_all()
{
  int i;
  pid_t pid, wpid;
  for (i = 0; i < 5; i++) {
    pid = fork();
    if(pid == 0) {
      break;
    }
  }
  if (i==5) {
    while( (wpid = waitpid(-1, NULL, WNOHANG)) != -1) { //使用非阻塞方式回收子线程
      if(wpid > 0) {
        printf("child pid %d finish \n", wpid);
      } else if(wpid == 0) {
        sleep(1);
        continue;
      }
    }
  } else {
    sleep(i);
    printf("num %d child pid: %d\n", i, getpid());
  }
}


int main(int argc, char const *argv[])
{
  printf("=========  before fork 1 ==========\n");

  /**
   * @brief 
   * 如果创建成功 父子进程都会返回值进行向下执行
   * 返回0表示当前是子进程创建成功
   * 返回>0 表示当前是父亲进程 返回的是子进程的进程id
   * 父子进程对于全局变量的处理 读时共享，写时复制
   */
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork error");
    exit(1);
  } else if (pid == 0) {
    printf("child pid is created pid : %d, parent pid: %d\n", getpid(), getppid());
  } else if(pid > 0) {
    printf("son pid : %d, current pid: %d, parent's parent pid: %d\n", pid, getpid(), getppid());
  }
  return 0;
}
