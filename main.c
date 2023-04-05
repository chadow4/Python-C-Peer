#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9000);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connexion échouée");
        exit(1);
    }

    int x = 200, y = 200;
    
    while (1) {

        // recuperation des coordonnées 
        char buffer[1024];
        printf("Entrez la position de la balle (format x,y) : ");
        fgets(buffer, 1024, stdin);
        sscanf(buffer, "%d,%d", &x, &y);

        write(sock, buffer, strlen(buffer));
        

        // envoi des données
        read(sock, buffer, 1024);
        sscanf(buffer, "%d,%d", &x, &y);
        printf("Position de la balle : %d,%d\n", x, y);
    }

    close(sock);
    return 0;
}