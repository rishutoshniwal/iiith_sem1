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

class Group{
     public:
     string gid;
     vector<string> members;
     vector<string> waiting;
     int index;
     string admin;
     
       public:
       Group(string gid)
       {
           this->gid=gid;
         //  members.push_back(gid);
       }
};

class Client{
   public:
   string id,password;
   int login,index;
   
   public:
   Client(int index){
         // this->id=id;
         // this->password=password;
         this->index=index;
         this->login=0;
   }
   
  
};

unordered_map<string,Group*> mapOfGroups;
unordered_map<string,Client*> mapOfUsers;

void* run_command(void* index)
{
    int cli = *((int*)index);
    free(index);
     Client *newJoin=new Client(cli);
      printf("New client is connected at index : %d\n",cli);
     
    
    char msg[1024];
    
    while(1)
    {
     //   cout<<"Tracker is here\n";
        bzero(msg, 1024);
        int valread=recv(cli ,msg,1024,0);
        
        if(valread==-1)
        {
            perror("Message not received\n");
            exit(-1);
        }
        string temp;
        string command(msg);
         cout<<command<<"\n";
        vector<string> arr;
        stringstream split(command);
        while(getline(split,temp,' ')){
          // cout<<temp<<"\n";
            arr.push_back(temp);
           }
        
        if(arr[0]=="create_user")
        {
                   
        /*
          ptr=strtok(NULL," ");
           string second(ptr);
           cout<<"second :"<<second<<"\n";
           ptr=strtok(NULL," ");
           string third(ptr);
            cout<<"third :"<<third<<"\n";               */
           
           if(newJoin->login==1)
           {
            printf("You are already logged in\n");
           }
           else{
               if(mapOfUsers.find(arr[1])==mapOfUsers.end()){
                
                 newJoin->id=arr[1];
                 newJoin->password=arr[2];
                 mapOfUsers.insert({arr[1],newJoin});
                 string reply="User Successfully Created\n";
                 int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                 if(sent_bytes == -1)
                  {
                    perror("Message not sent");
                    exit(-1);
                  }
               }
               else{
                       string reply="User Successfully Created\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                       {
                          perror("Message not sent");
                          exit(-1);
                      }
               }
               
           }
         
        }
        
        else if(arr[0]=="login")
        {
               if(mapOfUsers.find(arr[1])==mapOfUsers.end()){
                    string reply="Invalid username\n";
                    int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                    if(sent_bytes == -1)
                    {
                    perror("Message not sent");
                    exit(-1);
                    }
               }
               else{
                   Client *c=mapOfUsers[arr[1]];
     //            cout<<"id : "<<c->id<<" password : "<<c->password<<" login : "<<c->login<< " index : "<<c->index<<"\n";
                   if(c->login==1){
                      string reply="User is already login\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }                   
                   }
                   
                    else if(c->id==arr[1] && c->password==arr[2] && c->index==cli)
                    {
                       c->login=1;
                      string reply="Login successfull\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }    
                    }
                    else{
                      string reply="Wrong password\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }                        
                    }
                   
                    
               }
               
        }
        
        else if(arr[0]=="create_group")
        {
             if(mapOfGroups.find(arr[1])==mapOfGroups.end()){
                   Group *g=new Group(arr[1]);
                   g->members.push_back(newJoin->id);
                   g->index=newJoin->index;
                   g->admin=newJoin->id;
                   mapOfGroups.insert({arr[1],g});
                   
                   string reply="Group Created successfully\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }            
                   
             }
             else{
                      string reply="Group ID Already Exist\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }            
             }
        }
        
        else if(arr[0]=="join_group")
        {
               if(mapOfGroups.find(arr[1])==mapOfGroups.end()){
                      string reply="Group ID Does Not Exist\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }       
               }
               else{
                    Group *gr=mapOfGroups[arr[1]];
                    int search=0;
                    for(int i=0;i<gr->members.size();i++)
                    {
                          if(gr->members[i]==newJoin->id)
                          {
                             search=1;
                             break;
                          }
                    }
                    
                    if(search==1)
                    {
                           string reply="You are already member of the group\n";
                           int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                            if(sent_bytes == -1)
                            {
                              perror("Message not sent");
                              exit(-1);
                            }     
                    }
                    else{
                          gr->waiting.push_back(newJoin->id);
                           string reply="Your request to add into the group is added\n";
                           int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                            if(sent_bytes == -1)
                            {
                              perror("Message not sent");
                              exit(-1);
                            }  
                    }
               }
        }
        
        else if(arr[0]=="leave_group")
        {
               if(mapOfGroups.find(arr[1])==mapOfGroups.end()){
                      string reply="Group ID Does Not Exist\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }       
               }
               else{
                    Group *gr=mapOfGroups[arr[1]];
                    if(gr->admin==newJoin->id)
                    {
                           string reply="Admin can not leave The Group\n";
                           int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                           if(sent_bytes == -1)
                            {
                              perror("Message not sent");
                              exit(-1);
                            }   
                    }
                    else{
                         int search=0;
                         for(int i=0;i<gr->members.size();i++)
                         {
                              if(gr->members[i]==newJoin->id){
                                   gr->members.erase(gr->members.begin()+i);
                                   search=1;
                                   break;
                               }    
                         }
                         
                         if(search==1)
                         {
                           string reply="You left the group : "+arr[1]+"\n";
                           int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                            if(sent_bytes == -1)
                            {
                              perror("Message not sent");
                              exit(-1);
                            }     
                         }
                        else{
                         
                           string reply="You are not member of the group\n";
                           int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                            if(sent_bytes == -1)
                            {
                              perror("Message not sent");
                              exit(-1);
                            }  
                          }
                    
                    
                    }
                   
               }
        }  
        else if(arr[0]=="list_requests")
        {
               if(mapOfGroups.find(arr[1])==mapOfGroups.end()){
                      string reply="Group ID Does Not Exist\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }       
               }  
               else{
                      Group *gr=mapOfGroups[arr[1]];
                      string reply="Pending requests of group : "+arr[1]+"\n";
                      for(int i=0;i<gr->waiting.size();i++)
                      reply=reply+"Waiting user : "+gr->waiting[i]+"\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }   
                      
               }      
        } 
        
        else if(arr[0]=="accept_request")
        {  
               if(mapOfGroups.find(arr[1])==mapOfGroups.end()){
                      string reply="Group ID Does Not Exist\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }       
               }    
               else if(mapOfUsers.find(arr[2])==mapOfUsers.end()){
                      string reply="User Does Not Exist\n";
                      int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                      if(sent_bytes == -1)
                      {
                      perror("Message not sent");
                      exit(-1);
                      }       
               }  
               else{
                     Group *gr=mapOfGroups[arr[1]];
                     if(gr->admin==newJoin->id)
                     {
                         int search=0;
                         for(int i=0;i<gr->waiting.size();i++)
                         {
                              if(gr->waiting[i]==arr[2]){
                                   gr->waiting.erase(gr->waiting.begin()+i);
                                   search=1;
                                   break;
                               }    
                         }
                         if(search==1)
                         {
                              gr->members.push_back(arr[2]);
                              string reply="Request to join group accepted\n";
                              int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                              if(sent_bytes == -1)
                               {
                                  perror("Message not sent");
                                  exit(-1);
                               }  
                         }
                         else{
                               string reply="No such request exist\n";
                              int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                              if(sent_bytes == -1)
                               {
                                  perror("Message not sent");
                                  exit(-1);
                               }  
                         }
                     }
                     else{
                          string reply="You can not accet requests becuase you are not the admin of this group\n";
                          int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                          if(sent_bytes == -1)
                          {
                           perror("Message not sent");
                           exit(-1);
                          }       
                     }
               }      
        } 
        else if(arr[0]=="list_groups")
        { 
           string reply="";
           for(auto mp:mapOfGroups)
           {
                reply=reply+"Group id : "+mp.first+"\n";
                for(int j=0;j<mp.second->members.size();j++)
                      reply=reply+"-----> Member name : "+mp.second->members[j]+"\n";
           }
           int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
           if(sent_bytes == -1)
           {
               perror("Message not sent");
               exit(-1);
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
            if(newJoin->login==1)
            {
                newJoin->login=0;
                 string reply="Logout successfull\n";
                 int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                 if(sent_bytes == -1)
                 {
                  perror("Message not sent");
                  exit(-1);
                 } 
             }
             else{
                 string reply="Logout Already\n";
                 int sent_bytes=send(cli,reply.c_str(),strlen(reply.c_str()),0);
                 if(sent_bytes == -1)
                 {
                  perror("Message not sent");
                  exit(-1);
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
               cout<<"Invalid command\n";
        }
    }
    
}

int main(int argc,char* arg[])

{
    struct sockaddr_in server, client;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1)
    {
        perror("socket error : ");
        exit(-1);
    }
    
    server.sin_family = AF_INET;
    server.sin_port = htons(8989);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);
    
    int opt = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{									
		perror("Socket error");
		exit(EXIT_FAILURE);
	}
	
	
	
    
    
    socklen_t len = sizeof(struct sockaddr_in);

    if(bind(sock,(struct sockaddr*)&server,len)==-1)
    {
        perror("binding error");
        exit(-1);
    }

    if(listen(sock,30) == -1)
    {
        perror("listen error");
        exit(-1);
    }
    
    cout<<"Server is ready and waiting for connections\n";
    while(1)
    {
    //   cout<<"Inside while loop\n";
        pthread_t t;
        int* index;
        int cli=accept(sock, (struct sockaddr*)&client, &len);

        if(cli==-1)
        {
            perror("accept");
            exit(-1);
        }
        
        
        
    //    printf("New client is connected at index : %d",cli);
   //   Client *newJoin=new Client(index);

        index=(int*)malloc(sizeof(int));
        *index=cli;
        pthread_create(&t,NULL,run_command,index);
    }	
   
   
}



















