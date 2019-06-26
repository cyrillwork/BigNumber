#include <iostream>
#include <gtest/gtest.h>

#include "../bignumber.h"

using namespace std;

TEST(TEST1, add)
{
    //Arrange
    BigNumber a1 = {"999999999999"};
    BigNumber b1 = {"12345"};
    //act
    a1 += 1;
    //assert
    ASSERT_EQ (a1.getDecString(), "1000000000000");
    //act
    a1 += b1;
    //assert
    EXPECT_EQ (a1.getDecString(), "1000000012345");
}

TEST(TEST2, dev)
{
    //Arrange
    BigNumber a1 = {"200"};
    //act
    a1 = a1/4;
    //assert
    ASSERT_EQ (a1.getDecString(), "50");
}

TEST(TEST3, mul)
{
    //Arrange
    BigNumber a1 = {"100"};
    BigNumber b1 = {"200"};
    //act
    a1 = a1 * 100;
    //assert
    ASSERT_EQ (a1.getDecString(), "10000");
    //act
    a1 = a1 * b1;
    //assert
    EXPECT_EQ (a1.getDecString(), "2000000");
}

TEST(TEST4, diff)
{
    //Arrange
    BigNumber a1 = {"100"};
    BigNumber b1 = {"200"};
    BigNumber c1 = {"300"};
    //act
    bool cond1 = (a1 == b1);
    //assert
    ASSERT_EQ (cond1, false);
    //act
    bool cond2 = (a1 < b1);
    //assert
    ASSERT_EQ (cond2, true);
    //act
    bool cond3 = (a1 >= c1);
    //assert
    ASSERT_EQ (cond3, false);
    //act
    bool cond4 = (a1 <= b1);
    //assert
    ASSERT_EQ (cond4, true);
}

int main(int argc, char *argv[])
{
    cout << "Unit test for bignumber" << endl;

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

