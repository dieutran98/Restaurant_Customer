#include "../include/queue.h"
#include "../include/Customer.h"
//#include "../include/Food.h"
#include <iostream>

using namespace std;


template<class var>
queue<var>::queue(){
    array = NULL;
    capacity = 0;
    size = 0;
}

template<class var>
queue<var>::queue(int size){
    array = new var [size];
    capacity =0;
    this->size = size;
}

template<class var>
int queue<var>::getCapacity(){
    return capacity;
}

template<class var>
bool queue<var>::isEmpty(){
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "isEmpty"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "capacity = "<<capacity<<endl;
    // cout<<"---------------------------------------"<<endl;
    if(capacity==0){
        return true;
    }
    return false;
}

template<class var>
bool queue<var>::isFull(){
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "isFull"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "capacity = "<<capacity<<endl;
    // cout<<"---------------------------------------"<<endl;
    if(capacity==size){
        return true;
    }
    return false;
}

template<class var>
void queue<var>::push(var val){
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "Push"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    if(!isFull()){
        array[capacity]= val;
        capacity ++;
        // cout<< "capacity = "<<capacity<<endl;

    }
    else{
        cout<<"the queue is full, can't push!"<<endl;
    }
    // cout<<"---------------------------------------"<<endl;
}

template<class var>
var queue<var>::pop(){
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "pop"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    if(!isEmpty()){
        var re_val = array[0];
        for(int i=0;i<capacity-1;i++){
            array[i] = array[i+1];
        }
        capacity--;
        // cout<< "capacity = "<<capacity<<endl;
        return re_val;
    }
    else{
        cout<<"the queue is empty, can't pop"<<endl;
    }
    // cout<<"---------------------------------------"<<endl;
}

template<class var>
var queue<var>::pop(int index){
    //  cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    // cout<< "pop index"<<endl;
    // cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
    if(!isEmpty()){
        var re_val = array[index];
        for(int i=index;i<capacity-1;i++){
            array[i] = array[i+1];
        }
        capacity--;
        // cout<< "capacity = "<<capacity<<endl;
        return re_val;
    }
    else{
        cout<<"the queue is empty, can't pop"<<endl;
    }
    // cout<<"---------------------------------------"<<endl;

}

template<class var>
var* queue<var>::getElement(int index) {
    return (array+index);
}
template <class var>
var queue<var>::getEle(int index){
    return array[index];
}
template class queue<char>;
template class queue<Customer>;
//template class queue<Food>;