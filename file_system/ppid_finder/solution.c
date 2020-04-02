#include <stdio.h>
#include <unistd.h>
#include <string.h>
    
int main() {
    pid_t pid = getpid();
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
    printf("%i\n", ppid);
    fclose(f);
    return 0;
}

