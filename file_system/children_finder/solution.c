#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int children_cnt(pid_s) {
    /*
    Python pseudo code
    cnt = 0
    for process in proc:
        if process.status.ppid == pid:
            cnt += 1
            cnt += children_cnt(dir.status.pid)
    */
    int children_num = 0;

    DIR *d;
    struct dirent *dir;
    char *line = NULL;
    char buf[20];
    size_t len = 0;
    ssize_t read;
    int cnt = 0;
    int ppid;
    d = opendir("/proc");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            int pid = -1;
            sscanf(dir->d_name, "%i", &pid);
            if (pid > 0) {
                char fname[255];
                sprintf(fname, "/proc/%i/status", pid);
                FILE *f = fopen(fname, "r");

                while (read = getline(&line, &len, f) != -1) {
                    if (strstr(line, "PPid:") != NULL) {
                            sscanf(line, "%s %d", buf, &ppid);
                            break;
                    }
                }
                if (ppid == pid_s) {
                    children_num++;
                    children_num += children_cnt(pid);
                }
                fclose(f);
            }
        }
        closedir(d);
    }
    return children_num;
}

int main(int argc, char *argv[]){
    int pid;
    sscanf(argv[1], "%d", &pid);
    int num = children_cnt(pid);
    num += 1;
    printf("%i\n", num);
    return 0;
}



