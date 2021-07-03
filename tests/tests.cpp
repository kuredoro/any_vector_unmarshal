#include "gtest/gtest.h"

#include <boost/any.hpp>
#include "vector_of_any_unmarshal.hpp"

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

TEST(AVU, ItemsExistsForNonRequiredArgumentsConst)
{
    const std::vector<boost::any> vec = {1, 'a', 3.0};

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

TEST(AVU, UnmarshalToStruct)
{
    const std::vector<boost::any> vec = {1, 'a', 3.0};

    struct {
        int a = 0;
        char b = '\0';
        double c = 0;
        const char* d = "bar";
    } conf;

    auto msg = avu::unmarshal<2>(vec, conf.a, conf.b, conf.c, conf.d);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(msg.empty());
    EXPECT_EQ(conf.a, 1);
    EXPECT_EQ(conf.b, 'a');
    EXPECT_EQ(conf.c, 3.0);
    EXPECT_EQ(conf.d, "bar");
}

TEST(AVU, RequiredOmitted_NoError)
{
    const std::vector<boost::any> vec = {1, 'a', 3.0, "foo"};

    int a = 0;
    char b = '\0';
    double c = 0;
    const char* d = "bar";

    auto msg = avu::unmarshal(vec, a, b, c, d);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(msg.empty());
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 'a');
    EXPECT_EQ(c, 3.0);
    EXPECT_EQ(d, "foo");
}

TEST(AVU, RequiredOmitted_NotEnoughArgs)
{
    const std::vector<boost::any> vec = {1, 'a'};

    int a = 0;
    char b = '\0';
    double c = 0;
    const char* d = "bar";

    auto msg = avu::unmarshal(vec, a, b, c, d);

    if (!msg.empty())
        std::cout << "\nerror: " << msg << "\n\n";

    EXPECT_TRUE(!msg.empty());
    EXPECT_EQ(a, 0);
    EXPECT_EQ(b, '\0');
    EXPECT_EQ(c, 0);
    EXPECT_EQ(d, "bar");
}
