#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Привет от TCP сервера!";
    
    // 1. Создаем TCP сокет
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 2. Настраиваем опции сокета
    if (setsockopt(server_fd,
        SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT, 
        &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Принимаем соединения откуда угодно
    address.sin_port = htons(PORT);        // Порт 8080
    
    // 3. Привязываем сокет к порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // 4. Слушаем входящие соединения
    if (listen(server_fd, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("TCP сервер слушает на порту %d\n", PORT);
    
    while (1) {
        // 5. Принимаем новое соединение
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                                (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        // 6. Читаем данные от клиента
        int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
        printf("Получено %d байт: %s\n", bytes_read, buffer);
        
        // 7. Отправляем ответ
        send(new_socket, hello, strlen(hello), 0);
        printf("Ответ отправлен\n");
        
        // 8. Закрываем соединение с этим клиентом
        close(new_socket);
        
        // Очищаем буфер для следующего соединения
        memset(buffer, 0, BUFFER_SIZE);
    }
    
    return 0;
}