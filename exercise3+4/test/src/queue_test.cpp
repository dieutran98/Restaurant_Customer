#include "../../include/queue.h"
#include "../../include/Customer.h"

#include <iostream>
#include <sstream>
using namespace std;

int main(){
    /*
    queue<Customer> c(10);
    c.push(Customer(3,'a',"kk"));
    c.push(Customer(3,'b', "aa"));
    
    Customer* a = c.getElement(1);
    cout<<"id= "<< a->getId()<<endl;
    cout<<"name= "<< a->getname()<<endl;
    a->addFood('c');
    c.pop();
    //cout<<"a ="<< a<<endl;
    cout<<"getElement= " << c.getElement(0)->servedf()<<endl;
    cout<<"getElement= " << c.getElement(0)->servedf()<<endl;
    cout<<"getElement= " << c.getElement(0)->servedf()<<endl;
    */
    char  a;
    string k = "asdas dasdas";
    string temp;
    stringstream ss;
    stringstream ss0;
    ss<<k;
    ss>>temp;
    ss0<<temp;
    ss0>>a>>temp;
    //stringstream(temp)>>a;
    cout<<"a= "<<a<<" "<<temp<<endl;
    return 0;
}