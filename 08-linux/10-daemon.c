/**
 * @file 10-session.c
 * @author your name (you@domain.com)
 * @brief 
 * 会话
 * 1. 调用进程不能是进程组组长，该进程变成新回话首进程。
 * 2. 该进程成为一个新进程组的组长进程
 * 3. 需有root权限
 * 4. 新会话丢弃原有的控制终端，该会话没有控制终端
 * 5. 该调用进程是组长进程，出错返回
 * 6. 建立新会话时，先调用fork(), 父进程终止，子进程调用setsid();
 * 
 * 守护进程
 * daemon进程。通常运行在操作系统后台，脱离控制终端。一般不与用户直接交互。周期性的等待某个事件发生或周期性执行某一动作
 * 不受用户登录注销影响。通常采用以d结尾的命名方式
 * 
 * @version 0.1
 * @date 2023-12-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>

void sys_err(int flag, const char *message)
{
  if (flag)
  {
    perror(message);
    exit(1);
  }
}


int main(int argc, char const *argv[])
{
  pid_t pid;
  int ret, fd;

  pid = fork();
  if (pid > 0) 
    exit(0); // 1. 父进程终止
  pid = setsid(); // 2. 创建新会话
  sys_err(pid == -1, "setsid error");
  ret = chdir("/root/temp/mysql"); // 3.按需 改变工作目录
  sys_err(ret == -1, "chdir error");
  umask(0022); // 4.按需 改变文件访问权限掩码
  close(STDIN_FILENO); // 关闭文件描述符 0
  fd = open("/dev/null", O_RDWR); // fd -> 0
  sys_err(fd==-1, "open error");
  dup2(fd, STDOUT_FILENO); // 5. 按需 重定向stdout和stderr
  dup2(fd, STDERR_FILENO);
  
  while(1); // 模拟守护进程业务

  return 0;
}
