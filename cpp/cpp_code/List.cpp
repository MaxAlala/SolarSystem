//
// Created by X on 02.07.2019.
//

#include "List.h"

template<typename T>
std::ostream &operator<< (std::ostream &out, nsOfList::List<T> &t) {
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
std::ostream &operator<< (std::ostream &out, nsOfList::List<int> &t) {
    for (int i = 0; i < t.getSize(); i++) {
        std::cout << t[i] << " this is an integer! \n";
    }
    return out;
}