#include <iostream>
#include <stdio.h>

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sstream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <unistd.h>

#include "../include/Customer.h"

// Message queue path
#define server_path "temp/msgq_server.txt"
#define client_path1 "temp/msgq_client1.txt"
#define client_path0 "temp/msgq_client0.txt"

#define PERMS 0660
#define project_id 'S'

using namespace std;

void *send(void*);
void *recieve(void*);
void create_message();
void reverse(string&);
string itos(int);

struct msg_text {
   int msgqid;
   char mtext[200];
};
struct msg_buf{
   long type;
   struct msg_text msg_text;
};

struct msg_buf client_send;
struct msg_buf client_recieve;
int client_qid,server_qid;
key_t server_key,client_key;
string path;

//some Customer contribute can change
Customer c;
bool isVip= false;
string name="";

/*
*  ./Customer_m0 path isVip name
*/
int main(int argc, char**argv){
    pthread_t cusSend;
    pthread_t cusRecieve;
    int rc[2];
    string arg[2];
    
    if(argc>=2){
      path = argv[1];
      if(path=="path1"){
         path = client_path1;
         //cout<<"client path "<<path.c_str()<<"....."<<endl;
      }else if(path == "path0"){
         path = client_path0;
         //cout<<"client path "<<path.c_str()<<"....."<<endl;
      }
    }
    if(argc>=3){
      arg[0]=argv[2];
      if(arg[0]=="1"){
         //cout<<"if isvip"<<endl;
         isVip =true;
      }else{
         if(arg[0]=="0"){
            isVip=false;
         }
      }
    }
    if(argc>=4){
      arg[1]=argv[3];
      if(!arg[1].empty()){
         //cout<<"if name"<<endl;
         name= arg[1];
      }
    }
    //thread send massage
   rc[0]=pthread_create(&cusSend,NULL,send,NULL);
    if(rc[0]){
        cout << "Error:unable to create thread," << rc[0] << endl;
        return -1;
    }
    // thread recieve massage
   rc[1]=pthread_create(&cusRecieve,NULL,recieve,NULL);
   if(rc[1]){
        cout << "Error:unable to create thread," << rc[1] << endl;
        return -1;
   }
   pthread_exit(NULL);
    return 0;
}

void create_message(){
   // Client message queue
   if ((client_key = ftok(path.c_str(), project_id)) == -1) {
      perror("ftok: client_key");
      exit(1);
   }
   
   if ((client_qid = msgget(client_key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget: client_qid");
      exit(1);
   }
   // client queue id will be customer id
   client_send.msg_text.msgqid=client_qid;
   c = Customer(client_qid,isVip,name);

   //server massage queue
   if ((server_key = ftok(server_path, project_id)) == -1) {
      perror("ftok: server_key");
      exit(1);
   }
   
   if ((server_qid = msgget(server_key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget: server_qid");
      exit(1);
   }
   //cout<<"Customer 0 client_qid "<<client_qid<<endl;
   //cout<<"Customer 0 server_qid "<<server_qid<<endl;

   printf("message queue: ready to send messages.\n");
   //printf("Enter lines of text, ^D to quit:\n");
   client_send.type = 1;
}
void* send(void* argsend){
    int len;
    create_message();
    char sendbuf[200];
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        stringstream ss;
        string temp;
        
        string request;
        int len = strlen(sendbuf);
        /* remove newline at end, if it exists */
        if (sendbuf[len-1] == '\n') sendbuf[len-1] = '\0';

        ss<<sendbuf;
        ss>>temp;
        cout<<"sendbuf "<<sendbuf<<"..."<<endl;
        //cout<<"send temp "<< temp <<endl;
        // check if input is a request
        if(temp=="request"){
           if(!ss.eof()){
               char fid;
               ss>>fid;
               c.addFood(fid);
               request = "add "+ itos(c.getId()) + " "+fid+" "+c.getIsVip();
               if(c.getname()!=""){
                  request +=" " + c.getname();
               }
               strcpy(client_send.msg_text.mtext,request.c_str());
               len=strlen(client_send.msg_text.mtext);
               client_send.msg_text.mtext[len] = '\0';
               if (msgsnd(server_qid, &client_send, sizeof(client_send.msg_text.mtext), 0) == -1) 
                  perror("msgsnd");
               cout<<"send..."<<request<<endl;
               cout<<"================================================"<<endl;
           }
        }
    }

   if (msgctl(client_qid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
   pthread_exit(NULL);
}
void* recieve(void* argRecieve){
    printf("message queue: ready to receive messages.\n");
    string buf;
   while(1) { 
      if (msgrcv(client_qid, &client_recieve, sizeof(client_recieve.msg_text.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      buf = client_recieve.msg_text.mtext;
      stringstream ss;
      string temp;
      ss<<buf;
      ss>>temp;
      cout<<"recieve buf "<<buf<<"..."<<endl;
      //cout<<"recieve temp "<< temp <<endl;
      // check if recieve "serve ""
      if(temp=="serve"){
         ss>>temp;
         if(temp==itos(c.getId())||temp==c.getname()){
            char a = c.servedf();
            cout<<"served: "<<a<<endl;
            cout<<"================================================"<<endl;
         }
      }
   }
   pthread_exit(NULL);
}
void reverse(string &a)
{
    int n = a.length();
    
    for (int i = 0; i < n / 2; i++)
    {
       char temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
}

string itos(int a)
{
    string temp;
    while (a != 0)
    {
        temp.push_back('0' + a % 10);
        a = a / 10;
    }
    reverse(temp);
    return temp;
}