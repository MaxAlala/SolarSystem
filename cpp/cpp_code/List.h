//
// Created by X on 30.06.2019.
//

#ifndef CPP_CODE_LIST_H
#define CPP_CODE_LIST_H
#include <string>
#include <iostream>
#include <cassert>

//TODO 1) if char* or int* etc than will be memory leak!
// The solution is the (partial) specialization.

namespace Constants{
    extern const double earth_radius;
    extern const double mercury_radius;
    extern const double venus_radius;
}

namespace nsOfList {
    using std::cout;
    template<typename T>
    class List;  // pre-declare the template class itself
    template<typename T>
    std::ostream &operator<<(std::ostream &o, const List<T> &t);

    template<typename T>
    bool operator==(List<T> &t, List<T> &t1);

    template<typename T>
    bool operator!=(List<T> &t, List<T> &t1);

    template<typename T>
    class List {
    public:
        List();

        List(const List<T> &t);
        List(const std::initializer_list<T> &list);

        ~List();

        List<T>& push_back(T data);

        void clear();

        int getSize() const { return Size; }

        void push_front(T data);

        void pop_back();

        void insert(T value, int index);

        void removeAt(int index);

        T &front(void) const;

        T &back(void) const;

        void pop_front();

        T &operator[](int index);

        List<T> &operator=(const List<T> &t);

        friend bool operator==<>(List &t, List &t1);

        friend bool operator!=<>(List &t, List &t1);

        friend std::ostream &operator<<<>(std::ostream &o, const List &t);

        List<T> &operator+(T o);

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

        Node<T> *getHeadNode() {
            return head;
        }

        Node<T> *getLastNode() {
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
//        cout << "Called destructor! \n";
        clear();
    }


    template<typename T>
    List<T>& List<T>::push_back(T data) { // copy
//        cout << "inside push back!"<< "\n";
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
        return  *this;
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
        if (index == Size) { lastNode = previous; }
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

            if (index == Size - 1) {
                lastNode = previous->pNext;
            }
        }
    }

    template<typename T>
    void List<T>::pop_front() {
        Node<T> *temp = head;
        head = head->pNext;
//        cout << temp->data << " . Node deletion. \n";
        delete temp;
        Size--;
    }

    template<typename T>
    T &List<T>::front() const {
        assert(head != nullptr);
        return head->data;
    }

    template<typename T>
    T &List<T>::back() const {
        assert(head != nullptr);
        return this->operator[](Size - 1);
    }

    template<typename T>
    List<T> &operator+(List<T> &t, List<T> &t2) {
//        cout << "Starting to add objects." <<'\n';
        for (int i = 0; i < t2.getSize(); ++i) {
//            cout << i << " i " << '\n';
//            cout << t2[i] << " here " <<'\n';
            t.push_back(t2[i]);
        }
//        t.getLastNode()->pNext = t2.head;  // if want remove second List can use this way.
//        t.getLastNode() = t2.getLastNode();
        return t;
    }


    template<typename T>
    std::ostream &operator<<(std::ostream &out, nsOfList::List<T> &t) {
        for (int i = 0; i < t.getSize(); i++) {
            std::cout << t[i] << " is some unrecognized object. \n";
        }
        return out;
    }

//    template<typename T>
//    std::ostream &operator+ (List<T> &t, List<T> &t) {
//        for (int i = 0; i < t.getSize(); i++) {
//            cout << t[i] << " is some unrecognized object. \n";
//        }
//        return out;
//    }

    template<>
    inline std::ostream &operator<<(std::ostream &out, nsOfList::List<int> &t) {
        for (int i = 0; i < t.getSize(); i++) {
            std::cout << t[i] << " this is an integer! \n";
        }
        return out;
    }


    template<typename T>
    List<T> &List<T>::operator+(T o) {
        push_back(o);
        return *this;
    }

    template<typename T>
    List<T>::List(const List<T> &t) {
        *this = *this + t;
    }

    template<typename T>
    List<T> &List<T>::operator=(const List<T> &t) {
        if (this != &t) *this = *this + t;
        return *this;
    }

    template<typename T>
    bool operator==(List<T> &t, List<T> &t1) {
        if (&t == &t1) return true;
        if (t.getSize() != t.getSize()) return false;
        for (int i = 0; i < t.getSize(); i++) {
            if (t[i] != t1[i]) return false;
        }
        return true;
    }

    template<typename T>
    bool operator!=(List<T> &t, List<T> &t1) {
        return !(t == t1);
    }

    template<typename T>
    List<T>::List(const std::initializer_list<T> &list) {
        for (auto &element : list)
        {
            this->push_back(element);
        }
    }

}
#endif //CPP_CODE_LIST_H
