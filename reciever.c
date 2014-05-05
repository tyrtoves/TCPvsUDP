#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h> 
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/timeb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <readline/readline.h>

int main() {
	int sock, listener;
    struct sockaddr_in addr;
    struct timeval this_time, this_time_end, res;
    char buf[1024];
    int len;
    int bytes_read;
	srand (time(NULL));
	//TCP
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0) {
        perror("SOCKET");
        exit(0);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3502);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("BIND");
        exit(0);
    }

    listen(listener, 10);

    sock = accept(listener, NULL, NULL);
    if(sock < 0) {
        perror("ACCEPT");
        exit(0);
    }
	gettimeofday(&this_time, 0);           
    while(1) {
        bytes_read = recv(sock, buf, 1024, 0);
        if(bytes_read <= 0) break;
    }
    gettimeofday(&this_time_end, 0);
    close(sock);
    close(listener);
	res.tv_sec= this_time_end.tv_sec -this_time.tv_sec;
	res.tv_usec=this_time_end.tv_usec-this_time.tv_usec;
	if(res.tv_usec < 0) {
		res.tv_sec--;
		res.tv_usec+=1000000;
	}
	printf("TCP: %u.%u sec \n", res.tv_sec, res.tv_usec);   
    
	//UDP
    int sock_udp;
    struct sockaddr_in addr_udp;
    sock_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_udp < 0) {
        perror("SOCKET");
        exit(0);
    }
    addr_udp.sin_family = AF_INET;
    addr_udp.sin_port = htons(3492);
    addr_udp.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock_udp, (struct sockaddr *)&addr_udp, sizeof(addr_udp)) < 0) {
        perror("BIND");
        exit(0);
    }         
  	gettimeofday(&this_time, 0);
    while (recvfrom(sock_udp, buf, 1024, 0, NULL, NULL) == 1024)
    	continue;
 	gettimeofday(&this_time_end, 0);
	res.tv_sec= this_time_end.tv_sec -this_time.tv_sec;
	res.tv_usec=this_time_end.tv_usec-this_time.tv_usec;
	if(res.tv_usec < 0) {
		res.tv_sec--;
		res.tv_usec+=1000000;
	}
	printf("UDP: %u.%u sec \n", res.tv_sec, res.tv_usec);   
	
    return 0;
}
