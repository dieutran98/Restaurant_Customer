#include "../../include/Customer.h"

#include <iostream>

using namespace std;

int main(){
    Customer c;
    c= Customer(3, 'a', "Dieu");
    c.addFood('b');
    cout<<"ID= "<<c.getId()<<endl;
    cout<<"food ID= "<<c.servedf()<<endl;
    cout<<"name= "<<c.getname()<<endl;
    cout<<"food ID= "<<c.servedf()<<endl;
    
        if(c.foodIsEmpty()){
            cout<<"no food need to serve"<<endl;
        }
 
    return 0;
}