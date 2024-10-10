#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <unistd.h>

typedef struct {
    int var;
} data;

int main(int argc, char *argv[]){

    WSADATA wsa;
    SOCKET sck;
    char addr[] = "";
    char buf[1024] = "dupa";
    int port = 8000;
    struct sockaddr_in server;
    data pck;

    printf("Input address:\n");
    scanf("%s", addr);
    printf("Input port:\n");
    scanf("%d", &port);
    printf("Input var:\n");
    scanf("%d", &pck.var);

    WSAStartup(MAKEWORD(2,2), &wsa) != 0;

    if( (sck = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){
        printf("s", "broken socket");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    sendto(sck, buf, sizeof(buf), 0, (const struct sockaddr *) & server, sizeof(server));
    int n;

    while(1){
        printf("x\n");
        n = sendto(sck, buf, sizeof(buf), 0, (const struct sockaddr *) & server, sizeof(server));
        printf("%d\n", WSAGetLastError());
        sleep(3);
    }

    close(sck);
}