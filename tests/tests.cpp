#include "gtest/gtest.h"

#include <boost/any.hpp>
#include "mock_adapter.hpp"
#include "avu.hpp"

TEST(AVU, ZeroArguments)
{
    std::vector<boost::any> vec = {};

    auto msg = avu::unmarshal<0>(vec);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(msg.empty());
}

TEST(AVU, AllRequired)
{
    std::vector<boost::any> vec = {1, 'a', 3.0, "foo"};

    int a = 0;
    char b = '\0';
    double c = 0;
    const char* d = "";

    auto msg = avu::unmarshal<3>(vec, a, b, c, d);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(msg.empty());
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 'a');
    EXPECT_EQ(c, 3.0);
    EXPECT_EQ(d, "foo");
}

TEST(AVU, MoreArgumentsProvided)
{
    std::vector<boost::any> vec = {1, 'a'};

    int a = 0;
    char b = '\0';
    double c = 0;
    const char* d = "bar";

    auto msg = avu::unmarshal<2>(vec, a, b, c, d);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(msg.empty());
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 'a');
    EXPECT_EQ(c, 0);
    EXPECT_EQ(d, "bar");
}

TEST(AVU, ItemsExistsForNonRequiredArguments)
{
    std::vector<boost::any> vec = {1, 'a', 3.0};

    int a = 0;
    char b = '\0';
    double c = 0;
    const char* d = "bar";

    auto msg = avu::unmarshal<2>(vec, a, b, c, d);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(msg.empty());
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 'a');
    EXPECT_EQ(c, 3.0);
    EXPECT_EQ(d, "bar");
}
