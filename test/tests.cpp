#include <gtest/gtest.h>
#include <iostream>
#include "../sommet.cpp"
#include "../segment.h"
#include <gmock/gmock.h>
#include <fcntl.h>

//#include "../dijkstra.h"

class sommetTest : public ::testing::Test {
public:
    sommet s1;
protected:
    virtual void SetUp() {
        s1 = sommet(1.0, 2.0);
    }
};

sommet s2(1.0, 1.0);
sommet s3(0.0,2.0);

TEST_F(sommetTest, constructor){
    EXPECT_TRUE(s1.x() == 1.0);
    EXPECT_EQ(s1.y(), 2.0);
}

TEST (sommet, operators){
    auto sum = s2+s3;
    auto mult = s2*5;
    s2-=s3;
    EXPECT_EQ(sum.x(),1);
    EXPECT_EQ(sum.y(),3);
    EXPECT_EQ(mult.x(),5);
    EXPECT_EQ(mult.y(),5);
    EXPECT_EQ(s2.x(),1.0);
    EXPECT_EQ(s2.y(),-1.0);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}