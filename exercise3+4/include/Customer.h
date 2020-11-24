#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "queue.h"
#include <iostream>
using namespace std;
class Customer{
    int id;
    string name;
    int served;
    queue<char> foodid;
    bool isVip;
    public:
    Customer(int id, char fid, string name="");
    //Customer(int id, char fid, string name=" ");
    Customer(int id, bool isVip = false, string name="");
    Customer();
    int getId();
    char servedf();
    string getname();
    void addFood(char f);
    int getServed();
    void setName(string name);
    bool foodIsEmpty();
    string getIsVip();
    void copy(Customer);
};
#endif