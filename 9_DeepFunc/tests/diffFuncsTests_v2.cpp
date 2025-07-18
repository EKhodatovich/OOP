#include <gtest/gtest.h>
#include "deepfunctionnew.h"

using namespace testing;
namespace
{
    int addOne(int a)
    {
        return a+1;
    }

    double addTwo (int a)
    {
        return a+2.0;
    }

    int addThree (double a)
    {
        return static_cast<int>(a)+3;
    }

    template <typename T>
    requires std::is_arithmetic_v<T>
    T addFour(T a)
    {
        return a + 4.0;
    }

    int print(int a)
    {
        std::cout << a << ", ";
        return a;
    }

    std::pair<int, int> addOnes (std::pair<int,int> p)
    {
        return {p.first+1, p.second+1};
    }

    void voidPrint()
    {
        std::cout << "Hi, ";
    }

}
TEST(diffFuncsTests, addOne)
{
    static_assert(Callable<decltype(addOne), int>);

    ASSERT_EQ((deep<addOne,1>(5)), 6);
    ASSERT_EQ((deep<addOne,2>(5)), 6);
    ASSERT_EQ((deep<addOne,4>(5)), 6);
    ASSERT_EQ((deep<addOne,10>(5)), 6);

    ASSERT_EQ((deep<addOne,0>(5)), 0);
    ASSERT_EQ((deep<addOne,1>(-5)), -4);
    ASSERT_EQ((deep<addOne,1>(0)), 1);
    ASSERT_EQ((deep<addOne,1>(-1)), 0);

    ASSERT_EQ((deep<addOne,0>(5.0)), 0);
    ASSERT_EQ((deep<addOne,1>(-5.0)), -4);
    ASSERT_EQ((deep<addOne,1>(0.0)), 1);
    ASSERT_EQ((deep<addOne,1>(-1.0)), 0);

    static_assert( std::is_same_v<decltype((deep<addOne,1>(-1.0))), int>);
    static_assert( std::is_same_v<decltype((deep<addOne,1>(-1)))  , int>);

    static_assert( std::is_same_v<decltype((deep<addOne,1, int>   (-1.0))), int>);
    static_assert( std::is_same_v<decltype((deep<addOne,1, double>(-1.0))), int>);

    ASSERT_EQ((deep<addOne,1, double>(-1.0)), 0);
    ASSERT_EQ((deep<addOne,1, int>(-1.0)), 0);
    ASSERT_EQ((deep<addOne,1, double>(-1)), 0);
    ASSERT_EQ((deep<addOne,1, int>(-1)), 0);

}

TEST(diffFuncsTests, addTwo)
{
    ASSERT_DOUBLE_EQ((deep<addTwo,1>(5)), 7.0);
    ASSERT_DOUBLE_EQ((deep<addTwo,2>(5)), 7);
    ASSERT_DOUBLE_EQ((deep<addTwo,4>(5.0)), 7);
    ASSERT_DOUBLE_EQ((deep<addTwo,10>(5.0)), 7);

    ASSERT_DOUBLE_EQ((deep<addTwo,4>(5.5)), 7.0);
    ASSERT_DOUBLE_EQ((deep<addTwo,10>(5.5)), 7.0);

    ASSERT_EQ((deep<addTwo,4>(5.5)), 7.0);
}

TEST(diffFuncsTests, addThree)
{
    ASSERT_DOUBLE_EQ((deep<addThree,1>(5)), 8);
    ASSERT_DOUBLE_EQ((deep<addThree,2>(5)), 8);
    ASSERT_DOUBLE_EQ((deep<addThree,4>(5.0)), 8);
    ASSERT_DOUBLE_EQ((deep<addThree,10>(5.0)), 8);

    ASSERT_DOUBLE_EQ((deep<addThree,4>(5.5)), 8);
    ASSERT_DOUBLE_EQ((deep<addThree,10>(5.5)), 8);

    ASSERT_EQ((deep<addThree,4>(5.5)), 8);
}

TEST(diffFuncsTests, addFour)
{
    ASSERT_EQ((deep<addFour<int>,1>(5)), 5 + 4*1);
    ASSERT_EQ((deep<addFour<int>,2>(5)), 5 + 4*1);
    ASSERT_EQ((deep<addFour<double>,4>(5.0)), 5.0 + 4.0*1);
    ASSERT_EQ((deep<addFour<double>,10>(5.0)), 5.0 + 4.0*1);

    ASSERT_DOUBLE_EQ((deep<addFour<int>,4>(5.5)), 5.0 + 4.0*1);
    ASSERT_DOUBLE_EQ((deep<addFour<double>,10>(5.5)), 5.5 + 4.0*1);
}

TEST(diffFuncsTests, print)
{
    deep<print, 5>(5);
    std::cout << std::endl;
    deep<print, 1>(6);
    std::cout << std::endl;
    deep<print, 0>(7);
    std::cout << std::endl;
}

TEST(diffFuncsTests, voidPrint)
{
    deep<voidPrint, 5>();
    std::cout << std::endl;
    deep<voidPrint, 1>();
    std::cout << std::endl;
    deep<voidPrint, 0>();
    std::cout << std::endl;
}

TEST(diffFuncsTests, addOnes)
{
    std::pair<int, int> a {5,6};
    a = deep<addOnes, 5>(a);
    std::pair<int,int> b {6, 7};
    ASSERT_EQ(a.first, b.first); ASSERT_EQ(a.second, b.second);

    a = deep<addOnes, 1>(a);
    b = {7, 8};
    ASSERT_EQ(a.first, b.first); ASSERT_EQ(a.second, b.second);

    a = deep<addOnes, 0>(a);
    ASSERT_NE(a.first, b.first); ASSERT_NE(a.second, b.second);

    std::pair<double, double> c {5.0, 6.0};
    c = deep<addOnes, 6>(c);
    ASSERT_NE(c.first, b.first); ASSERT_NE(c.second, b.second);
}


