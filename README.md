## Modul 2 - Group I03 
</br>

### **Number 1**
The problem number 1 is not completed actually. Here are the examplanation of what is already done.
The problem ask to download files from the link that is provided and store them in a new directory called Musyik for mp3, Fylm for mp4, and Pyoto for jpg. </br>
When the time is 6 hours before 22.22 WIB on 9 April, all of the folder that is already been unzipped need to be zipped named Lopyu_Stevany.zip and all of the folder need to be removed. </br>

We are using fork for this problem but it is not running as it should be. For the download,
```c
char *URL[] = {"wget", "--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "/home/Sisop/Modul_2", "-q", NULL};
execv("/usr/bin/wget", URL);
```
The command to download the file is `wget` and make sure there is no certificate checking using `--no-check-certificate`. The third argument is the url of the file, the fourth argument is the path of the download, the fifth argument is `-q` to hide the download log that is happening in the terminal. After that, we need to execute the command using `execv`. </br>

The next step is to unzip the zip file.
```c
char *extract[] = {"unzip", "-q", "uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", NULL};
execv("/usr/bin/unzip", extract);
```
The format is the same and the difference is only the command that is used which is `unzip`. </br>

From what we think of, in order to change the name of the folder, we can use `mv` command to its folder plus the new name.
```c
execl("/usr/bin/mv", "mv", "MUSIK", "Musyik", NULL);
```
The old name is MUSIK and the new name is Musyik.</br>

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


First we make the execv of both the timestamp and the mkdir for the file directory creation
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
Then to make the file creation executed everytime, we use the while(1) to make the Direct function running every 40 second, the followed by sleep(40)
 
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
**B. not understanding yet**</br>
**C. not understanding yet**</br>
**D. not understanding yet**</br>
**E. not understanding yet** </br>

 
 
 
	

