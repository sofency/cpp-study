网络字节序：
   小端法：（PC本地存储） 高位存高地址，低位存低地址
   大端法：（网络存储）高位存低地址，低位存高地址
   htonl： 本地->网络（IP）
   htons： 本地->网络（PORT）
   ntohl： 网络->本地(IP)
   ntohs:  网络->本地 （PORT）

IP地址转换函数
  int inet_pton(int af, const char *src, void *dst);          本地字节序 --> 网络字节序
          af:  AF_INET (IPV4)  AF_INET6（IPV6）   -- 协议版本
          src: IP地址 点分十进制
          dst: 传唤后的网络字节序IP

          return:
            成功：1
            异常 0:  src 不是有效ip
            失败 -1 异常 设置errno
  
  const char * inet_ntop(int af, const void *src, char *dst, socklen_t size);  网络字节序 ---> 本地字节序
          af:  AF_INET (IPV4)  AF_INET6（IPV6）   -- 协议版本
          src: 网络字节序IP地址
          dst: 本地字节序IP
          size: dst大小
          return:
            成功： dst
            失败：null


socket函数
  #include<sys/socket.h>
  int socket(int domain, int type, int protocol) 创建一个套接字
      domain: AF_INET、AF_INET6、AF_UNIX
      type: SOCK_STREAM, SOCK_DGRAM
      protocol:0
      return: 成功 返回 新套接字所返回的文件描述符
  
  int bind(int sockfd, const structaddr *addr, socklen_t addrlen); 给socket绑定一个地址 IP+PORT
      sockfd: socket函数的返回值
      addr:    struct socket_in addr; addr.sin_family = AF_INET; addr.sin_port=htons(8888);
              addr.sin_addr.s_addr = htonl(INADDR_ANY);
              (struct socketaddr*)&addr;
      addrlen: sizeof(addr) 地址结构大小

      return:
          成功：0
          异常 -1:  errno
  
  int listen(int sockfd, int backlog); 设置同时与服务器建立连接的上限值
      sockfd: socket 函数返回值
      backlog: 上限数值 最大值128

  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); 
      阻塞等待客户端建立连接，成功的话返回一个与客户端成功连接的socket文件fd
      socketfd: socket返回值
      addr: 传出参数 成功与服务器建立连接的那个客户端地址结构
      addrlen:传入传出 
            入： addr大小。出：客户端实际大小
      返回值：
        成功: 能与服务器进行数据通信的socket对应的文件描述
        失败: -1 errno
        
  int connect(int sockfd, const struct socketaddr *addr, socklen_t addrlen)
      使用现有的socket与服务器建立连接
      socketfd: socket 函数返回值
      addr: 传入函数 服务器的地址结构
      addrlen: 服务器的地址结构的大小
      return:
        成功：0
        异常 -1:  errno