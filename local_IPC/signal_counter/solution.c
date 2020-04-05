#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//
// Created by r1d1 on 04/04/2020.
//

int sig1 = 0;
int sig2 = 0;
int flag = 1;

void sigusr1(){sig1++;}
void sigusr2(){sig2++;}
void sigterm(){flag = 0;}

int main(int argc, char *argv[]){
    signal(SIGUSR1, sigusr1);
    signal(SIGUSR2, sigusr2);
    signal(SIGTERM, sigterm);
    while(flag){}
    printf("%i %i\n", sig1, sig2);
    return 0;
}
