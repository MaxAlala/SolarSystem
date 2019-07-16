//
// Created by X on 13.07.2019.
//
#ifndef QUEUETP_H_
#define QUEUETP_H_

#include <string>
#include <iostream>

template <class Item>
class QueueTP
{
private:
    enum {Q_SIZE = 10};
// Node is a nested class definition
    class Node
    {
    public:
        Item item;
        Node * next;
        Node(const Item & i):item(i), next(0){ }
    };
    Node * front; // pointer to front of Queue
    Node * rear; // pointer to rear of Queue
    int items; // current number of items in Queue
    const int qsize; // maximum number of items in Queue
    QueueTP(const QueueTP & q) : qsize(0) {}
    QueueTP & operator=(const QueueTP & q) { return *this; }
public:
    QueueTP(int qs = Q_SIZE);
    ~QueueTP();
    bool isempty() const
    {
        return items == 0;
    }
    bool isfull() const
    {
        return items == qsize;
    }
    int queuecount() const
    {
        return items;
    }
    bool enqueue(const Item &item); // add item to end
    bool dequeue(Item &item); // remove item from front
};
// QueueTP methods
template <class Item>
QueueTP<Item>::QueueTP(int qs) : qsize(qs)
{
    front = rear = 0;
    items = 0;
}
template <class Item>
QueueTP<Item>::~QueueTP()
{
    Node * temp;
    while (front != 0) // while queue is not yet empty
    {
        temp = front; // save address of front item
        front = front->next;// reset pointer to next item
        delete temp; // delete former front
    }
}
// Add item to queue
template <class Item>
bool QueueTP<Item>::enqueue(const Item & item)
{
    if (isfull())
        return false;
    Node * add = new Node(item); // create node
// on failure, new throws std::bad_alloc exception
    items++;
    if (front == 0) // if queue is empty,
        front = add; // place item at front
    else
        rear->next = add; // else place at rear
    rear = add; // have rear point to new node
    return true;
}

// Place front item into item variable and remove from queue
template <class Item>
bool QueueTP<Item>::dequeue(Item & item)
{
    if (front == 0)
        return false;
    item = front->item; // set item to first item in queue
    items--;
    Node * temp = front; // save location of first item
    front = front->next; // reset front to next item
    delete temp; // delete former first item
    if (items == 0)
        rear = 0;
    return true;
}


void useIt(){

using std::string;
using std::cin;
using std::cout;
QueueTP<string> cs(5);
string temp;
while(!cs.isfull())
{
cout << "Please enter your name. You will be "
"served in the order of arrival.\n"
"name: ";
getline(cin, temp);
cs.enqueue(temp);
cout << "The queue is full. Processing begins!\n";
while (!cs.isempty())
{
cs.dequeue(temp);
cout << "Now processing " << temp << "...\n";
}
}
}

#endif //CPP_CODE_QUEUE_H



