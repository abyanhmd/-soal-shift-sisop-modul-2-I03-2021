#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<syslog.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<wait.h>
#include<dirent.h>

int main() {
    int status;
    
    //soal a
    pid_t cid;
    cid = fork();
    if(cid < 0) exit(0);
    if(cid == 0) {
        char *linuxcommand[] = {"unzip", "pets", "*.jpg", "-d", "/home/hilmythoriq/modul2/petshop",NULL}; //unzip only jpg files
        execv("/usr/bin/unzip", linuxcommand); //execute unzip command
    }
   
    //soal b save all pets identity to foldername[]
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
    
    //soal c save the pets name , umur, jenis
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
            
            //soal d save the other name and umur if the 1 jpg got 2 pets
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
            //akhir soal d Copy pets jpg to folder base on the identity and rename it
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
            
            
            //soal e Write all the pets name into keterangan.txt for each pets identity folder
            while(wait(&status) > 0);
            char ket[300];
            sprintf(ket, "/home/hilmythoriq/modul2/petshop/%s/keterangan.txt", name1_jenis);
            FILE *filep;
            filep = fopen(ket, "a+");
           
            fprintf(filep, "nama : %s\n", name1_nama);
            fprintf(filep, "umur : %s tahun\n\n", name1_umur);
            fclose(filep);
            
            //akhir soal e
            
            //soal d copy the other 2 pets in 1 jpg to make it 2 jpg
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
                
                //soal e Write to keterangan.txt for the 2 pets in 1 jpg 
               
                while(wait(&status) > 0);
                char ket[300];
                sprintf(ket, "/home/hilmythoriq/modul2/petshop/%s/keterangan.txt", name2_jenis);
               
                FILE *filep;
                filep = fopen(ket, "a+");
                
                fprintf(filep, "nama : %s\n", name2_nama);
                fprintf(filep, "umur : %s tahun\n\n", name2_umur);
                fclose(filep);
                
                //akhir soal e
            }
            //akhir soal d
        }
    }
    //remove all jpg that have been moved
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
                execv("/bin/rm", linuxcommand);
}
}
}
}
