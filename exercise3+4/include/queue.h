#ifndef QUEUE_H
#define QUEUE_H

template<class var>
class queue{
    private:
    var *array;
    int capacity;
    int size;

    public:

    queue();
    queue(int size);
    bool isEmpty();
    bool isFull();
    int getCapacity();
    void push(var value);
    var pop();
    var pop(int index);
    var* getElement(int index);
    var getEle(int index);
};
#endif
