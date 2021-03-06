#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

//
// Created by r1d1 on 04/04/2020.
//

int main (void)
{
    pid_t pid = fork();
    if (pid) {
        printf("%i\n", pid);
        return 0;
    }
    else {
        setsid();
        chdir("/");
        open("/dev/null", O_RDWR);
        dup(0);
        dup(0);
        while (1) {}
    }
    return 0;
}
