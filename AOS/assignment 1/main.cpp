#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<limits.h>
#include<bits/stdc++.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <stdint.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdlib.h>
#include <termios.h>
#include<cstring>
#include<filesystem>
#include<exception>
#include<fstream>
 #include <fcntl.h>
#include <cstdio>
 
 
using namespace std;


struct termios saved_attributes;

  stack<char*> stBack;
    stack<char*> stFrwd;
    char* here;
    char* home;

int normal_mode(char* tmp);
int isRelative(char *givenPath);
int deleteFile(char* tmp);

void
reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void
set_input_mode (void)
{
  struct termios tattr;
  char *name;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}


char const * sperm(__mode_t mode) {
    static char local_buff[16] = {0};
    int i = 0;
    // user permissions
    if ((mode & S_IRUSR) == S_IRUSR) local_buff[i] = 'r';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IWUSR) == S_IWUSR) local_buff[i] = 'w';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IXUSR) == S_IXUSR) local_buff[i] = 'x';
    else local_buff[i] = '-';
    i++;
    // group permissions
    if ((mode & S_IRGRP) == S_IRGRP) local_buff[i] = 'r';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IWGRP) == S_IWGRP) local_buff[i] = 'w';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IXGRP) == S_IXGRP) local_buff[i] = 'x';
    else local_buff[i] = '-';
    i++;
    // other permissions
    if ((mode & S_IROTH) == S_IROTH) local_buff[i] = 'r';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IWOTH) == S_IWOTH) local_buff[i] = 'w';
    else local_buff[i] = '-';
    i++;
    if ((mode & S_IXOTH) == S_IXOTH) local_buff[i] = 'x';
    else local_buff[i] = '-';
    return local_buff;
}

void help(char* tmp,int start,int end)
{

struct dirent  *dp;
struct stat     statbuf;
struct passwd  *pwd;
struct group   *grp;
struct tm      *tm;
char            datestring[256];
DIR *dir;
 cout << "\033[H\033[2J\033[3J" ;        // clear screen


// set cursor to 0,0
//printf("\033[%d;%dH",0,0);


int i=1;
 
   // start=i;
if ((dir = opendir (tmp)) != NULL) {
/* Loop through directory entries. */

while ((dp = readdir(dir)) != NULL && start<=end) {
     
   if(i>=start){
   
  // printf("%d ",i);
    /* Get entry's information. */
   // if (stat(dp->d_name, &statbuf) == -1)
   //     continue;
   stat(dp->d_name, &statbuf);
       start++;
       
      printf("%-25.20s ",dp->d_name);
   
   
   
    /* Print out type, permissions, and number of links. */
  //  if(dp->d_type==DT_REG)
   // printf("-");
  //  else
  //  printf("d");
   
     if(dp->d_type==DT_REG)
    printf("-%10s ", sperm (statbuf.st_mode));
    else
    printf("d%10s ", sperm (statbuf.st_mode));
   // printf("%4d", statbuf.st_nlink);


    /* Print out owner's name if it is found using getpwuid(). */
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
        printf(" %-8.8s ", pwd->pw_name);
    else
        printf(" %-8d ", statbuf.st_uid);


    /* Print out group name if it is found using getgrgid(). */
    if ((grp = getgrgid(statbuf.st_gid)) != NULL)
        printf(" %-8.8s ", grp->gr_name);
    else
        printf(" %-8d ", statbuf.st_gid);


    /* Print size of file. */
    printf(" %9jd Bytes     ", (intmax_t)statbuf.st_size);


    tm = localtime(&statbuf.st_mtime);


    /* Get localized date string. */
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);


    printf(" %s \n", datestring);
    }
    i++;
}



}



}




struct dirent * getPtrToFile(char *tmp,int index)
{
 // getting files and directories and storing them into vectors
int i=0;
DIR *dir;
struct dirent *ent;

if ((dir = opendir (tmp)) != NULL) {
 
  while ((ent = readdir (dir)) != NULL )  {
   
     i++;
     if(i==index)
     break;
      
   
  }
  
  return ent;
  closedir (dir);
} else {

  perror ("");
  return NULL;
}
return NULL;
}


int commandToInt(char *token)
{
    string s="";
    for(int i=0;i<256;i++)
    {
        if(token[i]=='\0')
        break;
        s=s+token[i];
       
    }
    string commArr[9]={"copy","move","rename","create_file","create_dir","delete_file",
                         "delete_dir","goto","search"};
           for(int i=0;i<9;i++)
           {
             
            // cout<<"\n"<<commArr[i]<<" "<<s;
              if(commArr[i].compare(s)==0)
              return i;
           }
           
           return 100;

}


void set_command_mode(){
 printf("\033[%d;%dH",20,0);
 printf("Command mode activated : enter your commands below : \n"); 
 printf("\033[%d;%dH",21,0);

}

void copyFile(char *src_path, char* dst_path,bool var)
{
     int src_fd, dst_fd, n, err;
    unsigned char buffer[4096];
  //  char * src_path, dst_path;

    // Assume that the program takes two arguments the source path followed
    // by the destination path.

  

   // src_path = src;
   // dst_path = dest;

    src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_CREAT | O_WRONLY);
    
   // cout<<src_path<<"\n";
   // cout<<dst_path<<"\n";

    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    }

    close(src_fd);
    close(dst_fd);
}


void deleteDirectory(char* dirPath)
{
    // printf("directory to be deleted is %s\n", dirPath.c_str());
   // cout<<dirPath<<"\n";
    DIR *d = opendir(dirPath);
    if (d)
    {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL)
        {
            
            if (strcmp(dir->d_name, ".")==0 || strcmp(dir->d_name, "..")==0){
        
             }
            else
            {
                string s1(dirPath);
                string s2(dir->d_name);
                string s3=s1+"/"+s2;
              //  cout<<s3<<"\n";
                 int len1=s3.length();
                char arr1[len1+1];
              strcpy(arr1,s3.c_str());
                struct stat st;

                if (stat(arr1, &st) == -1)
                {
                    cout << "error can't open directory\n";
                    return;
                }
                if (S_ISDIR(st.st_mode))
                {
                   

                    deleteDirectory(arr1);
                }
                else
                {
                   // printf("file currently to be deleted is %s\n", path.c_str());

                     deleteFile(arr1);
                }
            }
        }
        closedir(d);
        int ret = rmdir(dirPath);
        if (ret == -1)
        {
            cout << "error, cant remove directory name\n";
        }
    }
    else
    {
        cout << "error,cant open dir\n";
    }
}



int search(char* dirPath,char* fileName)
{
    // printf("directory to be deleted is %s\n", dirPath.c_str());
  // cout<<dirPath<<"\n";
    DIR *d = opendir(dirPath);
    if (d)
    {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL)
        {
            
            if (strcmp(dir->d_name, ".")==0 || strcmp(dir->d_name, "..")==0){
        
             }
            else
            {
                string s1(dirPath);
                string s2(dir->d_name);
                string s3=s1+"/"+s2;
                string s4(fileName);
              //  cout<<s3<<"\n";
                 int len1=s3.length();
                char arr1[len1+1];
              strcpy(arr1,s3.c_str());
                struct stat st;

                if (stat(arr1, &st) == -1)
                {
                    cout << "error can't open directory\n";
                    return 0; 
                }
                
                 if(s2==s4)
                    return 1;
                if (S_ISDIR(st.st_mode))
                {
                  
                    if(search(arr1,fileName))
                    return 1;
                }
           //     else
            //    {
                   // printf("file currently to be deleted is %s\n", path.c_str());

            //         deleteFile(arr1);
            //    }
            }
        }
        closedir(d);
       
    }
    else
    {
        cout << "error,cant open dir\n";
    }
    
    return 0;
}



void copyPermission(char* first,char* second){
struct stat st;
stat(first,&st);
chmod(second,st.st_mode);
}

void copyDirectory(char* source,char* dest)
{
    DIR *d;
    struct dirent *dir;
    int ret = mkdir(dest,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    d=opendir(source);
    if (d==NULL)
    {
        cout << "wrong location\n";
        return;
    }
    while ((dir=readdir(d)) != NULL)
    {
   // cout<<dir->d_name<<"\n";
        if (strcmp(dir->d_name, ".")==0 || strcmp(dir->d_name, "..")==0){
        
        }
            
        else
        {
           
            string s1(source);
            string s2(dest);
            string s3(dir->d_name);
            s1=s1+"/"+s3;
            s2=s2+"/"+s3;
            
            int len1=s1.length();
             char arr1[len1+1];
              strcpy(arr1,s1.c_str());
              
              int len2=s2.length();
             char arr2[len2+1];
              strcpy(arr2,s2.c_str());
            
         //   cout<<s1<<"\n";
         //    cout<<s2<<"\n";
           
            struct stat st;
            if (stat(arr1, &st)==-1)
            {
                cout << "error invalid file /directory";
                return;
            }

            if (S_ISDIR(st.st_mode))
            {
              
                
                copyDirectory(arr1,arr2);
                copyPermission(arr1,arr2);
            }
            else
            {
             
            
              
               ifstream file ;
                file.open(arr2);
                  copyFile(arr1,arr2,true);
                 copyPermission(arr1,arr2);
                file.close();
          
            }
        }
    }
   
}

void copyDirHelper(char* fileName,char* destPath,char* tmp){
    //  cout<<"here\n";
    cout<<"copy directory helper\n";
         if(isRelative(destPath))
         {
         
         cout<<"relative\n";
         string s(tmp);
        // cout<<s<<"\n";
         string s1(fileName);
          string s2(destPath);
          int pos=s2.find("~");
          
          s2=s+s2.substr(pos+1)+"/"+s1;
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
          
          
         s1=s+"/"+s1;
         int len1=s1.length();
         char arr1[len1];
          strcpy(arr1,s1.c_str());
          
          copyDirectory(arr1,arr2);
            
             
         }
        
        else{
        
         string s(tmp);
         string s1(fileName);
          string s2(destPath);
          s2=s2+"/"+s1;
          s1=s+"/"+s1;
          
        
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
             int len1=s1.length();
         char arr1[len1];
          strcpy(arr1,s1.c_str());
            
            copyDirectory(arr1,arr2);
     
       }
      
      
     
       


}


void copyFileHelper(char* fileName,char* destPath,char* tmp)
{

  
         
         if(isRelative(destPath))
         {
         
        // cout<<"yes\n";
         string s(tmp);
        // cout<<s<<"\n";
         string s1(fileName);
          string s2(destPath);
          int pos=s2.find("~");
          
          s2=s+s2.substr(pos+1)+"/"+s1;
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
          
          
         s1=s+"/"+s1;
         int len1=s1.length();
         char arr1[len1];
        // cout<<s1<<"\n";
        // cout<<s2<<"\n";
          strcpy(arr1,s1.c_str());
           ifstream file ;
        file.open(arr2);
         
       copyFile(arr1,arr2,true);
       copyPermission(arr1,arr2);
       file.close();
          
            
             
         }
         // /home/rishu/Desktop/q2.sh
         // /home/rishu/Desktop/assign
        // char *var1="/home/rishu/Desktop/q2.sh";
        // char *var2="/home/rishu/Desktop/assign";
        // cout<<"hua copy ya nhi : "<<copyFile(fileName,destPath)<<"\n";
        else{
        
         string s(tmp);
         string s1(fileName);
          string s2(destPath);
          s2=s2+"/"+s1;
          s1=s+"/"+s1;
          
        //  cout<<s1<<"\n";
        //  cout<<s2<<"\n";
         
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
             int len1=s1.length();
         char arr1[len1];
          strcpy(arr1,s1.c_str());
            
            
        ifstream file ;
        file.open(arr2);
         
       copyFile(arr1,arr2,true);
       copyPermission(arr1,arr2);
       file.close();
       }
      
      
         //copy /home/rishu/Desktop/hamlet.txt /home/rishu/Desktop/assign/hamlet.txt
         
       

}



void moveFileHelper(char* fileName,char* destPath,char* tmp){

 if(isRelative(destPath))
         {
         
        // cout<<"yes\n";
         string s(tmp);
        // cout<<s<<"\n";
         string s1(fileName);
          string s2(destPath);
          int pos=s2.find("~");
          
          s2=s+s2.substr(pos+1)+"/"+s1;
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
          
          
         s1=s+"/"+s1;
         int len1=s1.length();
         char arr1[len1];
        // cout<<s1<<"\n";
        // cout<<s2<<"\n";
          strcpy(arr1,s1.c_str());
        //   ifstream file ;
       // file.open(arr2);
         
       //copyFile(arr1,arr2,true);
      // copyPermission(arr1,arr2);
      // file.close();
      
       ifstream file ;
        file.open(arr2);
       copyFile(arr1,arr2,true);
       copyPermission(arr1,arr2);
       file.close();
       deleteFile(arr1);
          
            
             
         }
         else{
         
          string s(tmp);
         string s1(fileName);
          string s2(destPath);
          s2=s2+"/"+s1;
          s1=s+"/"+s1;
          
        //  cout<<s1<<"\n";
        //  cout<<s2<<"\n";
         
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
             int len1=s1.length();
         char arr1[len1];
          strcpy(arr1,s1.c_str());
          
           ifstream file ;
        file.open(arr2);
       copyFile(arr1,arr2,true);
       copyPermission(arr1,arr2);
       file.close();
       deleteFile(arr1);
         
         }


}



void moveDirHelper(char* fileName,char* destPath,char* tmp){

 if(isRelative(destPath))
         {
         
        // cout<<"yes\n";
         string s(tmp);
        // cout<<s<<"\n";
         string s1(fileName);
          string s2(destPath);
          int pos=s2.find("~");
          
          s2=s+s2.substr(pos+1)+"/"+s1;
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
          
          
         s1=s+"/"+s1;
         int len1=s1.length();
         char arr1[len1];
       //  cout<<s1<<"\n";
       //  cout<<s2<<"\n";
          strcpy(arr1,s1.c_str());
        //   ifstream file ;
       // file.open(arr2);
         
       //copyFile(arr1,arr2,true);
      // copyPermission(arr1,arr2);
      // file.close();
      
      
      
      copyDirectory(arr1,arr2);
      deleteDirectory(arr1);
    
          
            
             
         }
         else{
         
          string s(tmp);
         string s1(fileName);
          string s2(destPath);
          s2=s2+"/"+s1;
          s1=s+"/"+s1;
          
       //  cout<<s1<<"\n";
       //   cout<<s2<<"\n";
         
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
             int len1=s1.length();
         char arr1[len1];
          strcpy(arr1,s1.c_str());
          
          copyDirectory(arr1,arr2);
            deleteDirectory(arr1);
    
         
         }


}

int deleteFile(char* tmp)
{
   return remove(tmp);
}


int checkDirectory(char* fileName,char* destPath,char* tmp)
{
 // cout<<"sona\n";
    
   //   cout<<"maa\n";
         string s(tmp);
         string s1(fileName);
          string s2(destPath);
          int pos=s2.find("~");
          
          s2=s+s2.substr(pos+1)+"/"+s1;
          s1=s+"/"+s1;
      //    cout<<s1<<"\n";
          int len1=s1.length();
          char arr1[len1];
            strcpy(arr1,s1.c_str());
        //  cout<<"papa\n";
        struct stat st;
        stat(arr1, &st);
        if ((S_ISDIR(st.st_mode))){
         //   cout<<"rishu\n";
            return 1;
            }
        else{
       // cout<<"file\n";
            return 0;
            }
          
            
             
         
        
     
}

int isRelative(char *givenPath)
{
   if(givenPath[0]=='~')
   return 1;
   else
   return 0;
}


void enter_command_mode(char* tmp,int start,int end){

set_command_mode();
string str="";
//cout<<str;
int marker=1;
while(marker)
{
    char c;
    c=cin.get();
    if(c==27)
       break;
       
     if(c==127)    // press backspace
        {
          help(tmp,start,end);
          set_command_mode();
          if(str.size()>0)
            str.pop_back();
            cout<<str;
        }
     else if(c==10){      // enter command
       int n=str.length();
       char command[n+1];
       strcpy(command,str.c_str());
       char *token=strtok(command," ");  
       int num=commandToInt(token);
   //    cout<<"\n idhr : "<<tmp<<"\n";
   //  cout<<num<<"\n";
       str="";
      help(tmp,start,end);
       set_command_mode();
       
  
      if(num==0)    // copy
      {
        // cout<<"copy command\n";
         char* fileName=strtok(NULL," ");
         char* destPath=strtok(NULL," ");
         
         if(checkDirectory(fileName,destPath,tmp))
         {
       //   cout<<"copy directory \n";
          copyDirHelper(fileName,destPath,tmp);
         }
         else{
        // cout<<"copy File \n";
        copyFileHelper(fileName,destPath,tmp);
        }
       
       }
         
      
      else if(num==1)  //move   
      {
        char* fileName=strtok(NULL," ");
         char* destPath=strtok(NULL," ");
         
           if(checkDirectory(fileName,destPath,tmp))
         {
         // cout<<"move directory \n";
         moveDirHelper(fileName,destPath,tmp);
         }
         else{
        // cout<<"move File \n";
           moveFileHelper(fileName,destPath,tmp);
        }
         
          
          
       //move /home/rishu/Desktop/hamlet.txt /home/rishu/Desktop/temp_activity/hamlet.txt
      }
      else if(num==2)  // rename  
      {
         char* oldName=strtok(NULL," ");
         char* newName=strtok(NULL," ");
         string s(tmp);
         string s1(oldName);
          string s2(newName);
          s1=s+"/"+s1;
          s2=s+"/"+s2;
          
        //  cout<<s1<<"\n";
        //  cout<<s2<<"\n";
          
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
            
             int len1=s1.length();
         char arr1[len1];
          strcpy(arr1,s1.c_str());
          int val=rename(arr1,arr2);
         
         
       //rename /home/rishu/Desktop/hamlet.txt /home/rishu/Desktop/amar_hai_hum.txt
      }
      else if(num==3)    // create_file  
      {
         char* fileName=strtok(NULL," ");
         char* destPath=strtok(NULL," ");
          if(isRelative(destPath))
         {
         
       
         string s(tmp);
         string s1(fileName);
          string s2(destPath);
          int pos=s2.find("~");
          
          s2=s+s2.substr(pos+1)+"/"+s1;
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
          
          
         s1=s+"/"+s1;
         int len1=s1.length();
         char arr1[len1];
        
          strcpy(arr1,s1.c_str());
          
         // cout<<s1<<"\n";
         // cout<<s2<<"\n";
          
           ofstream file;
           file.open(s2);
           file.close();
          }
      
      else{
      
          string s(tmp);
         string s1(fileName);
          string s2(destPath);
          s2=s2+"/"+s1;
        
      
       
        // cout<<s2<<"\n";
          

         ofstream file;
         file.open(s2);
         file.close();
         
     //   cout<<"rishu toshniwal\n";
        }
         //exit(0);
      }
      else if(num==4)    // create_dir
      {
           char* fileName=strtok(NULL," ");
         char* destPath=strtok(NULL," ");
      
            if(isRelative(destPath))
         {
         
       
         string s(tmp);
         string s1(fileName);
          string s2(destPath);
           int pos=s2.find("~");
            s2=s+s2.substr(pos+1)+"/"+s1;
          int len2=s2.length();
          char arr2[len2];
            strcpy(arr2,s2.c_str());
            
          mkdir(arr2,0777);
         
          }
          else{
       
          string s1(fileName);
          string s2(destPath);
          s2=s2+"/"+s1;
           int n=s1.length();
           char path[n+1];
           strcpy(path,s2.c_str());
           int check=mkdir(path,0777);
           }
           //cout<<path<<"\n";
           //if(check==-1)
          // cout<<"ban nhi paya\n";
           //else
           //cout<<"ban gyi directory\n";
           
           
           
      }
      else if(num==5)   //delete file 
      {
        char* filePath=strtok(NULL," ");
        if(isRelative(filePath))
        {
         string s(tmp);
         string s1(filePath);
          int pos=s1.find("~");
          s1=s+s1.substr(pos+1);
          int len1=s1.length();
          char arr1[len1];
            strcpy(arr1,s1.c_str());
            deleteFile(arr1);
        }
        else
         deleteFile(filePath);
      }
      else if(num==6)  //delete directory   
      {
           char* filePath=strtok(NULL," ");
           if(isRelative(filePath))
           {
           string s(tmp);
           string s1(filePath);
          int pos=s1.find("~");
          s1=s+s1.substr(pos+1);
          int len1=s1.length();
          char arr1[len1];
            strcpy(arr1,s1.c_str());
           deleteDirectory(arr1);
        }
        else{
       // cout<<"sona\n";
         deleteDirectory(filePath);
         }
      }
      else if(num==7)   // go to  
      {
        //  char* fileName=strtok(NULL," ");
        //  char* first=fileName;
        // string name(fileName);
        //  while(fileName!=NULL)
        //  {
        //    fileName=strtok(NULL," ");
        //    if(fileName!=NULL){
        //     string s(fileName);
        //     name=name+" "+s;
        //    }
             
         //}
        
        // if(isRelative(first)){
        //cout<<"hi hello\n";
           //  string s(tmp);
           //  int pos=name.find("~");
           //   name=s+name.substr(pos+1);
           //    int len1=name.length();
           // char arr1[len1];
          //  strcpy(arr1,name.c_str());
         //  cout<<arr1<<"\n";
         //   tmp=arr1;
         //   here=arr1;
         //   while(stBack.size()!=0)
          //     stBack.pop();
          //     while(stFrwd.size()!=0)
          //     stFrwd.pop();
              // start=1;
              // end=5;
          //     normal_mode(tmp);
               
           //  help(tmp,start,end);
           //  set_command_mode();
         
         //}
         //else{
        // cout<<name<<"\n";
        //  int len1=name.length();
        //    char arr1[len1];
        //    strcpy(arr1,name.c_str());
        //    tmp=arr1;
        //    here=arr1;
          //  cout<<arr1<<"\n";
        //    while(stBack.size()!=0)
        //       stBack.pop();
        //       while(stFrwd.size()!=0)
        //       stFrwd.pop();
              // start=1;
              // end=5;
        //    normal_mode(tmp);
           //  help(tmp,start,end);
         // set_command_mode();
         //}
     // cout<<name<<"\n";
         
        
      }
      
       else if(num==8)   // search  
      {
        //  cout<<"rishu\n";
        
         char* fileName=strtok(NULL," ");
         string name(fileName);
         while(fileName!=NULL)
         {
            fileName=strtok(NULL," ");
            if(fileName!=NULL){
             string s(fileName);
             name=name+" "+s;
             }
             
         }
      //   cout<<name<<"\n";
         
         
      }
      else{
      cout<<"wrong command\n";
      }
     
     }
     else if(c=='q')
     {
         exit(0);
     }
     else if(c==27)
     {
        return;
     }
    else{
    str=str+c;
    cout<<c;
    }

}

}



void enable_scrolling(char* tmp,int start,int end,int total)
{
char c;
   const int ESC=27;
  set_input_mode ();
  // set cursor to 0,0
printf("\033[%d;%dH",1,0);   
int x=1;
int y=0;


 while (1)
    {
        fflush(stdin);
        char inp[3];
        inp[0] = cin.get();
        
         if (inp[0] == 27) // arrow keys or any ctrl key is pressed
        {
            inp[1] = cin.get();
            inp[2] = cin.get();
            
            if (inp[2] == 'A' || inp[0] == 107 || inp[0] == 75) // arrow key upward
            {
                 if(x>1){
                x--;
                printf("\033[%d;%dH",x,y); 
                }
                
            }
            
            
            
             if (inp[2] == 'B' || inp[0] == 108 || inp[0] == 76) //arrow key downward
            {
            
                  if(x<5){
                  x++;
                  printf("\033[%d;%dH",x,y); 
                  }
                  
                 
            }
            
             if (inp[2]=='D') //left arrow key
            {
               if(stBack.size()>0){
                 stFrwd.push(here);
                 here=stBack.top();
                 stBack.pop();
                   normal_mode(here);
                   }
            } 
            
            
             if (inp[2] == 'C') // right arrow key
             {
               // cout<<"sonam\n";
                if(stFrwd.size()>0){
                // cout<<"rishu\n";
                 stBack.push(here);
                 here=stFrwd.top();
                 stFrwd.pop();
                  normal_mode(here);
                 }
             }
             
        }
         if (inp[0] == 'H' || inp[0] == 'h') // starting directory
        {
             while(stFrwd.size()!=0)
               stFrwd.pop();
               while(stBack.size()!=0)
               stBack.pop(); 
               here=home;
               normal_mode(here);
        }
        
        
        if(inp[0]==127)    // press backspace
        {
           string s1(tmp);
           s1=s1+(string)"/..";
            int n=s1.length();
               char path[n+1];
               strcpy(path,s1.c_str());
               
               
               while(stFrwd.size()!=0)
               stFrwd.pop();
               while(stBack.size()!=0)
               stBack.pop();
               
               stFrwd.push(here);
               here=path;
               normal_mode(here);
               
        }
        
        if(inp[0]==10)
        {
            struct dirent* ent= getPtrToFile(tmp,start+x-1);
            
            // open a file
            if(ent->d_type==DT_REG){
          //   printf(" rishu toshniwal %-20s \n", ent->d_name);
          
            pid_t pid = vfork();
                if (pid == 0) {
              // child process
               char execName[] = "gedit";
               char* newName=ent->d_name;
               string s1(tmp);
               string s2(newName);
               s1=s1+"/"+s2;
               int n=s1.length();
               char path[n+1];
               strcpy(path,s1.c_str());
            //   string newPath=tmp+newName;
               
            //   printf(" rishu toshniwal %-20s \n",newPath);
             //  char path[]="/home/rishu/Desktop/hamlet.txt";
               char *exec_args[] = {execName, path, NULL};
                    execv("/usr/bin/gedit", exec_args);
              }
           }
           
           // open the directory
          if(ent->d_type==DT_DIR){
             char* newName=ent->d_name;
              string s1(tmp);
               string s2(newName);
               s1=s1+"/"+s2;
            // cout<<s1<<"\n";
               int n=s1.length();
               char path[n+1];
               strcpy(path,s1.c_str());
         
               stBack.push(tmp);
               here=path; 
               while(stFrwd.size()!=0)
               stFrwd.pop();
               normal_mode(here);
             
           }
       }

        if (inp[0] == 75 || inp[0] == 107) // read K move down
        {
        
          if(x==5 && end!=total){
          //cout << "\033[H\033[2J\033[3J" ;        // clear screen
          start++;
          end++;
          help(tmp,start,end);
          x=5;
          printf("\033[%d;%dH",x,y); 
         
          
          }
           
        }
        
        
         if (inp[0] == 76 || inp[0] == 108){ // read L move up
             if(x==1 && start!=1){
              //  cout << "\033[H\033[2J\033[3J" ;        // clear screen
                 start--;
                 end--;
                 help(tmp,start,end);
          
                  x=1;
                  printf("\033[%d;%dH",x,y); 
               }
             
         }
         
         if(inp[0]==':')
         {
             enter_command_mode(tmp,start,end);
         }
        
         if (inp[0] == 'q')
        {
            // to get out of char reading mode
            // cout << "\033[H\033[2J\033[3J" ;  
            //  reset_input_mode ();
             cout << "\033[H\033[2J\033[3J" ;        // clear screen
             reset_input_mode();
           exit(0);    
          //  break;
        }
 }
}



void printInitialKFiles(int start,int end, char* tmp,int total){


help(tmp,start,end);
enable_scrolling(tmp,start,end,total);


// cout<<"rishu\n";
//for(int i=0;i<v1.size();i++){
 //struct dirent* temp=v1[i];
// cout<<temp->d_name<<"\n";
// struct stat st;
 //   if(stat(v1[i]->d_name,&st) != 0) {
   
 //       return ;
 //   }
 //    cout<<st.st_size<<"\n";   
//}



//for(int i=0;i<v2.size();i++){
//struct dirent* temp=v2[i];
//cout<<"rishu in Loop 2\n";
 //struct stat st;
    //if(stat(temp->d_name,&st) != 0) {
    //    return ;
   // }
   //  cout<<st.st_size<<"\n";   
//}


 //  while (1)
  //  {
  //    read (STDIN_FILENO, &c, 1);
  //    if (c == ESC)  {        /* C-d */
  //       cout<<"\n";
  //      break;
  //      }
  //    else
  //      putchar (c);
 //   }
    
 // set cursor to 0,0
//printf("\033[%d;%dH",0,0);   
    
    
//cout << "\033[H\033[2J\033[3J" ;        // clear screen


}

int normal_mode(char* tmp)
{

// getting files and directories and storing them into vectors
//vector<struct dirent *> v1;
//vector<struct dirent *> v2;
DIR *dir;
struct dirent *ent;
int total=0;
if ((dir = opendir (tmp)) != NULL) {
 
  while ((ent = readdir (dir)) != NULL) {
   //  printf ("%s\n", ent->d_name);
    
    
   //  struct stat st;
   // if(stat(ent->d_name,&st) != 0) {
   //   cout<<"gadbad yaha h";
   //     return 1;
   // }
    // cout<<ent->d_name<<" "<<st.st_size<<"\n";   
    //cout<<ent<<"\n";
     
   // if(ent->d_type==DT_REG)
   // v1.push_back(ent);
   // else if(ent->d_type==DT_DIR)
   // v2.push_back(ent);
    total++;
  }
  cout<<total<<"\n";
  closedir (dir);
} else {

  perror ("");
  return EXIT_FAILURE;
}


int start=1,end=5;
//cout<<tmp<<"\n";
//cout<<start<<" "<<end<<"\n";
 printInitialKFiles(start,end,tmp,total);


return 1;
}
int main()
{
 
    char tmp[256];
   
    getcwd(tmp,256);
    string s="";
     for(int i=0;i<256;i++)
    {
      
        s=s+tmp[i];
        if(tmp[i]=='\0')
        break;
    }
   // st.push(tmp);
   here=tmp;
   home=tmp;
    normal_mode(here);
       return 0;
}