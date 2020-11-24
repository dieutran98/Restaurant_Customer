#include <iostream>
#include <sstream>
#include <fstream>

#include <pthread.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>

#include <string.h>

#include "../include/Restaurant.h"

#define savefile "dailyWork.txt"
#define errormsg "your comand is wrong please enter the right cmd: add [id] [food id] [isVip] [name] or serve!"<<endl

#define server_path "temp/msgq_server.txt"
//#define client_path "temp/msgq_client.txt"
#define PERMS 0660
#define project_id 'S'
using namespace std;


struct msg_text {
   int msgqid;
   char mtext[200];
};
struct msg_buf{
   long type;
   struct msg_text msg_text;
};

struct msg_buf server_buf;
int server_qid,client_qid;
key_t server_key;
Restaurant r;
string cmd;

void *send(void*);
void *recieve(void*);
void create_message();
/* 
*   convert string to int 
*/
int sti(string a){
    int length = a.length();
    // cout<<"lenght =" << length<<endl;
    int number=0;
    for (int i =0; i<length; i++){
        if(a[i]<='9'&& a[i]>='0')
            number = number*10 + a[i]-'0';
        else return 0;
    }
    return number;
}

template<typename t>
void saveWork(t cmd){
    ofstream myfile (savefile, ios::app);
    if (myfile.is_open())
    {
    myfile << cmd << endl;
    myfile.close();
    }
    else cout << "Fail to save the log!"<<endl;
}
int implement(){
    stringstream ss;
    stringstream ss0;
    ss<<cmd;
    string temp;
    ss>>temp;
    if(temp == "add"){ 
        ss>>temp;
        int id;
        string name =" ";
        string invalidFid;
        string invalidId;
        
        stringstream(temp)>>id>>invalidId;
        if(invalidId.empty()){
           // cout<<temp<<endl;
           //cout<<"id hop le "<<id<<endl;
           char fid;
           ss>>temp;
           ss0<<temp;
           ss0>>fid>>invalidFid;
           if(invalidFid.empty()){
               //cout<<"fid= "<<fid<<endl;
               if(fid>='a' && fid<='z'  /*&& fid>='A' && fid<='Z'*/){
                    //cout<<"Food id hop le "<<fid<<endl;
                    bool isVip =false;
                    if(ss.eof()){
                        //cout<<"add cus 1"<<endl;
                        r.addCustomer(id,fid,isVip,name);
                        saveWork<string>(cmd);
                        return 1;
                    }
                    else{
                        ss>>temp;
                        if(temp=="1"||temp=="0"){
                            isVip = (temp == "1")? true:false;
                            //cout<<"isVip hop le "<<isVip<<endl;
                            if(ss.eof()){
                                //cout<<"add cus 2"<<endl;
                                r.addCustomer(id,fid,isVip,name);
                                saveWork<string>(cmd);
                                return 1;  
                            }
                            else{
                                ss>>temp;
                                name = temp;
                                //cout<<"add cus 3"<<endl;
                                r.addCustomer(id,fid,isVip,name);
                                saveWork<string>(cmd);
                                return 1;
                            }
                        }
                        else{
                            name = temp;
                            //cout<<"add cus 4"<<endl;
                            r.addCustomer(id,fid,isVip,name);
                            saveWork<string>(cmd);
                            return 1;
                        }
                    }
               }  
           }
        }
        cout<<errormsg;
        return -1;
    }
    if(temp=="serve"){
        //string ser = r.serve();
        //if(!ser.empty()){
        //cout<<ser<<endl;
        //saveWork<string>(ser);
        return 1;
        }
        return -1;
}


int main(int argc, char**argv){
    pthread_t cusSend;
    pthread_t cusRecieve;
    int rc[2];
    //create_message();
   rc[0]=pthread_create(&cusSend,NULL,send,NULL);
    if(rc[0]){
        cout << "Error:unable to create thread," << rc[0] << endl;
        return -1;
    }
   rc[1]=pthread_create(&cusRecieve,NULL,recieve,NULL);
   if(rc[1]){
        cout << "Error:unable to create thread," << rc[1] << endl;
        return -1;
   }
   pthread_exit(NULL);
    return 0;
    
}
void create_message(){
    
   // server message queue
   if ((server_key = ftok(server_path, project_id)) == -1) {
      perror("ftok: server_key");
      exit(1);
   }
   
   if ((server_qid = msgget(server_key, PERMS | IPC_CREAT)) == -1) {
      perror("msgget: server_qid");
      exit(1);
   }
    // client message queue
    
   //cout<<"Restaurant client_qid "<<client_qid<<endl;
   cout<<"Restaurant server_qid "<<server_qid<<endl;
   printf("message queue: ready to send messages.\n");
   //printf("Enter lines of text, ^D to quit:\n");
   server_buf.type = 1;
}
void* send(void* argsend){
    create_message();
    char sendbuf[200];
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        int len = strlen(sendbuf);
        string temp;
        /* remove newline at end, if it exists */
        if (sendbuf[len-1] == '\n') sendbuf[len-1] = '\0';
        //cout<<"sendbuf "<<sendbuf<<"..."<<endl;
        temp = sendbuf;
        if(temp=="serve"){
            if(!r.isEmpty()){
                Customer a = r.serve();
                temp ="serve "+itos(a.getId())+" "+a.servedf();
                cout<<"sendbuf "<<temp<<"..."<<endl;
                saveWork<string>(temp);
                //if (sendbuf[len-1] == '\n') sendbuf[len-1] = '\0';
                strcpy(server_buf.msg_text.mtext,temp.c_str());
                client_qid = a.getId();
                //s0>>client_qid;
                //cout<<"client id "<<client_qid<<endl;
                if (msgsnd(client_qid, &server_buf, sizeof(server_buf.msg_text.mtext), 0) == -1) 
                perror("msgsnd");
                cout<<"================================================"<<endl;
            }
        }
    }
   if (msgctl(server_qid, IPC_RMID, NULL) == -1) {
      perror("msgctl");
      exit(1);
   }
   printf("message queue: done sending messages.\n");
   pthread_exit(NULL);
}
void* recieve(void* argRecieve){
    printf("message queue: ready to receive messages.\n");
    string buf;
   while(1) { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
      if (msgrcv(server_qid, &server_buf, sizeof(server_buf.msg_text.mtext), 0, 0) == -1) {
         perror("msgrcv");
         exit(1);
      }
      buf = server_buf.msg_text.mtext;
      stringstream ss;
      string temp;
      string recievebuf;
      ss<<buf;
      ss>>temp;
      cout<<"recieve buf.mytext: "<<buf<<"...."<<endl;
      cout<<"recieve temp "<< temp <<endl;
      if(temp=="add"){
         cmd = buf;
         cout<<"cmd "<<cmd<<endl;
         implement();
         cout<<"================================================"<<endl;
      }
   }
   pthread_exit(NULL);
}