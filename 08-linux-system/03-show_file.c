#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <dirent.h> 
#include<sys/stat.h>
void sys_err(int flag, const char* message)
{
  if(flag)
  {
    perror(message);
    exit(1);
  }
}

// 递归展示目录下所有文件信息
void show_all_file(const char* path)
{
  DIR* dir = opendir(path);
  sys_err(dir == NULL, "open dir error");

  struct dirent *p;
  while ((p=readdir(dir)) != NULL)
  {
    if(strcmp(p->d_name, ".") == 0 || strcmp(p->d_name, "..") == 0) 
    {
      continue;
    }
    char fullpath[1024];  
    // 安全性：snprintf函数提供了一个可指定最大输出字符数的参数，这可以防止缓冲区溢出。而sprintf没有这个功能，
    //        如果不小心超出了缓冲区的容量，就可能导致程序崩溃或更严重的安全问题。
    // 灵活性：sprintf在格式化字符串时提供了更多的格式选项，比如处理宽度和精度。然而，snprintf提供的选项较少。
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, p->d_name); 

    struct stat buf;
    int ret = stat(fullpath, &buf);
    sys_err(ret==-1,  "file status error");

    //if(access(fullpath, F_OK)==0)
    if(S_ISDIR(buf.st_mode))
    {
      show_all_file(fullpath);
    }
    else
    {
      printf("%s\n", fullpath);
    }
  }
  closedir(dir);
}

int main(int argc, char* argv[])
{
  char *path = argv[1];
  printf("file list\n");
  show_all_file(path);
  return 0;
}