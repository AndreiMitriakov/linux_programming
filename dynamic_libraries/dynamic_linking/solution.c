//
// Created by r1d1 on 30/03/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <dlfcn.h>

typedef int (*ext_fun)(int);

bool init_library(char *lib, char *func, ext_fun *fptr) {
    void *lib_ptr = dlopen(lib, RTLD_LAZY);

    if(NULL == lib_ptr)
        return false;

    *fptr = dlsym(lib_ptr, func);

    if (NULL == fptr)
        return false;

    return true;
}

int main(int argc, char *argv[]){
    char *lib = argv[1];
    char *func = argv[2];
    int iarg = atoi(argv[3]);

    ext_fun function = NULL;

    if (init_library(lib, func, &function))
        printf("%d\n", function(iarg));
    else
        printf("Something wrong\n");
    return 0;
}

/*
 *
 *
CC = gcc
SRC = solution.c
EXEC = solution
LD_FLAGS = -ldl

all: ${EXEC}

${EXEC}: ${SRC}
	@${CC} $@.c -o $@ -std=c11



 all: solution

solution: solution.c
	gcc -o solution solution.c -fPIC -ldl


all: solution lib

solution: solution.c lib
	gcc solution.c -fPIC -ldl -o solution

lib: libfunc.c
	gcc -o libShared.so libfunc.c -shared -fPIC
 * */