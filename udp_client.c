#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main (int argc, char**argv) {
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  struct sockaddr_in daddr;
  memset(&daddr, 0, sizeof(daddr));

  daddr.sin_family = AF_INET;
  daddr.sin_port = htons(12345);
  inet_pton(AF_INET, argv[1], &daddr.sin_addr);
  
  socklen_t addrlen = sizeof(daddr);

  sendto(sockfd, "1", 1, 0, (const struct sockaddr*)&daddr, addrlen);
  sendto(sockfd, "2", 1, 0, (const struct sockaddr*)&daddr, addrlen);
  sendto(sockfd, "3", 1, 0, (const struct sockaddr*)&daddr, addrlen);

  return EXIT_SUCCESS;
}
