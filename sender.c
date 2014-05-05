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



char msg[1000];

int main() {
	int n = 100000;
	int sock;
    struct sockaddr_in addr;
    int i;
	//TCP
    sock = socket(AF_INET, SOCK_STREAM, 0);
 	if(sock < 0) {
        perror("SOCKET");
        exit(0);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3502);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("CONNECT");
        exit(0);
    }
    for(i = 0; i < n; ++i) 
    	send(sock, msg, sizeof(msg), 0);
    close(sock);
    
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
    addr_udp.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    for(i = 0; i < n; ++i) { 	
    	sendto(sock_udp, msg, sizeof(msg), 0, (struct sockaddr *)&addr_udp, sizeof(addr_udp));
    }
	close(sock_udp);
	
    return 0;
}
