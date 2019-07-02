//
// Created by X on 02.07.2019.
//

#include "Test.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../List.h"
#include "../STL.h"

class ClassDeclaration : public testing::Test { // fixture
    public:
    protected:
        void SetUp()
        {
            list.push_back(Object("Mercury", 3.3e23));
            list.push_back(Object("Venus", 4.87e23));
            list.push_back(Object("Earth", 5.972e24));
            list.push_back(Object("Mars", 6.42e23));

            list2.push_back(Object("Jupiter", 1898e24));
            list2.push_back(Object("Saturn", 569e24));
            list2.push_back(Object("Uranus", 86.8e24));
            list2.push_back(Object("Neptune", 102.e24));
        }
        void TearDown(){
        }
   nsOfList::List<Object> list;
   nsOfList::List<Object> list2;
    };

TEST_F(ClassDeclaration, isZeroElemEarth){
    ASSERT_EQ(list.front().getName(), "Mercury") << " test with zero elem";
    list.push_front(Object("Earth", 5.972e24));
    ASSERT_EQ(list.front().getName(), "Earth") << " test with zero elem";
}

TEST_F(ClassDeclaration, isZeroElemWeightis3_3e23){
    ASSERT_EQ(list.front().getWeight(), 3.3e23) << " test weight 3.3e23";
}

TEST_F(ClassDeclaration, isSumSize8){
    list2.clear();
    list2.push_back(Object("Mercury", 3.3e23));
    list2.push_back(Object("Venus", 4.87e23));
    list2.push_back(Object("Earth", 5.972e24));
    list2.push_back(Object("Mars", 6.42e23));
    cout << "hellllo! \n";
    if(list == list2)cout << "hellllo! EQUAL \n";
    ASSERT_EQ(8, (list + list2).getSize());
}


//TEST_F(ClassDeclaration, aretheyEqual){
//    ASSERT_EQ(list, list2) << " equality";
//}

