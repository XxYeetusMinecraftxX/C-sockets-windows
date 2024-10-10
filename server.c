#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <unistd.h>

typedef struct {
    int var;
} data;


int main(){

    WSADATA wsa;
    SOCKET sck;
    char addr[] = "";
    char buf[1024];
    int port = 8000;
    struct sockaddr_in server, sender;
    data pck;

    printf("Input address:\n");
    scanf("%s", addr);
    printf("Input port:\n");
    scanf("%d", &port);

    WSAStartup(MAKEWORD(2,2), &wsa) != 0;

    if( (sck = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        printf("broken socket");
    }

    //server.sin_addr.s_addr = inet_addr(addr);
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if( (bind(sck, (const struct sockaddr *) &server, sizeof(server))) < 0 ){
        printf("bind broken");
    }
    
    int n;
    int sender_len = sizeof(sender);

    printf("a");

    while(1){

    memset(&sender, 0, sizeof(sender));
    
    printf("b");

    n = recvfrom(sck, (char *) buf, sizeof(buf), 0, (struct sockaddr *) &sender, &sender_len);

    printf("c");

    buf[n] = '\0';
    printf("%s\n", buf);
    printf("%d\n", n);

    sleep(5);
    }

    close(sck);

}