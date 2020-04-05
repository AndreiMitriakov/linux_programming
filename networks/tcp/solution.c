#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>

#define BUFSIZE 5000

struct sockaddr_in local;

int cmp (char x1, char x2) {
    return x2 - x1;
}

int server (int port) {
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss, 5);

    cs = accept(ss, NULL, NULL);

    while (1){
        char buf[BUFSIZE] = {0};
        read(cs, buf, BUFSIZE);
        if (strstr(buf, "OFF\n") != NULL)
            break;
        qsort(buf, strlen(buf), sizeof(char), cmp);
        //  send back to the client
        write(cs, buf, strlen(buf)+1);
    }
    close(cs);
    return 0;
}

int main (int argc, char ** argv) {
    if (argc != 2)
        return -1;

    server(atoi(argv[1]));

    return 0;
}