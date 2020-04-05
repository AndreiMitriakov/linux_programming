#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

//
// Created by r1d1 on 04/04/2020.
//


int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read, i, length;
    char c;
    int cnt = 0;
    char cmd[100];
    sprintf(cmd, "./%s %s", argv[1], argv[2]);
    FILE *f = popen(cmd, "r");
    while ((read = getline(&line, &len, f)) != -1) {
        length = strlen(line);
        i = 0;
        for (; i < length; i++) {
            if (line[i] == '0')
                cnt++;
        }
    }
    printf("%i\n", cnt);

    return 0;
}
