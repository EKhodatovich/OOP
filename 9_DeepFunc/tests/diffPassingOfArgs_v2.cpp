#include "deepfunction.hpp"
#include <gtest/gtest.h>

using namespace testing;

int globVar = 1;
const int globConstVar = 2;

namespace
{
    int namespaceVar = 3;

    int addOne(int a)
    {
        return a+1;
    }
    void addToIntRef(int &b)
    {
        b+=2;
    }
    void addValToIntRef(int& a, int b)
    {
        a+=b;
    }
    void addRefToIntRef(int& a, int& b)
    {
        a+=b;
    }
    void printIntRef(int& a )
    {
        std::cout << a;
    }
    void printConstIntRef(const int& a )
    {
        std::cout << a;
    }
    void printStringInt(std::string& str, int a)
    {
        str+= std::to_string(a);
    }
    void printStringIntRef(std::string& str, int& a)
    {
        str+= std::to_string(a);
    }
    void printStringConstIntRef(std::string& str, const int& a)
    {
        str+= std::to_string(a);
    }


}
TEST(diffPassingOfArgs, addOne)
{
    int localVar = 5;
    ASSERT_EQ((deep<addOne, 4>(globVar)), 5 );
    ASSERT_EQ((deep<addOne, 4>(globConstVar)), 6 );
    ASSERT_EQ((deep<addOne, 4>(namespaceVar)), 7 );
    ASSERT_EQ((deep<addOne, 4>(localVar)), 9 );
    ASSERT_EQ((deep<addOne, 4>(6)), 10 );
}

TEST(diffPassingOfArgs, addToIntRef)
{
    int localVar = 5;
    deep<addToIntRef, 4>(globVar);
    ASSERT_EQ(globVar, 1 + 2*4);
    //deep<addToIntRef, 4>(globConstVar);
    //ASSERT_EQ(globConstVar, 6 );
    deep<addToIntRef, 4>(namespaceVar);
    ASSERT_EQ(namespaceVar, 3 + 2*4 );
    deep<addToIntRef, 4>(localVar);
    ASSERT_EQ(localVar, 5 + 2*4 );
    deep<addToIntRef, 4>(6);

    globVar = 1;
    namespaceVar = 3;
}


TEST(diffPassingOfArgs, addValToIntRef)
{
    int localVar = 5;
    deep<addValToIntRef, 4>(globVar, globVar);
    ASSERT_EQ(globVar, 1+1+2+4+8);
    // deep<addValToIntRef, 4>(globConstVar, globConstVar);
    // ASSERT_EQ(globConstVar, 2+2+4+8+16 );
    deep<addValToIntRef, 4>(namespaceVar, namespaceVar);
    ASSERT_EQ(namespaceVar, 3+3+6+12+24 );
    deep<addValToIntRef, 4>(localVar, localVar);
    ASSERT_EQ(localVar, 5+5+10+20+40 );


    globVar = 1;
    namespaceVar = 3;
    localVar = 5;

    deep<addValToIntRef, 4>(globVar, globConstVar);
    ASSERT_EQ(globVar, 1+2*4);
    // deep<addValToIntRef, 4>(globConstVar, namespaceVar);
    // ASSERT_EQ(globConstVar, 2+2+4+8+16 );
    deep<addValToIntRef, 4>(namespaceVar, localVar);
    ASSERT_EQ(namespaceVar, 3+5*4);
    globVar = 1;
    deep<addValToIntRef, 4>(localVar, globVar);
    ASSERT_EQ(localVar, 5+1*4);

    globVar = 1;
    namespaceVar = 3;
}

TEST(diffPassingOfArgs, addRefToIntRef)
{
    int localVar = 5;
    deep<addRefToIntRef, 4>(globVar, globVar);
    ASSERT_EQ(globVar, 1+1+2+4+8);
    // deep<addValToIntRef, 4>(globConstVar, globConstVar);
    // ASSERT_EQ(globConstVar, 2+2+4+8+16 );
    deep<addRefToIntRef, 4>(namespaceVar, namespaceVar);
    ASSERT_EQ(namespaceVar, 3+3+6+12+24 );
    deep<addRefToIntRef, 4>(localVar, localVar);
    ASSERT_EQ(localVar, 5+5+10+20+40 );

    globVar = 1;
    namespaceVar = 3;
    localVar = 5;

    deep<addRefToIntRef, 4>(namespaceVar, localVar);
    ASSERT_EQ(namespaceVar, 3+5*4);
    globVar = 1;
    deep<addRefToIntRef, 4>(localVar, globVar);
    ASSERT_EQ(localVar, 5+1*4);

    globVar = 1;
    namespaceVar = 3;
    localVar = 5;
}

TEST(diffPassingOfArgs, printIntRef)
{
    int localVar = 5;
    std::cout << "global variable: \t";
    deep<printIntRef, 5>(globVar);
    std::cout << std::endl;
    std::cout << "namespace variable: \t";
    deep<printIntRef, 5>(namespaceVar);
    std::cout << std::endl;
    std::cout << "local variable: \t";
    deep<printIntRef, 5>(localVar);
    std::cout << std::endl;
    std::cout << "temporal variable: \t";
    deep<printIntRef, 5>(6);
    std::cout << std::endl;
}


TEST(diffPassingOfArgs, printConstIntRef)
{
    int localVar = 5;
    std::cout << "global variable: \t";
    deep<printConstIntRef, 5>(globVar);
    std::cout << std::endl;
    std::cout << "global const variable: \t";
    deep<printConstIntRef, 5>(globConstVar);
    std::cout << std::endl;
    std::cout << "namespace variable: \t";
    deep<printConstIntRef, 5>(namespaceVar);
    std::cout << std::endl;
    std::cout << "local variable: \t";
    deep<printConstIntRef, 5>(localVar);
    std::cout << std::endl;
    std::cout << "temporal variable: \t";
    deep<printConstIntRef, 5>(6);
    std::cout << std::endl;
}

TEST(diffPassingOfArgs, printStringInt)
{
    int localVar = 5;
    std::string str{};
    deep<printStringInt, 5>(str, globVar);
    ASSERT_STREQ(str.c_str(), "11111"); str="";
    deep<printStringInt, 5>(str, globConstVar);
    ASSERT_STREQ(str.c_str(), "22222"); str="";
    deep<printStringInt, 5>(str, namespaceVar);
    ASSERT_STREQ(str.c_str(), "33333"); str="";
    deep<printStringInt, 5>(str, localVar);
    ASSERT_STREQ(str.c_str(), "55555"); str="";
    deep<printStringInt, 5>(str, 6);
    ASSERT_STREQ(str.c_str(), "66666"); str="";
}

TEST(diffPassingOfArgs, printStringIntRef)
{
    int localVar = 5;
    std::string str{};
    deep<printStringIntRef, 5>(str, globVar);
    ASSERT_STREQ(str.c_str(), "11111"); str="";
    //deep<printStringIntRef, 5>(str, globConstVar);
    //ASSERT_STREQ(str.c_str(), "22222"); str="";
    deep<printStringIntRef, 5>(str, namespaceVar);
    ASSERT_STREQ(str.c_str(), "33333"); str="";
    deep<printStringIntRef, 5>(str, localVar);
    ASSERT_STREQ(str.c_str(), "55555"); str="";
    deep<printStringIntRef, 5>(str, 6);
    ASSERT_STREQ(str.c_str(), "66666"); str="";
}

TEST(diffPassingOfArgs, printStringConstIntRef)
{
    int localVar = 5;
    std::string str{};
    deep<printStringConstIntRef, 5>(str, globVar);
    ASSERT_STREQ(str.c_str(), "11111"); str="";
    deep<printStringConstIntRef, 5>(str, globConstVar);
    ASSERT_STREQ(str.c_str(), "22222"); str="";
    deep<printStringConstIntRef, 5>(str, namespaceVar);
    ASSERT_STREQ(str.c_str(), "33333"); str="";
    deep<printStringConstIntRef, 5>(str, localVar);
    ASSERT_STREQ(str.c_str(), "55555"); str="";
    deep<printStringConstIntRef, 5>(str, 6);
    ASSERT_STREQ(str.c_str(), "66666"); str="";
}


