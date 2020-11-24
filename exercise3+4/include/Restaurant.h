#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "queue.h"
#include "Customer.h"
#define max 20

void reverse(string &a);
string itos(int a);
class Restaurant{
    queue<Customer> cusNormal;
    queue<Customer> cusVip;
    int nCustomer;
    int fNumber;
    public:
    Restaurant();
    int addCustomer(int id, char fid, bool isvip, string name = "");
    Customer serve();

    bool isEmpty();

};

#endif
