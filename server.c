#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "checkprime.h"

int N = 12;

void error(char *message) {
	printf("%s() failed, errno = %d", message, errno);
  	exit(1);
}

void child(int sock) {
	struct timespec start, finish;
	double elapsed;

	char requestBuff[256];
	char answerBuff[256];
	int requestLen = read(sock, requestBuff, sizeof(requestBuff));
	if(-1 == requestLen) {
		error("read");
	}
	
	unsigned long long int number = strtoull(requestBuff, NULL, 10);

	
	clock_gettime(CLOCK_MONOTONIC, &start);
	int answer = isPrime(number, N);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	if(answer == 1)
		sprintf(answerBuff, "YES N=%i time=%fsec\n", N, elapsed);
	else
		sprintf(answerBuff, "NO N=%i time=%fsec\n", N, elapsed);

	write(sock, answerBuff, strlen(answerBuff));
	close(sock);
	exit(0);
}

int main() {
  struct sockaddr_in addr;
  int accepted_socket;
  int fork_pid;
  int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(-1 == listen_socket) {
  	error("socket");
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(31337);
  printf("ok1\n");
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  printf("ok2\n");
  if(-1 == bind(listen_socket, (struct sockaddr*)&addr, sizeof(addr))){
    error("bind");
  }

  if(-1 == listen(listen_socket, 100)) {
    error("listen");
  }

  for(;;) {
    accepted_socket = accept(listen_socket, 0, 0);
    if(-1 == accepted_socket) {
      error("accept");
    }

    fork_pid = fork();
    if(-1 == fork_pid) {
      error("fork");
    } else if(0 == fork_pid) {
      close(listen_socket);
      child(accepted_socket);
    } else {
      close(accepted_socket);
    }
  }
  exit(0);
}
