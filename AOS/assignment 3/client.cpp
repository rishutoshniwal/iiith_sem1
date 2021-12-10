#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include<cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include<string>




using namespace std;

string ip,port;
string choice;
int login=0;


int main(int argc,char* arg[])
{

   char* ptr=strtok(arg[1],":");
   string temp1(ptr);
   ptr=strtok(NULL,":");
   string temp2(ptr);
   ip=temp1;
   port=temp2;
   cout<<ip<<" "<<port<<"\n";
   
   
   struct sockaddr_in server_address;
  // pthread_t t;
   
   int use=socket(AF_INET, SOCK_STREAM, 0);
   if(use==-1)
   {
     perror("socket error : ");
     exit(-1);
   }
   
  
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8989);
    
    int n=ip.length();
    char arr[n+1];
    strcpy(arr,ip.c_str());
    
    
    if(inet_pton(AF_INET,arr,&server_address.sin_addr) == -1) 
    {
        printf("Server not found \n");
        exit(-1);
    }
    
    if (connect(use,(struct sockaddr *)&server_address,sizeof(server_address)) == -1)
    {
        printf("\nConnection Failed\n");
        exit(-1);
    }
    
    printf("Client is connected to server\n");
    
    
    char msg[1024];
    while(1)
    {
        bzero(msg,1024);
        scanf("%[^\n]%*c",msg);
        string temp;
       // cout<<msg<<"\n";
        string command(msg);
       // cout<<command<<"\n";
        vector<string> arr;
        stringstream split(command);
        while(getline(split,temp,' ')){
         //  cout<<temp<<"\n";
            arr.push_back(temp);
           }
     // cout<<"here  : ";
      //  ptr=strtok(msg," ");
      //  string first(ptr);
     // cout<<first<<"\n";
     
     
     
         
        
        
        if(arr[0]=="create_user")
        {
           if(login==1)
           {
            printf("You are already logged in\n");
           }
           else{
             //  cout<<"Message before sending : "<<msg<<"\n";
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg;
           }
        }
        else if(arr[0]=="login")
        {
           if(login==1)
           {
            printf("You are already logged in\n");
           }
           else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
                string res(msg);
                if(res=="Login successfull\n"){
             //  printf("test if condition");
                login=1;
                }
             }          
        }
        else if(arr[0]=="create_group")
        {
            if(login==0){
              printf("To create a group you need to login first");
            }
            else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
            }     
                         
        }
        else if(arr[0]=="join_group")
        {
           if(login==0){
              printf("To join a group you need to login arr[0]");
            }
            else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
            }     
        }
        
        else if(arr[0]=="leave_group")
        {
           if(login==0){
              printf("To leave a group you need to login arr[0]");
            }
            else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
            }     
        }
        
        else if(arr[0]=="list_requests")
        {
           if(login==0){
              printf("To see requests to join a group, you need to login arr[0]");
            }
            else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
            }     
        }
        
        else if(arr[0]=="accept_request")
        {
           if(login==0){
              printf("To see requests to join a group, you need to login arr[0]");
            }
            else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
            }     
        }
        
        
        else if(arr[0]=="list_groups")
        {
           if(login==0){
              printf("To see requests to join a group, you need to login arr[0]");
            }
            else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
            }     
        } 
        else if(arr[0]=="list_files")
        {
        }   
        else if(arr[0]=="upload_file")
        {
        }  
        else if(arr[0]=="download_file")
        {
        }  
        else if(arr[0]=="logout")
        {
            if(login==0)
           {
            printf("You are already logged out\n");
           }
           else{
               int sent_bytes = send(use,msg,1024, 0);
               if(sent_bytes==-1)
                {
                perror("Message not sent to server");
                 exit(-1);
                }

                bzero(msg, 1024);

                int valread=recv(use,msg,1024,0);
                if(valread==-1)
                {
                perror("Message not received from server");
                exit(-1);
                }
                cout << msg; 
                string res(msg);
                if(res=="Logout successfull\n"){
         //       printf("test if condition");
                login=0;
                }
             }      
        }
        else if(arr[0]=="show_downloads")
        {
        }  
        else if(arr[0]=="stop_share")
        {
        }     
        else{
             printf("Not a legal command\n");
        }
    }
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
 return 1;  
}