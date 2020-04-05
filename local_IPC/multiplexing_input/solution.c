#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main (void) {
    int fileDescriptor1 = open("in1", O_RDONLY, O_NONBLOCK);
    int fileDescriptor2 = open("in2", O_RDONLY, O_NONBLOCK);
    if(fileDescriptor1 < 0){
        printf("in1 does not exist");
    }
    if(fileDescriptor2 < 0){
        printf("in2 does not exist");
    }
    int cnt = 0;
    int i;
    while(1)
    {
        fd_set fds;
        int maxfd;
        int res;
        char buf[256];
        FD_ZERO(&fds);
        FD_SET(fileDescriptor1, &fds);
        FD_SET(fileDescriptor2, &fds);

        select(fileDescriptor2 + 1, &fds, NULL, NULL, NULL);
        if (FD_ISSET(fileDescriptor1, &fds))
        {
            res = read(fileDescriptor1, buf, sizeof(buf));
            if (res > 0)
            {
                cnt += atoi(buf);
            }
            if (res == 0)
                break;
        }
        if (FD_ISSET(fileDescriptor2, &fds))
        {
            res = read(fileDescriptor2, buf, sizeof(buf));
            if (res > 0)
            {
                cnt += atoi(buf);
            }
            if (res == 0)
                break;

        }

    }
    printf("%i\n", cnt);
    return 1;
}