////
//// Created by X on 02.07.2019.
////
//
//#include "Test.h"
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include "../List.h"
//#include "../STL.h"
//
//class ClassDeclaration : public testing::Test { // fixture
//public:
//protected:
//    void SetUp()
//    {
//    }
//    void TearDown(){
//    }
//    nsOfList::List<Object> list{Object("Mercury", 3.3e23),
//                                Object("Venus", 4.87e23),
//                                Object("Earth", 5.972e24),
//                                Object("Mars", 6.42e23)};
//    nsOfList::List<Object> list2{Object("Jupiter", 1898e24),
//                                 Object("Saturn", 569e24),
//                                 Object("Uranus", 86.8e24),
//                                 Object("Neptune", 102.e24)};
//};
//
//TEST_F(ClassDeclaration, isZeroElemEarth){
//    ASSERT_EQ(list.front().getName(), "Mercury") << " test with zero elem";
//    list.push_front(Object("Earth", 5.972e24));
//    ASSERT_EQ(list.front().getName(), "Earth") << " test with zero elem";
//}
//
//TEST_F(ClassDeclaration, isZeroElemWeightis3_3e23){
//    ASSERT_EQ(list.front().getWeight(), 3.3e23) << " test weight 3.3e23";
//}
//
//TEST_F(ClassDeclaration, isSumSize8){
//
//    ASSERT_EQ(8, (list + list2).getSize());
//}
//
//TEST_F(ClassDeclaration, aretheyEqual){
//    list2.clear();
//    list2.push_back(Object("Mercury", 3.3e23)).push_back(Object("Venus", 4.87e23))
//    .push_back(Object("Earth", 5.972e24)).push_back(Object("Mars", 6.42e23));
//    ASSERT_EQ(true, list == list2) << " equality";
//}
//
//::testing::AssertionResult isTrue(bool b)
//// return assertResult
//{
//    return testing::AssertionSuccess();
//}
//
