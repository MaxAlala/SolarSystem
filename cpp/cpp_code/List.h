//
// Created by X on 30.06.2019.
//

#ifndef CPP_CODE_LIST_H
#define CPP_CODE_LIST_H
#include <string>
#include <iostream>
#include <cassert>

namespace nsOfList {
    using namespace std;

    template<typename T>
    class List;  // pre-declare the template class itself
    template<typename T>
    std::ostream &operator<< (std::ostream &o, const List<T> &t);

    template<typename T>
    class List {
    public:
        List();
        List(List<T> &t);
        ~List();
        void push_back(T data);
        void clear();
        int getSize () const{ return Size; }
        void push_front(T data);
        void pop_back();
        void insert(T value, int index);
        void removeAt(int index);
        T &front();
        T &back();
        void pop_front();
        T &operator[](int index);
        List<T>&operator=(List<T> &t);
        friend std::ostream &operator<< <>(std::ostream &o, const List &t);
        List<T>& operator+(T o);

    private:
        template<typename E>
        class Node {
        public:
            Node *pNext;
            E data;

            Node(E data = E(), Node *pNext = nullptr) {
                this->data = data;
                this->pNext = pNext;
            }
        };

        Node<T>* getHeadNode(){
            return head;
        }
        Node<T>* getLastNode(){
            return lastNode;
        }
        int Size{};
        Node<T> *head = nullptr;
        Node<T> *lastNode = nullptr;
    };

    template<typename T>
    List<T>::List() {
        Size = 0;
        head = nullptr;
    }

    template<typename T>
    List<T>::~List() {
        clear();
    }


    template<typename T>
    void List<T>::push_back(T data) { // copy
        cout << "inside push back!"<< "\n";
        if (head == nullptr) {
            head = new Node<T>(data);
        } else {
            Node<T> *current = this->head;

            while (current->pNext != nullptr) {
                current = current->pNext;
            }
            current->pNext = new Node<T>(data);
            lastNode = current->pNext;
        }
        Size++;
    }

    template<typename T>
    void List<T>::clear() {
        while (Size) {// if 0 = stop
            pop_front();
        }
    }

    template<typename T>
    T &List<T>::operator[](const int index) {
        assert(!(index > Size - 1 || index < 0) && "wrong index, out of range");
        int counter = 0;
        Node<T> *current = this->head;
        while (counter != index) {
            current = current->pNext;
            counter++;
        }
        return current->data;
    }

    template<typename T>
    void List<T>::push_front(T data) {
        head = new Node<T>(data, head);
        Size++;
    }

    template<typename T>
    void List<T>::pop_back() {
        if (Size == 0) { return; }
        removeAt(Size - 1);
    }

    template<typename T>
    void List<T>::insert(T value, int index) {
        Node<T> *previous = nullptr;
        if (index == 0) {
            push_front(value);
        } else {
             previous = this->head;
            for (int i = 0; i < index - 1; i++) {
                previous = previous->pNext;
            }
            Node<T> *newNode = new Node<T>(value, previous->pNext);
            previous->pNext = newNode;
            Size++;
        }
        if (index == Size) {lastNode = previous; }
    }

    template<typename T>
    void List<T>::removeAt(int index) {
        if (index == 0) {
            pop_front();
        } else {
            Node<T> *previous = this->head;
            for (int i = 0; i < index - 1; i++) {
                previous = previous->pNext;
            }

            Node<T> *toDelete = previous->pNext;
            previous->pNext = toDelete->pNext;
            delete toDelete;
            Size--;

            if (index == Size-1) {
                lastNode = previous->pNext;
            }
        }
    }

    template<typename T>
    void List<T>::pop_front() {
        Node<T> *temp = head;
        head = head->pNext;
        delete temp;
        Size--;
    }

    template<typename T>
    T &List<T>::front() {
        assert(head != nullptr);
        return head->data;
    }

    template<typename T>
    T &List<T>::back() {
        assert(head != nullptr);
        return this->operator[](Size - 1);
    }

    template<typename T>
    List<T>& operator+ (List<T> &t, List<T> &t2) {
        cout << "Starting to add objects." <<'\n';
        for (int i = 0; i < t2.getSize(); ++i) {
//            cout << i << " i " << '\n';
//            cout << t2[i] << " here " <<'\n';
            t.push_back(t2[i]);
        }
//        t.getLastNode()->pNext = t2.head;  // if want remove second List can use this way.
//        t.getLastNode() = t2.getLastNode();
        return t;
    }

    template< typename T>
    List<T>& List<T>::operator+(T o){
        push_back(o);
        return *this;
    }

    template<typename T>
    List<T>::List(List<T> &t) {
        *this = *this + t;
    }

    template<typename T>
    List<T> &List<T>::operator=(List<T> &t) {
        if(this != &t) *this = *this + t;
        return *this;
    }
}
#endif //CPP_CODE_LIST_H

