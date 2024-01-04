/**
 * @file server.c
 * @author your name (you@domain.com)
 * @brief 本地套接字 主要两个进程间通信
 * pipe mmap fifo
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

#include "wrap.h"

#define SERV_ADDR  "serv.socket"

void sys_err(int flag, char* message) {
  if (flag) {
    perror(message);
    exit(-1);
  }
}

int main(void)
{
    int lfd, cfd, len, size, i;
    struct sockaddr_un servaddr, cliaddr;  // 本地套接字使用sockaddr_un
    char buf[4096];

    lfd = Socket(AF_UNIX, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, SERV_ADDR);

    // 用于获取结构体中成员相对于结构体开始位置的偏移量。这个宏定义在 stddef.h（在 C 中）或 cstddef（在 C++ 中）
    len = offsetof(struct sockaddr_un, sun_path) + strlen(servaddr.sun_path);     /* servaddr total len */

    unlink(SERV_ADDR);                              /* 确保bind之前serv.sock文件不存在,bind会创建该文件 */
    Bind(lfd, (struct sockaddr *)&servaddr, len);           /* 参3不能是sizeof(servaddr) */

    Listen(lfd, 20);

    printf("Accept ...\n");
    while (1) {
        len = sizeof(cliaddr);  //AF_UNIX大小+108B
        // cliaddr是传出参数
        cfd = Accept(lfd, (struct sockaddr *)&cliaddr, (socklen_t *)&len);

        len -= offsetof(struct sockaddr_un, sun_path);      /* 得到文件名的长度 */
        cliaddr.sun_path[len] = '\0';                       /* 确保打印时,没有乱码出现 */

        printf("client bind filename %s\n", cliaddr.sun_path);

        while ((size = read(cfd, buf, sizeof(buf))) > 0) {
            for (i = 0; i < size; i++)
                buf[i] = toupper(buf[i]);
            write(cfd, buf, size);
        }
        close(cfd);
    }
    close(lfd);

    return 0;
} 