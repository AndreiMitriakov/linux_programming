#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1000

int main(int argc, char *argv[])
{
    int shmid, shmid1, shmid2, i;
    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, SHM_SIZE,0666|IPC_CREAT);
    shmid1 = shmget(atoi(argv[1]), SHM_SIZE, 0666 );
    shmid2 = shmget(atoi(argv[2]), SHM_SIZE, 0666 );

    int *arr = (int*) shmat(shmid, (void*)0, 0);
    int *arr1 = (int*) shmat(shmid1,(void*)0, 0);
    int *arr2 = (int*) shmat(shmid2,(void*)0, 0);

    for (i = 0; i < 100; i++)
        arr[i] = arr1[i] + arr2[i];

    shmdt(arr2);
    shmdt(arr1);
    shmdt(arr);

    printf("%i\n", key);
    return 0;
}
