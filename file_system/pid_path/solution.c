#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

//
// Created by r1d1 on 03/04/2020.
//

int get_ppid_custom(int pid) {
    char pids[10];
    char path[20] = "/proc/";
    snprintf(pids, sizeof(pids), "%d", pid);
    strcat(path, pids);
    strcat(path, "/status");
    FILE* f = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char ppid_s[10];
    int pnt = 0;
    int ppid, i;
    while ((read = getline(&line, &len, f)) != -1) {
        // printf("Retrieved line of length %zu:\n", read);
        if (strstr(line, "PPid:")) {
            for (i = 0; i < len; i++){
                if (isdigit(line[i])) {
                    ppid_s[pnt] = line[i];
                    pnt++;
                }
            }
        }
    }
    ppid_s[pnt] = '\0';
    sscanf(ppid_s, "%d", &ppid);
    fclose(f);
    return ppid;
}


int main(int argc, char *argv[]){
    int ppid;
    sscanf(argv[1], "%d", &ppid);
    printf("%i\n", ppid);
    while (1) {
        ppid = get_ppid_custom(ppid);
        printf("%i\n", ppid);
        if ((ppid == 1))
            break;
    }
    return 0;
}

