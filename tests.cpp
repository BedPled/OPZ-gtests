#include "gtest/gtest.h"
#include "lib.h"

TEST (OPZtest, makeOPZ) {
    EXPECT_EQ(  "1 2 + 4 * 3 + " ,makeOPZ("(1+2)*4+3"));
}


TEST (OPZtest, add) {
    EXPECT_EQ(  1+2+6+8+10 ,resultOPZ(makeOPZ("1+2+6+8+10")));
}

TEST (OPZtest, sub) {
    EXPECT_EQ(  10-9-5-6-10 ,resultOPZ(makeOPZ("10-9-5-6-10")));
}


TEST (OPZtest, expression) {
    EXPECT_EQ(  (1+2)*4+3 ,resultOPZ(makeOPZ("(1+2)*4+3")));
    EXPECT_EQ(  3+(1+2)*4 ,resultOPZ(makeOPZ("3+(1+2)*4")));
    EXPECT_EQ(  resultOPZ(makeOPZ("(1+2)*4+3")) ,resultOPZ(makeOPZ("3+4*(1+2)")));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
