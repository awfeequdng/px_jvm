#include <gtest/gtest.h>
#include <iostream>
#include "arena.hh"

using namespace std;
using namespace testing;

class TestArena : public testing::Test {
public:
    TestArena() {}

protected:
    Arena _arena;
};

TEST_F(TestArena, test1) {
    auto ptr1 = _arena.Amalloc(16);
    EXPECT_EQ(_arena.used(), 16);
    auto ptr2 = _arena.Amalloc(7);
    EXPECT_EQ(_arena.used(), 24);
    _arena.Afree(ptr1, 8);
    EXPECT_EQ(_arena.used(), 24);
    _arena.Afree(ptr2, 8);
    EXPECT_EQ(_arena.used(), 16);
    _arena.Afree(ptr1, 16);
    EXPECT_EQ(_arena.used(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
