#include "../include/Restaurant.h"
#include <iostream>
using namespace std;

Restaurant::Restaurant(){
    cusNormal = queue<Customer>(10);
    cusVip = queue<Customer>(10);
    fNumber = 0;
    nCustomer = 0;
}

bool Restaurant::isEmpty(){
    return cusVip.isEmpty() && cusNormal.isEmpty();
}

int Restaurant::addCustomer(int id, char fid, bool isvip, string name){
    if(nCustomer <= max){
        if(isvip){
             //cout<<"Customer is Vip" << endl;
            if(!cusVip.isEmpty()){
            // cout<<"vip Customer queue is not empty" << endl;
                int n = cusVip.getCapacity();
                for(int i=0; i<n; i++){
                    Customer* c = cusVip.getElement(i);
                    if(c->getId()==id){
                        c->addFood(fid);
                        if(name != ""){
                            c->setName(name);
                            // cout<<"name change "<< c->getname()<<endl;
                        }
                        return 1;
                    }
                }
                // cout<<"Customer haven't in queue yet" << endl;
                cusVip.push(Customer(id,fid,name));
            }
            else{
            // cout<<"vip Customer queue is empty" << endl;
                cusVip.push(Customer(id,fid,name));
            }
        }else{
             //cout<<"Customer is Normal" << endl;
            if(!cusNormal.isEmpty()){
             //cout<<"Normal Customer queue is not empty" << endl;
                int n = cusNormal.getCapacity();
                for(int i=0; i<n; i++){
                    Customer* c = cusNormal.getElement(i);
                    if(c->getId()==id){
                        c->addFood(fid);
                        if(name != ""){
                            c->setName(name);
                            //cout<<"name change "<< c->getname()<<endl;
                        }
                        return 1;
                    }
                }
                 //cout<<"Customer haven't in queue yet" << endl;
                cusNormal.push(Customer(id,fid,name));
            }
            else{
             //cout<<"Normal Customer queue is empty" << endl;
                cusNormal.push(Customer(id,fid,name));
            }
        }
        nCustomer++;
    }else{
        cout<<"Restaurant is full right now, please comeback later. ";
        return 0;
    }
    return 1;
}

void reverse(string &a)
{
    int n = a.length();
    for (int i = 0; i < n / 2; i++)
    {   
        char temp0 = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp0;
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

Customer Restaurant::serve(){
    //string s_serve;
    Customer a;
    for(int k=0; k<2; k++){    
        if(!cusVip.isEmpty()){
            //cout<<"vip is available"<<endl;
            int n = cusVip.getCapacity();
            for(int i=0; i<n; i++){
                Customer* cus= cusVip.getElement(i);
                if(cus->getServed()==fNumber){
                    a.copy(cusVip.getEle(i));
                    char fid = cus->servedf();
                    a.addFood(fid);
                    //int id = cus->getId();
                    //cout<<"id ="<<id<<endl;
                    if(cus->foodIsEmpty()){
                        cusVip.pop(i);
                        return a;
                    }
                    // cout<<"s_serve =" << s_serve << endl;
                    if(isEmpty()){
                        cout<<"Restaurant is empty now!"<< endl;
                        fNumber =0;
                    }
                    return a;
                }
            }
        }else{
             //cout<<"Cusotmer vip is empty!"<<endl;
        }

        if(!cusNormal.isEmpty()){
            //cout<<"normal is available"<<endl;
            int n = cusNormal.getCapacity();
            for(int i=0; i<n; i++){
                Customer* cus= cusNormal.getElement(i);
                if(cus->getServed()==fNumber){
                    a.copy(cusNormal.getEle(i));
                    char fid = cus->servedf();
                    a.addFood(fid);

                    if(cus->foodIsEmpty()){
                        cusNormal.pop(i);
                        return a;
                    }
                    // cout<<"s_serve =" << s_serve << endl;
                    if(isEmpty()){
                        cout<<"Restaurant is empty now!"<< endl;
                        fNumber =0;
                    }
                    return a;
                }
            }
        }else{
             //cout<<"Cusotmer Normal is empty!"<<endl;
        }
        fNumber++;
    }
    cout<<"there is no Customer need to be served"<<endl;
    fNumber =0;
}

