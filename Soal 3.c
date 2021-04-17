#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>


int main(int argc, char *argv[]) {
 
  pid_t child_id;
  int status;
  char stringfile[40];
  struct tm *timestamp;

child_id = fork();
time_t now = time(NULL);
timestamp = localtime(&now);

strftime(stringfile, sizeof(stringfile), "%Y-%m-%d_%H:%M:%S", timestamp);

  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
   
    char *argv[] = {"mkdir", stringfile, NULL};
    execv("/bin/mkdir", argv);
    sleep (40);
  }}
  
