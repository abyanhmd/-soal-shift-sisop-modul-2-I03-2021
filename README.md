## Modul 2 - Group I03 

### **Number 1**
The problem asks us to download 3 zip files which contains video, photo, and music.
Each type of the zip file should be extracted and the folder named as **Musyik** for *mp3*, **Fylm** for *mp4*, and **Pyoto** for *jpg*. When it's Stevany's birthday (9 April 2021 22.22 WIB), the folders that have been unzipped need to be zipped with the name **Lopyu_Stevany.zip**. But before that, we need to download, unzip, and move the files 6 hours before her birthday.

We store all the links, zip names, folder names in variables.
```c
char *URL[] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
                "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", 
                "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
char *zipName[] = {"Foto_for_Stevany.zip", "Musik_for_Stevany.zip", "Film_for_Stevany.zip"};
char *oldName[] = {"FOTO", "MUSIK", "FILM"};
char *newName[] = {"Pyoto", "Musyik", "Fylm"};
```

We use daemon for this problem so the `exec` command can run more than once. First, we use `wget` command inside a loop to download the files iteratively.
```c
for(int i = 0; i < 3; i++) {
    char *argv[] = {"wget", "-q", "--no-check-certificate", URL[i], "-O", zipName[i], NULL};
    if((child_id = fork()) == 0)
        execv("/usr/bin/wget", argv);
    while((wait(&status)) > 0);
}
```
First, we store the terminal command inside `char` data type and execute it using `execv`. The option `-q` is used to make the terminal quiet and not to print all the log message.
The option `--no-check-certificate` is used to make the program run without checking the file's certificate.
The option `-O` is used to store all the downloaded file to the `zipName` variable. The `if` condition is used to make sure it is child process.
And the last is `wait` command to make sure the program runs one by one.

After that, we need to unzip all the downloaded file using unzip command.
```c
for(int j = 0; j < 3; j++) {
    char *argv[] = {"unzip", "-qq", zipName[j], NULL};
    if((child_id = fork()) == 0)
        execv("/usr/bin/unzip", argv);
    while((wait(&status)) > 0);
}
```
The format of this loop is not really different with the previous loop. The difference is only the parameter of the `argv`. The option `-qq` is to make the program run more quietly and not to print the log messages in the output. The `zipName` is the variable that is going to be unzipped.

In order to rename the folder, we can use `mv` command to move the folder to its directory following the new folder name to rename the folder name.
```c
for(int k = 0; k < 3; k++) {
    char *argv[] = {"mv", "-T", oldName[k], newName[k], NULL};
    if((child_id = fork()) == 0)
        execv("/usr/bin/mv", argv);
    while((wait(&status)) > 0);
}
```
The format of this loop is not really different with the previous loop. The difference is only the parameter of the `argv`. The option `-T` is to move all the files inside the old folder to the new folder.

All of the 3 folders need to be zipped and named as `Lopyu_Stevany.zip`.
```c
char *zipFolder[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Pyoto", "Musyik", "Fylm", NULL};
execv("/usr/bin/zip", zipFolder);
```
The option `-r` is to make the zip command runs recursively and the option `-m` is to delete the folders that have been zipped. The next parameter is the name of the zipped file and the last 3 parameters is the folders name that are going to be zipped.

Downloading, unzipping, and renaming the files 6 hours before Stevany's birthday can be programmed with `time.h` library.
We need to declare it in our code first before using it.
```c
time_t t = time(NULL);
struct tm tm = *localtime(&t);

int day = tm.tm_mday;
int month = tm.tm_mon + 1;
int hour = tm.tm_hour;
int minute = tm.tm_min;
int second = tm.tm_sec;
```
Make an `if` condition preceeding download loop, unzip loop, and rename loop with the condition as 9 April 16.22 WIB because we need to do it 6 hours before her birthday and an `else if` condition for zipping process.
```c
if(day == 9 && month == 4 && hour == 16 && minute == 22 && second == 0)
    download_loop;
    unzip_loop;
    rename_loop;

else if(day == 9 && month == 4 && hour == 22 && minute == 22 && second == 0)
    zip_process;
```
This program will run in the background because of daemon and it will execute when the time is exactly the same with the `if` and `else if` condition.

### **NUMBER 2**
**A. Extract zip files and remove all unnecessary folder**</br>
First we need to have directory "/home/[user]/modul2/petshop" then we have to unzip the pets.zip then remove all unnecessary folder.
```c
int status;
    
    //soal a
    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid == 0) {
        char *linuxcommand[] = {"unzip", "pets", "*.jpg", "-d", "/home/hilmythoriq/modul2/petshop",NULL}; //unzip only jpg files
        execv("/usr/bin/unzip", linuxcommand); //execute unzip command
    }
   ```
  To remove the unnecessary folder we just to unzip only the jpg files using ``*.jpg``</br>
  
**B. Make folder based on all the pets identity**</br>
To save all the pets identity we use 
```c
while(wait(&status) > 0);
    DIR *dirp;
    struct dirent *entry;
    dirp = opendir("/home/hilmythoriq/modul2/petshop");
    char foldername[100][300];
    int idx = 0;
    while((entry = readdir(dirp)) != NULL) //Return name for the next directory
    { 
        if(entry->d_type == DT_REG) 
        {
            char tmp[300], name1[300];
            memset(foldername[idx], 0, sizeof(foldername[idx]));
            memset(name1, 0, sizeof(name1));
            strcpy(tmp, entry->d_name);
            
            int i, found = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                name1[i] = tmp[i];
            } // if find ";" save all before ";"
            
            for(i = 0; i < idx && found == 0; i++)
                if(strcmp(foldername[i], name1) == 0)
                    found = 1;
            
            if(found == 0) {
                strcpy(foldername[idx], name1);
                idx++;
            }
        }
    }
```
   To find the pets identity we find until we found the `;` word then save the pets identity in the foldername array.</br>
   Next we want to make the folder with looping the foldername array.
   ```c
   int i;
    for(i = 0; i < idx; i++) {
        pid_t cid;
        cid = fork();
        if(cid < 0) exit(0);
        if(cid == 0) {
            char tmp[300];
            sprintf(tmp, "/home/hilmythoriq/modul2/petshop/%s", foldername[i]);
            char *linuxcommand[] = {"mkdir", tmp, NULL}; //make new directory using mkdir
            execv("/bin/mkdir", linuxcommand); //execute mkdir command
        }
    }
```

</br>**C. Move all the pets file to their identity folders and rename it only the name.jpg**</br>
First we want to save all the name, identity and the umur of all the pets. To find it we use this.
```c
while(wait(&status) > 0);
    DIR *dirp2;
    struct dirent *entry2;
    dirp2 = opendir("/home/hilmythoriq/modul2/petshop");
    while((entry2 = readdir(dirp2)) != NULL) {
        if(entry2->d_type == DT_REG) {
            char tmp[300];
            char name1_jenis[300], name1_nama[300], name1_umur[300];
            char name2_jenis[300], name2_nama[300], name2_umur[300];
            memset(name1_jenis, 0, sizeof(name1_jenis));
            memset(name1_nama , 0, sizeof(name1_nama));
            memset(name1_umur , 0, sizeof(name1_umur));
            memset(name2_jenis, 0, sizeof(name2_jenis));
            memset(name2_nama , 0, sizeof(name2_nama));
            memset(name2_umur , 0, sizeof(name2_umur));
            strcpy(tmp, entry2->d_name);
            
            int i, ii, found = 0, adadua = 0;
            for(i = 0; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                name1_jenis[i] = tmp[i];
            }
            
            i++; ii = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == ';') break;
                name1_nama[i-ii] = tmp[i];
            }
            
            i++; ii = i;
            for(; i < strlen(tmp); i++) {
                if(tmp[i] == '_' || (tmp[i] == '.' && tmp[i+1] == 'j')) break;
                name1_umur[i-ii] = tmp[i];
            }
```
To check the identity we check until we found the first `;` then save the identity to the `name1_jenis` array.</br>
for the nama we check until we found the second `;` then save the nama to the `name1_nama`array.</br>
the last we check until we found `_` or `.` and `j` because when we have only 1 pet in 1 jpg files we check until got the `.` and `j` but for 2 pets in 1 jpg we save the first umur when we found `_`.</br>

And for move all the pets and rename it we use this.
```c
int status;
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char asal[300], tujuan[300];
                sprintf(asal, "/home/hilmythoriq/modul2/petshop/%s", entry2->d_name);
                sprintf(tujuan, "/home/hilmythoriq/modul2/petshop/%s/%s.jpg", name1_jenis, name1_nama);
                char *linuxcommand[] = {"cp", "-r", asal, tujuan, NULL}; //copy all pets base on the identity
                execv("/bin/cp", linuxcommand);//execute copy command
            }
```

</br>**D. Move all the pets into each of their pets identity if there is 2 pets in 1 jpg**   
Because we already save and move the first pet into its pets identity folder. Here we only need to find the nama, umur, and jenis for the second pet.
```c
if(tmp[i] == '_') {
                i++; ii = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    name2_jenis[i-ii] = tmp[i];
                }
                
                i++; ii = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == ';') break;
                    name2_nama[i-ii] = tmp[i];
                }
                
                i++; ii = i;
                for(; i < strlen(tmp); i++) {
                    if(tmp[i] == '.' && tmp[i+1] == 'j') break;
                    name2_umur[i-ii] = tmp[i];
                }
                
                adadua = 1;
            }
```
we use `if(tmp[i] == '_')` because the second pet information start after the `_` word. then we check until the first `;` to save the identity to `name2_jenis`array and then check until the second `;` to save the nama to `name2_nama` array and finally check until `.` and `j` to save umur to `name2_umur`. To make mark if the jpg files got 2 pets we count it using `adadua = 1`</br>
Then we want to move the jpg to its identity we use.</br>
```c
if(adadua == 1) {
                pid_t cid;
                cid = fork();
                if(cid < 0) exit(0);
                if(cid == 0) {
                    char asal[300], tujuan[300];
                    sprintf(asal, "/home/hilmythoriq/modul2/petshop/%s", entry2->d_name);
                    sprintf(tujuan, "/home/hilmythoriq/modul2/petshop/%s/%s.jpg", name2_jenis, name2_nama);
                    char *linuxcommand[] = {"cp", "-r", asal, tujuan, NULL}; //copy all jpg base on the pets identity
                    execv("/bin/cp", linuxcommand); //execute copy command
                }
```

</br>**E. Write all the nama and umur into Keterangan.txt**</br>
To write all the nama and umur we write it after moving the jpg files.</br>
for the first pet we use.
```c
while(wait(&status) > 0);
            char ket[300];
            sprintf(ket, "/home/hilmythoriq/modul2/petshop/%s/keterangan.txt", name1_jenis);
            FILE *filep;
            filep = fopen(ket, "a+");
           
            fprintf(filep, "nama : %s\n", name1_nama);
            fprintf(filep, "umur : %s tahun\n\n", name1_umur);
            fclose(filep);
```
and for the second pets we just need to change the array
```c
while(wait(&status) > 0);
                char ket[300];
                sprintf(ket, "/home/hilmythoriq/modul2/petshop/%s/keterangan.txt", name2_jenis);
               
                FILE *filep;
                filep = fopen(ket, "a+");
                
                fprintf(filep, "nama : %s\n", name2_nama);
                fprintf(filep, "umur : %s tahun\n\n", name2_umur);
                fclose(filep);
```
</br>**Additional**</br>
because we only move the jpg files using `cp` command so we need to delete all the jpg files that not been moved to the folder so we use 
```c
while(wait(&status) > 0);
    DIR *dirp3;
    struct dirent *entry3;
    dirp3 = opendir("/home/hilmythoriq/modul2/petshop");
    while((entry3 = readdir(dirp3)) != NULL) {
        if((entry3->d_type == DT_REG) && strcmp(entry3->d_name, ".") != 0 && strcmp(entry3->d_name, "..") != 0) {
            pid_t cid;
            cid = fork();
            if(cid < 0) exit(0);
            if(cid == 0) {
                char foldername[300];
                sprintf(foldername, "/home/hilmythoriq/modul2/petshop/%s", entry3->d_name);
                char *linuxcommand[] = {"rm", "-r", foldername, NULL};
                execv("/bin/rm", linuxcommand);}}
```                     

    
	

### **Number 3**
**A. we need to make a file directory every 40 seconds and make the name of the file is the same as the timestamp**</br>

First we make the execv of both the timestamp and the `mkdir` for the file directory creation. To use the timestamp, we use `strftime` function and `localtime` as the time given.
 ```c
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
```

Then to make the file creation executed everytime, we use the `while(1)` to make the `Direct` function running every 40 second, the followed by `sleep(40)`
 
 ```c
 while(1)
{
int a = Direct();
if (a == 10)
{
sleep(40);
}
}
 ```

**B. For all the directory that has been created, they will download 10 images from "https://picsum.photos/", where each image is downloaded every 5 seconds. Then the file named will be after the timestamp and given the size (n% 1000) + 50 pixels where n is Unix Epoch seconds**</br>

First, use the child process of the previous program. After that iterate ten times in the child and call `Download` function and pass the file name. Then, use `sleep(5)` to make the program run for every 5 seconds.

```c
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
 ```

In the `Download` function, break the function into two process. The first one is for the timestamp using `strftime`. Then set `path` for the images to be filled into the file directory. Before that set the size with `SIZE = (((int)t)%1000)+50`. to get the images we use `sprintf(url, "https://picsum.photos/%d/%d", SIZE, SIZE);`. For the second process we execv the `url` using `wget` and also set the `kill` process

```c
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
```

**C. The directory has been filled with 10 images, create a file "status.txt", which contains the message "Download Success" which is encrypted with the Caesar Cipher technique and with shift 5. After the file is created, zip the directory file and delete the directory leaving a zip file**</br>

First we continue the previous `Direct` function. After the download process ends, encrypt the download success message that will be done by `Chiper` function. Make `status.txt` by using `TXT` function. To zip it all the process that had been done, call `ZIP` function. Finally kill the process.
In `Cipher`, every message slide every `key` that available. If the word exceeded `z`, it will slide from `a`.
In `TXT` function, make `path` that filled with with file directory and `status.txt` that already been encrypted.
In `ZIP` function, zip all the progress. To erase the zipped file use `-m` argument.

```c
else if(anak_id3 > 0 && wait(&status) > 0)
{
char message[20] = {"Download Success"};
int key = 5;
Cipher(message, key);
TXT(message, tanggalD);
ZIP(tanggalD);
}
kill(getpid(),SIGTERM);
```

```c
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
```

```c
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
```

```c
void ZIP(char tanggalD[])
{
char *argv[] = {"zip", "-r" , "-m", tanggalD, tanggalD, NULL};
  execv("/bin/zip", argv);
}
```

**D and E. When the program is run, the program will generate a killer program in the form of an executable bash program, and after the killer program is run, the killer program will delete itself. If the program is run using the -z argument, if the killer program is executed, all processes that are being carried out by the program will stop immediately. However, if the program is run using the -x argument, the program will stop but will complete the process in the directory that was created**</br>

In `Killer` function, split the process into two. The child will make `killer.sh` file. If `-z` is the argument, the `killer.sh` will fill in a command to kill all the process that being run with `io3`. After killing, delete the `killer.sh` with `rm` command. If its `-x` argument, it will kill the child process. 
In parent of `Killer` function, make the `killer.sh` could be run by using `chmod` with `+x` argument.

```c
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
```

In the main, call `Killer` function by passing the the `PID` from the main child.

```c
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
 ```
	

