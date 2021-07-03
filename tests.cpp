#include "gtest/gtest.h"

#include "avu.hpp"

TEST(AVU, ZeroArguments)
{
    hello();
    EXPECT_EQ(1, 1);
}
