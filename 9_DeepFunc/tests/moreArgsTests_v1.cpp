#include <gtest/gtest.h>
#include "deepfunction.hpp"

using namespace testing;
namespace
{
int addVar(int a, int b)
{
    return a+b;
}

double addTwoVars (int a, unsigned b, long c)
{
    return a+b+c;
}

void print(int a)
{
    std::cout << a << ", ";
}

std::pair<int, int> addVarToPair (std::pair<int,int> p, int a)
{
    return {p.first+a, p.second+a};
}

}
TEST(moreArgsTests, addVar)
{
    ASSERT_EQ((deep<addVar,1>(5, 1)), 6);
    ASSERT_EQ((deep<addVar,2>(5, 2)), 9);
    ASSERT_EQ((deep<addVar,4>(5, 3)), 5 + 3*4);
    ASSERT_EQ((deep<addVar,10>(5, 1)), 15);

    ASSERT_EQ((deep<addVar,0>(5, 1)), 5);
    ASSERT_EQ((deep<addVar,0>(5, 0)), 5);
    ASSERT_EQ((deep<addVar,0>(5, -2)), 5);
    ASSERT_EQ((deep<addVar,1>(-5, 1)), -4);
    ASSERT_EQ((deep<addVar,1>(0, 1)), 1);
    ASSERT_EQ((deep<addVar,1>(-1, 1)), 0);

    ASSERT_EQ((deep<addVar,0>(5.0, 2)), 5);
    ASSERT_EQ((deep<addVar,1>(-5.0, 1.0)), -4);
    ASSERT_EQ((deep<addVar,1>(0, 1.0)), 1);
    ASSERT_DOUBLE_EQ((deep<addVar,1>(-1.0, 1.0)), 0.0);

    static_assert( std::is_same_v<decltype((deep<addVar,1>(-1.0, -1.0))), double>);
    static_assert( std::is_same_v<decltype((deep<addVar,1>(-1, 1)))     , int>);
    static_assert( std::is_same_v<decltype((deep<addVar,1>(-1, 1.0)))   , int>);
    static_assert( std::is_same_v<decltype((deep<addVar,1>(-1.0, 1)))   , double>);

    static_assert( std::is_same_v<decltype((deep<addVar,1, double>(-1.0, 1))), double>);
    static_assert( std::is_same_v<decltype((deep<addVar,1, int>   (-1.0, 1))), int>);
    static_assert(!std::is_same_v<decltype((deep<addVar,1, int>   (-1.0, 1))), double>);
    static_assert(!std::is_same_v<decltype((deep<addVar,1, double>(-1.0, 1))), int>);
}

TEST(moreArgsTests, addTwo)
{
    ASSERT_DOUBLE_EQ((deep<addTwoVars,1>(5, 1, 1)), 7.0);
    ASSERT_DOUBLE_EQ((deep<addTwoVars,2>(5, 2.0, 2)), 5 + 2 * 4);
    ASSERT_DOUBLE_EQ((deep<addTwoVars,4>(5.0, 2, 2.0)), 5.0 + 2*4 + 2.0 * 4);
    ASSERT_DOUBLE_EQ((deep<addTwoVars,10>(5.0, 2, 2)), 5.0 + 2*10 + 2*10);

    ASSERT_DOUBLE_EQ((deep<addTwoVars,4>(5.5, 1, 0)), 5.0 + 1*4);
    ASSERT_DOUBLE_EQ((deep<addTwoVars,10>(5.5, 0, 1)), 5.0 + 1.0*10);

    ASSERT_EQ((deep<addTwoVars,4>(5.5, 2, 0)), 5+2*4);
}

TEST(moreArgsTests, print)
{
    deep<print, 5>(10);
    std::cout << std::endl;
    deep<print, 1>(20);
    std::cout << std::endl;
    deep<print, 0>(7);
    std::cout << std::endl;
}


TEST(moreArgsTests, addVarToPair)
{
    std::pair<int, int> a {5,6};
    a = deep<addVarToPair, 5>(a, 1);
    std::pair<int,int> b {10, 11};
    ASSERT_EQ(a.first, b.first); ASSERT_EQ(a.second, b.second);

    a = deep<addVarToPair, 1>(a, 2);
    b = {12, 13};
    ASSERT_EQ(a.first, b.first); ASSERT_EQ(a.second, b.second);

    a = deep<addVarToPair, 0>(a, 2);
    ASSERT_EQ(a.first, b.first); ASSERT_EQ(a.second, b.second);
}
