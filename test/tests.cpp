#include <gtest/gtest.h>
#include <iostream>
#include "../sommet.cpp"
#include "../segment.cpp"
#include "../obstacle.cpp"
#include <gmock/gmock.h>
#include <fcntl.h>

//#include "../dijkstra.h"
//Les unit-tests

class sommetTest : public ::testing::Test {
public:
    sommet s1;
protected:
    virtual void SetUp() {
        s1 = sommet(1.0, 2.0);
    }
};

sommet s2(1.0, 1.0);
sommet s3(0.0, 2.0);

TEST_F(sommetTest, constructor) {
    EXPECT_TRUE(s1.x() == 1.0);
    EXPECT_EQ(s1.y(), 2.0);
}

TEST (sommet, operators) {
    auto sum = s2 + s3;
    auto mult = s2 * 5;
    s2 -= s3;
    EXPECT_EQ(sum.x(), 1);
    EXPECT_EQ(sum.y(), 3);
    EXPECT_EQ(mult.x(), 5);
    EXPECT_EQ(mult.y(), 5);
    EXPECT_EQ(s2.x(), 1.0);
    EXPECT_EQ(s2.y(), -1.0);
}

const auto b = sommet(0, 0);
const auto e = sommet(1, 0);

class segmentTest : public ::testing::Test {
public:
    segment s;
    sommet beg;
    sommet end;
protected:
    virtual void SetUp() {
        s = segment(b, e);
        beg = s.begin();
        end = s.end();
    }
};

class obstacleTest : public ::testing::Test {
    std::vector<sommet> vertices;
    segment line1;

    virtual void SetUp() {
        vertices.push_back(sommet(1, 1));
        vertices.push_back(sommet(3, 1));
        vertices.push_back(sommet(3, 3));
        vertices.push_back(sommet(1, 3));
    }
};

TEST_F(segmentTest, constructor) {
    EXPECT_EQ(beg.x(), 0.0);
    EXPECT_EQ(beg.y(), 0.0);
    EXPECT_EQ(end.x(), 1.0);
    EXPECT_EQ(end.y(), 0.0);
}

TEST(segment, intersection) {
    const sommet point1_hl(0.0, 0.0);
    const sommet point1_hr(5.0, 0.0);
    const sommet point1_vl(0.0, 0.0);
    const sommet point1_vr(0.0, 5.0);
    const segment line1h(point1_hl, point1_hr);
    const segment line1v(point1_vl, point1_vr);
    EXPECT_EQ(intersection(line1h, line1v), false);

    const sommet point2_hl(-5, 0);
    const segment line2h(point2_hl, point1_hr);
    EXPECT_EQ(intersection(line2h, line1v),true);

    const sommet point2_vl(0, -5);
    const segment line2v(point2_vl, point1_vr);
    EXPECT_EQ(intersection(line2h, line2v), true);
    EXPECT_EQ(intersection(segment(point1_hl, point1_hr), segment(point1_hl, point1_hr)), false);
    EXPECT_EQ(intersection(segment(point1_hl, point1_hr), segment(point1_hr, sommet(10,0))), false);


    EXPECT_EQ(intersection(line2h, segment(sommet(-5,2), sommet(5,2))), false);

    EXPECT_EQ(intersection(segment(sommet(-5,0), sommet(5,0)), segment(sommet(1,2), sommet(0,4))), false);
    EXPECT_EQ(intersection(segment(sommet(-5,0), sommet(5,0)), segment(sommet(1,2), sommet(1,2))), false);
}

TEST(obstacle, segments) {
    obstacle o1;
    o1.vertices.push_back(sommet(1, 1));
    o1.vertices.push_back(sommet(3, 1));
    o1.vertices.push_back(sommet(3, 3));
    o1.vertices.push_back(sommet(1, 3));
    auto line0 = o1.segments(0);
    EXPECT_EQ(line0.begin().x(), 1);
    EXPECT_EQ(line0.begin().y(), 1);

    EXPECT_EQ(line0.end().x(), 3);
    EXPECT_EQ(line0.end().y(), 1);
}

TEST(obstacle, constains_inside) {
    obstacle o1;
    o1.vertices.push_back(sommet(1, 1));
    o1.vertices.push_back(sommet(3, 1));
    o1.vertices.push_back(sommet(3, 3));
    o1.vertices.push_back(sommet(1, 3));
    sommet out(4, 1);
    sommet in(2, 2);
    sommet bord(2, 1);
    EXPECT_EQ(o1.contains_inside(out), false);
    EXPECT_EQ(o1.contains_inside(in), true);
    EXPECT_EQ(o1.contains_inside(bord), true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}