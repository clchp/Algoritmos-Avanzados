#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "socketGame"

int main() {
    int sock;
    struct sockaddr_un addr;
    char buffer[128];
    int low, high, secret, guess;

    printf("Ingrese rango bajo y alto: ");
    scanf("%d %d", &low, &high);
    printf("Piense un número secreto entre %d y %d: ", low, high);
    scanf("%d", &secret);

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    // Enviar rango inicial
    sprintf(buffer, "%d %d", low, high);
    write(sock, buffer, strlen(buffer) + 1);

    while (1) {
        // Recibir propuesta del servidor
        read(sock, buffer, sizeof(buffer));
        guess = atoi(buffer);
        printf("Servidor propuso: %d\n", guess);

        if (guess == secret) {
            strcpy(buffer, "Correcto");
            write(sock, buffer, strlen(buffer) + 1);
            printf("¡Servidor acertó!\n");
            break;
        } else if (guess > secret) {
            strcpy(buffer, "Alto");
            write(sock, buffer, strlen(buffer) + 1);
        } else {
            strcpy(buffer, "Bajo");
            write(sock, buffer, strlen(buffer) + 1);
        }
    }

    close(sock);
    return 0;
}
