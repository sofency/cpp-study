/**
 * @file 08-mmap.c
 * @author your name (you@domain.com)
 * @brief 内存映射 mmap
 * void *mmap(void *addr, size_t length, int port, int flags, int fd, off_t offset) 创建共享内存映射
 *        addr： 指定映射区的首地址，通常为NULL 表示让系统自动分配
 *        length: 共享内存映射区的大小
 *        prot: 共享内存映射区的读写属性。PROT_READ、PROT_WRITE、PROT_READ | PROT_WRITE
 *        flags: 标注共享内存的共享属性。MAP_SHARED、MAP_PRIVATE
 *        fd: 用于创建共享内存映射区的那个文件的文件描述符
 *        offset: 偏移位置，需要是4K的倍数
 * 返回值: 成功: 映射区的首地址  失败:MAP_FAILED, errno
 * 
 * 注意事项:
 * a. 创建映射区时， 隐含着一次对映射文件的读操作
 * b. 当MAP_SHARED时，要求映射区的权限 <  文件打开的权限 而MAP_PRIVATE则无所谓
 * @version 0.1
 * @date 2023-12-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include <sys/mman.h>

void sys_err(int flag, const char* message) {
  if (flag) {
    perror(message);
    exit(1);
  }
}

struct Student
{
  int id;
  char name[256];
  int score
};

int main(int argc, char const *argv[])
{
  int fd = open("testmmap", O_RDWR | O_CREAT | O_TRUNC, 0644);   /* code */
  sys_err(fd == -1, "open file error");

  struct Student stu = {1, "sofency", 21};
  // ftruncate(fd, 20); /*指定空间大小*/
  ftruncate(fd, sizeof(stu));
  // int length = lseek(fd, 0, SEEK_END);

  // 创建映射区需要read权限
  // char *p = mmap(NULL, 20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  // fd=-1的话 为匿名映射  映射改为MAP_SHARED | MAP_ANONYMOUS 匿名映射只能用于血缘关系间通信
  struct Student *p = mmap(NULL, sizeof(stu), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

  sys_err(p == MAP_FAILED, "mmap error");

  // strcpy(p, "hello world"); /*使用p对文件进行读写操作*/
  memcpy(p, &stu, sizeof(stu));

  // printf("---%s---\n", p); /*读操作*/
  printf("id: %d, name: %s, socre: %d\n", p->id, p->name, p->score); /*读操作*/


  // munmap释放的地址必须是mmap申请返回的首地址
  int ret = munmap(p, sizeof(stu));
  sys_err(ret == -1, "unmap file error");

  return 0;
}
