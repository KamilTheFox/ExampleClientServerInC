#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024 // Max 1400 (Вообще 1500, но лучше оставить 1400 из за заголовков)

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT);
    
    if (bind(sockfd, (const struct sockaddr *)&servaddr, 
             sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    printf("UDP сервер слушает на порту %d\n", PORT);
    printf("Ждем сообщения от клиентов...\n");
    
    while (1) {
        socklen_t len = sizeof(cliaddr);
        
        int n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 
                         false, (struct sockaddr *)&cliaddr, &len);
        
        if (n > 0) 
        {
            buffer[n] = '\0';
        } else if (n == 0) 
        {
            printf("Получен пустой пакет\n");
            continue;
        } else 
        {
            perror("recvfrom failed");
            continue;
        }
        
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(cliaddr.sin_addr), client_ip, INET_ADDRSTRLEN);
        
        printf("Получено %d байт от %s:%d\n", n, client_ip, ntohs(cliaddr.sin_port));
        printf("Сообщение: %s\n", buffer);
        
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), 
                "UDP сервер получил: '%.100s' (длина: %d байт)", buffer, n);
        
        sendto(sockfd, response, strlen(response), 
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("Ответ отправлен клиенту\n\n");
    }
    
    close(sockfd);
    return 0;
}