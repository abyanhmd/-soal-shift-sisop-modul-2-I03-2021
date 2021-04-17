#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {

  pid_t child_id;
  int status;

  child_id = fork();
  if (child_id == 0) {
    
    char *argv[] = {"unzip", "pets", "-d","/home/hilmythoriq/Modul2/petshop",NULL}; //unzip pets zip to directory
    execv("/bin/unzip", argv); //run unzip
  } else {
    
    while ((wait(&status)) > 0);
    char *argv[] = {"rm", "-r", "/home/hilmythoriq/Modul2/petshop/apex_cheats","/home/hilmythoriq/Modul2/petshop/musics", "/home/hilmythoriq/Modul2/petshop/unimportant_files" ,NULL}; //remove unnecessary files
    execv("/usr/bin/rm", argv); //run rm 
}
    }
	
