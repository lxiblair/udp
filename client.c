#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(0);
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    int s;
    struct sockaddr_in addr;
    char buffer[1024];
    socklen_t addr_size;

    // create a socket in internet domain with default protocol (UDP)
    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;               
    addr.sin_port = htons(port);             
    addr.sin_addr.s_addr = inet_addr(ip);    

    // to send data
    bzero(buffer, 1024); // clear data in buffer
    strcpy(buffer, "Hello World!");
    sendto(s, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
    printf("[+]Data send: %s\n", buffer);

    // receive data from server
    bzero(buffer, 1024);
    addr_size = sizeof(addr);
    recvfrom(s, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
    printf("[+]Data recv: %s\n", buffer);

    close(s);


    return 0;
}