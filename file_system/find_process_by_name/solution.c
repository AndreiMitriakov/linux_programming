#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, int ** argv) {
    DIR *d;
    struct dirent *dir;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int cnt = 0;
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
                read = getline(&line, &len, f);
                if (strstr(line, "genenv") != NULL)
                    cnt++;
                fclose(f);
            }
        }
        closedir(d);
    }
    printf("%d\n", cnt);
    return 0;
}

