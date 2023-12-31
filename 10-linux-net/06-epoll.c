#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
// 只在linux有用
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>
#include "wrap.h"
/**
 * @brief 突破文件描述符1024限制
 * cat /proc/sys/fs/file-max 查看一个进程可以打开的socket描述符上限 或者ulimit -a
 * 也可以修改上限
 * sudo  vim /etc/secutiry/limits.conf
 *        soft nofile  size
 *        hard nofile  20000 
 * 
 */


#define MAXLINE 8192
#define SERV_PORT 8000

#define OPEN_MAX 5000


int main(int argc, char *argv[])
{
    int i, listenfd, connfd, sockfd;
    int  n, num = 0;
    ssize_t nready, efd, res;
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;

    struct sockaddr_in cliaddr, servaddr;


    Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));      //端口复用

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    Listen(listenfd, 20);

    // 创建OPEN_MAX表示创建的红黑树监听节点数量 仅供内核参考 可以扩容
    // 返回值 指向新创建的红黑树的节点 fd
    efd = epoll_create(OPEN_MAX);           
    if (efd == -1)
        perr_exit("epoll_create error");

    struct epoll_event tep, ep[OPEN_MAX];       //tep: epoll_ctl参数  ep[] : epoll_wait参数

    // 事件 EPOLLIN EPOLLOUT EPOLLERR
    tep.events = EPOLLIN; 
    tep.data.fd = listenfd;           //指定lfd的监听时间为"读"

    // 第二个参数 op即 对该监听红黑树所做的操作
    //               EPOLL_CTL_ADD 添加fd到监听红黑树
    //               EPOLL_CTL_MOD 修改fd在监听红黑树上的监听事件。
    //               EPOLL_CTL_DEL 将一个fd从监听红黑树上摘下
    // 第三个参数 待监听的fd
    // 第四个参数 
    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);    //将lfd及对应的结构体设置到树上,efd可找到该树
    if (res == -1)
        perr_exit("epoll_ctl error");

    for ( ; ; ) {
        // epoll为server阻塞监听事件, ep为struct epoll_event类型数组, OPEN_MAX为数组容量, -1表永久阻塞
        // 返回的是有事件响应的个数，并且ep的前nready被设置为对应的fd信息
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); 
        if (nready == -1)
            perr_exit("epoll_wait error");

        for (i = 0; i < nready; i++) {
            if (!(ep[i].events & EPOLLIN))      //如果不是"读"事件, 继续循环
                continue;

            if (ep[i].data.fd == listenfd) {    //判断满足事件的fd是不是lfd            
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);    //接受链接

                printf("received from %s at PORT %d\n", 
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
                        ntohs(cliaddr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                tep.events = EPOLLIN; tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);      //加入红黑树
                if (res == -1)
                    perr_exit("epoll_ctl error");

            } else {                                                    //不是lfd, 
                sockfd = ep[i].data.fd;
                n = Read(sockfd, buf, MAXLINE);

                if (n == 0) {                                           //读到0,说明客户端关闭链接
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //将该文件描述符从红黑树摘除
                    if (res == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);                                      //关闭与该客户端的链接
                    printf("client[%d] closed connection\n", sockfd);

                } else if (n < 0) {                                     //出错
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //摘除节点
                    Close(sockfd);

                } else {                                                //实际读到了字节数
                    for (i = 0; i < n; i++)
                        buf[i] = toupper(buf[i]);                       //转大写,写回给客户端

                    Write(STDOUT_FILENO, buf, n);
                    Writen(sockfd, buf, n);
                }
            }
        }
    }
    Close(listenfd);
    Close(efd);

    return 0;
}

