//
// Created by X on 02.07.2019.
//

#include "Test.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../List.h"

    class ClassDeclaration : public testing::Test { // fixture
    public:
        nsOfList::List<int> list;
        ClassDeclaration() {
            list;
        }
    };

TEST_F(ClassDeclaration, test1){
    ASSERT_EQ("1","1");
}

TEST_F(ClassDeclaration, test2){
    ASSERT_EQ("","2");
}
