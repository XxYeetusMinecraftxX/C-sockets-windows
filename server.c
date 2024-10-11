#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <unistd.h>

typedef struct{
    int x,y,z;
} pdata;

int main(int argc, char *argv[]){

    WSADATA wsa;
    SOCKET sck;
    char addr[] = "";
    char buf[1024];
    int port = 8080;
    struct sockaddr_in server, sender;

    pdata pck;

    printf("Input address:\n");
    scanf("%s", addr);
    printf("Input port:\n");
    scanf("%d", &port);

    WSAStartup(MAKEWORD(2,2), &wsa) != 0;

    if( (sck = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        printf("broken socket");
    }

    if(addr == "all"){
        server.sin_addr.s_addr = INADDR_ANY;
    } else if(addr == "localhost"){
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    } else {
        server.sin_addr.s_addr = inet_addr(addr);
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if( (bind(sck, (const struct sockaddr *) &server, sizeof(server))) < 0 ){
        printf("bind broken");
    }
    
    int n;
    int sender_len = sizeof(sender);

    while(1){

    memset(&sender, 0, sizeof(sender));

    n = recvfrom(sck, (char *) buf, sizeof(buf), 0, (struct sockaddr *) &sender, &sender_len);

    memcpy(&pck, &buf, sizeof(pdata));
    printf("%d %d %d\n", pck.x, pck.y, pck.z);
    }

    close(sck);

}
