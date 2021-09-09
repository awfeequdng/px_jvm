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
    auto ptr = _arena.Amalloc(16);
    EXPECT_EQ(_arena.used(), 16);
    ptr = _arena.Amalloc(7);
    EXPECT_EQ(_arena.used(), 24);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
