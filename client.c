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
    struct sockaddr_in server;

    pdata pck;

    pck.x = 5;
    pck.y = 10;
    pck.z = 15;

    printf("Input address:\n");
    scanf("%s", addr);
    printf("Input port:\n");
    scanf("%d", &port);

    WSAStartup(MAKEWORD(2,2), &wsa) != 0;

    if( (sck = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        printf("s", "broken socket");
    }

    if(addr == "localhost"){
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
    } else {
        server.sin_addr.s_addr = inet_addr(addr);
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    sendto(sck, buf, sizeof(buf), 0, (const struct sockaddr *) & server, sizeof(server));
    int n;

    while(1){

        printf("Input data x y z:\n");
        scanf("%d", &pck.x);
        scanf("%d", &pck.y);
        scanf("%d", &pck.z);

        memcpy(&buf, &pck, sizeof(pdata));

        n = sendto(sck, buf, sizeof(buf), 0, (const struct sockaddr *) & server, sizeof(server));
        //printf("%d\n", WSAGetLastError());
    }

    close(sck);
}
