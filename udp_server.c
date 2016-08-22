/**
 * Using netem to enforce a packet loss of 50% an assertion fails.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main (int argc, char** argv) {
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));

  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(12345);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);

  int optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  bind(sockfd, (const struct sockaddr*)&saddr, sizeof(saddr));


  char buf[2] = { 0, 0 };
  ssize_t read;
  socklen_t addrlen = sizeof(saddr);

  read = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
  printf("%s\n", buf);
  assert(buf[0] == '1');
  assert(read == 1);

  read = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
  printf("%s\n", buf);
  assert(buf[0] == '2');
  assert(read == 1);

  read = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
  printf("%s\n", buf);
  assert(buf[0] == '3');
  assert(read == 1);

  return EXIT_SUCCESS;
}
