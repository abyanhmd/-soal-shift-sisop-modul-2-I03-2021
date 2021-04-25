#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <signal.h>


int Direct();
int Download(char tanggalD[]);
void Cipher(char message[], int key);
void TXT(char message[], char tanggalD[]);
void ZIP(char tanggalD[]);
void Killer(int argN, char **argV, int pid);



int Direct()
{
char tanggalD[150];
int status;
time_t t;
pid_t anak_id;
anak_id = fork();
t = time(NULL);
 
strftime(tanggalD, sizeof(tanggalD), "%Y-%m-%d_%H:%M:%S", localtime(&t));
if(anak_id < 0)
exit(EXIT_FAILURE);
if (anak_id == 0)
{
 
char *argv[] = {"mkdir", tanggalD, NULL};
execv("/bin/mkdir", argv);
}
else if(anak_id > 0 && wait(&status) > 0)
{
pid_t anak_id2;
anak_id2 = fork();
if(anak_id2 < 0)
exit(EXIT_FAILURE);
if (anak_id2 == 0)
{
pid_t anak_id3;
anak_id3 = fork();
if(anak_id3 < 0)
exit(EXIT_FAILURE);
if (anak_id3 == 0)
{

  short gambar = 1;
while(gambar <= 10)
{
int z = Download(tanggalD);
if(z == 7)
{
gambar++;
sleep(5);
}
}
}
else if(anak_id3 > 0 && wait(&status) > 0)
{
char message[20] = {"Download Success"};
int key = 5;
Cipher(message, key);
TXT(message, tanggalD);
ZIP(tanggalD);
}

 
kill(getpid(),SIGTERM);
}
else
{
return 10;
}
}
}

int Download(char tanggalD[])
{

char temp[150];
  char path[150]={};
  char url[150]={};
pid_t anak_id;
anak_id = fork();
time_t t;
t = time(NULL);
strftime(temp, sizeof(temp), "%Y-%m-%d_%H:%M:%S", localtime(&t));
strcat(path, tanggalD);
  strcat(path,"/");
  strcat(path, temp);
 
  int SIZE = (((int)t)%1000)+50;
  sprintf(url, "https://picsum.photos/%d/%d", SIZE, SIZE);
if(anak_id < 0)
exit(EXIT_FAILURE);
if (anak_id == 0)
{

char *argv[] = {"wget",url , "-qO", path, NULL};
  execv("/bin/wget", argv);
  kill(getpid(),SIGTERM);
}
else
{
return 7;
}
}

void Cipher(char message[], int key)
{
char ch;
int i;
for(i = 0; message[i] != '\0'; ++i){
ch = message[i];
 
if(ch >= 'a' && ch <= 'z'){
ch = ch + key;
if(ch > 'z'){
ch = ch - 'z' + 'a' - 1;
}
 
message[i] = ch;
}
else if(ch >= 'A' && ch <= 'Z'){
ch = ch + key;
if(ch > 'Z'){
ch = ch - 'Z' + 'A' - 1;
}
 message[i] = ch;
 printf ("ch");
}
}
}

void TXT(char message[], char tanggalD[])
{
FILE *file1;
char path [150] = {};

strcat(path, tanggalD);
  strcat(path,"/");
  strcat(path, "status.txt");
  file1 = fopen(path, "w");
  fputs(message, file1);
  fclose(file1);
 
}

void ZIP(char tanggalD[])
{
char *argv[] = {"zip", "-r" , "-m", tanggalD, tanggalD, NULL};
  execv("/bin/zip", argv);
}

void Killer(int argN, char **argV, int pid)
{
pid_t anak_id;
anak_id = fork();
int status;
if(anak_id < 0)
exit(EXIT_FAILURE);
if (anak_id == 0)
{
FILE *file1 = fopen("killer.sh", "w");
if (argN == 2 && strcmp(argV[1], "-z") == 0)
{
fprintf(file1, "#!/bin/bash\nkillall -9 io3\nrm \"$0\"");
}
else if (argN == 2 && strcmp(argV[1], "-x") == 0)
{
fprintf(file1, "#!/bin/bash\nkill %d\nrm \"$0\"", pid);
}
fclose(file1);
}
else if(anak_id > 0 && wait(&status) > 0)
{
char *argv[] = {"chmod", "+x", "killer.sh", NULL};
        execv("/bin/chmod", argv);
}

}

int main(int argN, char **argV) {
pid_t pid, sid;        

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
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  Killer(argN, argV, (int) getpid()+1);
while(1)
{
int a = Direct();
if (a == 10)
{
sleep(40);
}
}

}
