#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

int main() {
    pid_t pid, sid, child_id;
    int status;
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/abyan/Sisop/Modul_2/Folder")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    char *URL[] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", 
                "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", 
                "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
    char *zipName[] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};
    char *oldName[] = {"FOTO", "MUSIK", "FILM"};
    char *newName[] = {"Pyoto", "Musyik", "Fylm"};

    while(1) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        int day = tm.tm_mday;
        int month = tm.tm_mon + 1;
        int hour = tm.tm_hour;
        int minute = tm.tm_min;
        int second = tm.tm_sec;
        
        if(day == 9 && month == 4 && hour == 16 && minute == 22 && second == 0) {
            for(int i = 0; i < 3; i++) {
                char *argv[] = {"wget", "-q", "--no-check-certificate", URL[i], "-O", zipName[i], NULL};
                if((child_id = fork()) == 0)
                    execv("/usr/bin/wget", argv);
                while((wait(&status)) > 0);
            }
        
            for(int j = 0; j < 3; j++) {
                char *argv[] = {"unzip", "-qq", zipName[j], NULL};
                if((child_id = fork()) == 0)
                    execv("/usr/bin/unzip", argv);
                while((wait(&status)) > 0);
            }

            for(int k = 0; k < 3; k++) {
                char *argv[] = {"mv", "-T", oldName[k], newName[k], NULL};
                if((child_id = fork()) == 0)
                    execv("/usr/bin/mv", argv);
                while((wait(&status)) > 0);
            }
        }
        
        else if(day == 9 && month == 4 && hour == 22 && minute == 22 && second == 0) {
            char *zipFolder[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
            execv("/usr/bin/zip", zipFolder);
        }

        sleep(1);
    }
    return 0;
}
