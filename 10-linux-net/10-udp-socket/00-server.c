#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>

#define SERVER_PORT 8000

void sys_err(int flag, char* message) {
  if (flag) {
    perror(message);
    exit(-1);
  }
}
int main(int argc, char const *argv[])
{
  int socketfd, res;
  char buf[1024];
  char ip[INET_ADDRSTRLEN];
  int i; /*用于遍历*/

  socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  sys_err(socketfd == -1, "socket error");

  struct sockaddr_in sock, client;
  socklen_t client_length;

  bzero(&sock, sizeof(sock));
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = htonl(INADDR_ANY);
  sock.sin_port = htons(SERVER_PORT);

  res = bind(sockfd, (struct sockaddr *) &sockaddr_in, sizeof(sock));
  sys_err(res==-1, "bind error");

  while(1) {
    int length = recvfrom(socketfd, buf, sizeof(buf), MSG_PEEK, &client, &client_length);
    sys_err(length == -1, "recv error");
    printf("receive from client %s at port %d\n", inet_ntop(AF_INET, &client.sin_addr, ip, sizeof(ip)), ntohs(client.sin_port));
    // 加工
    for (i = 0; i< length; i++) {
      buf[i] = toupper(buf[i]);
    }

    // 发送给客户端
    length = sendto(socketfd, buf, n, 0, &client, sizeof(client));
    sys_err(length == -1, "sendto error");
  }
  close(socketfd);
  return 0;
}
