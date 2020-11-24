#include "../include/Customer.h"

Customer::Customer(int id, char fid, string name){
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "Customer Contructor"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    this->id = id;
    // cout<< "id= "<< this->id<< endl;
    setName(name);
    // cout<< "name= "<<this->name<<endl;
    served = 0;
    foodid = queue<char> (10);
    foodid.push(fid);
    // cout<<"food ID= "<<*foodid.getElement(0)<<endl;
    // cout<<"---------------------------------------"<<endl;
}
Customer::Customer(int id, bool isVip,  string name){
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "Customer Contructor"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    this->id = id;
    // cout<< "id= "<< this->id<< endl;
    setName(name);
    // cout<< "name= "<<this->name<<endl;
    served = 0;
    this->isVip = isVip;
    foodid = queue<char> (10);
    // cout<<"food ID= "<<*foodid.getElement(0)<<endl;
    // cout<<"---------------------------------------"<<endl;
}
// Customer::Customer(int id, char fid,  string name){
//     // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
//     // cout<< "Customer Contructor"<<endl;
//     // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
//     this->id = id;
//     // cout<< "id= "<< this->id<< endl;
//     setName(name);
//     // cout<< "name= "<<this->name<<endl;
//     served = 0;
//     foodid = queue<char> (10);
//     foodid.push(fid);
//     // cout<<"food ID= "<<*foodid.getElement(0)<<endl;
//     // cout<<"---------------------------------------"<<endl;
// }

Customer::Customer(){
    foodid = queue<char>(10);
}

int Customer::getId(){
    return id;
}

string Customer::getname(){
    return name;
}

char Customer::servedf(){
    served++;
    return foodid.pop();
}

void Customer::addFood(char f){
    foodid.push(f);
}
void Customer::setName(string name){
    this->name = name;
}

int Customer::getServed(){
    return served;
}

bool Customer::foodIsEmpty(){
    return foodid.isEmpty();
}

string Customer::getIsVip(){
    if(isVip){
        return "1";
    }
    return "0";
}

void Customer::copy(Customer a){
    id= a.id;
    name = a.name;
    served = a.served;
    //foodid = a.foodid;
    isVip = a.isVip;
}