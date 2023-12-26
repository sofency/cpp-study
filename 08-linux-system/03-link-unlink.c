#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

void deal_ret(int ret, int limit, const char* message) {
   if (ret < limit) {
    perror(message);
    exit(1);
  }
}

/**
 * @brief 改名操作
 * 
 */
void mv(const char* old, const char*new_path) {
  link(old, new_path);
  unlink(old);
}
void test() {
  int fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
  deal_ret(fd, 0, "open temp.txt error"); 
  int ret = unlink("temp.txt"); //临时文件处理 只会在进程结束时进行删除临时文件
  deal_ret(ret, 0, "unlink temp.txt error");
  const *message = "hello world\n";
  ret = write(fd, message, strlen(message));
  deal_ret(ret, 0, "write temp.txt error");
  printf("enter any letter to continue:\n");
  getchar();
  close(fd);
}

int main(int argc, char const *argv[])
{
  int choice = argv[0] - '0';
  switch (choice)
  {
  case 0: test();
    break;
  case 1: mv(argv[1], argv[2]);
  default:
    break;
  }
  return 0;
}
