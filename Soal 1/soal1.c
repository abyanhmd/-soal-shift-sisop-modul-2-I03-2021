#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main() {
    pid_t child_id;
    child_id = fork();
    int status;

    if(child_id == 0) {
        if(fork() == 0) {
            char *extract[] = {"unzip", "-q", "uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", NULL};
            execv("/usr/bin/unzip", extract);
        }
        else {
            execl("/usr/bin/mv", "mv", "MUSIK", "Musyik", NULL);

            char *rem[] = {"rm", "-r", "MUSIK", NULL};
            execv("/usr/bin/rm", rem);
        }
    }
    else {
        char *URL[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "/home/Sisop/Modul_2", "-q", NULL};
        execv("/usr/bin/wget", URL);
    }

    return 0;
}