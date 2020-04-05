#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 5000

struct sockaddr_in local;

int main(int c, char **v)
{

    if (c != 2)
        return -1;

    int port = atoi(v[1]);
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int result = bind(s, (struct sockaddr*) &local, sizeof(local));



    while (1){
        char buf[BUFSIZE] = {0};
        read(s, buf, BUFSIZE);
        printf("%s", buf);
        if (strcmp(buf, "OFF\n"))
            break;

    }

    return 0;
}
