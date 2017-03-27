#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 5555
#define MAX_LINE_LENGTH 4096

int main(void)
{
    int udpfd;
    struct sockaddr_in clientAddr, serverAddr;
    socklen_t  addrLength;
    size_t bytesRecvd;
    char msgBuf[MAX_LINE_LENGTH];
    const char defaultReply[] = "Hi!";
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(udpfd == -1)
        {
            // Ошибка открытия сокета
            perror("Can't create socket!");
            exit(1);
        }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(SERVER_PORT);
    if(bind(udpfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
        {
            // Ошибка назначения имени сокету
            perror("Can't bind socket!");
            exit(1);
        }
    while(true) {
        memset(&clientAddr, 0, sizeof(clientAddr));
        bytesRecvd = recvfrom(udpfd, &msgBuf, MAX_LINE_LENGTH, 0, (struct sockaddr*)&clientAddr, &addrLength);
        if(bytesRecvd > 0) {
            //Отправляем эхо-ответ
            sendto(udpfd, msgBuf, bytesRecvd, 0, (struct sockaddr*)&clientAddr, addrLength);
            //printf("Got packet!");
            write(1, "*\n", 2);
        }
    }

    exit(0);
}
