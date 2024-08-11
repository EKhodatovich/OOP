#include "gtest/gtest.h"
#include "Matrix.hpp"

TEST(StaticMembers, new_set_zero_OK)
{
    Matrix result = Matrix::zeros(1, 2);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 0.0);
    try
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 0.0);
    }
    catch (std::out_of_range& err) {
        SUCCEED();
    }
    try
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 0.0);
    }
    catch (std::out_of_range& err) {
        SUCCEED();
    }
}
TEST(StaticMembers, new_set_identity_OK)
{
    Matrix result = Matrix::identity(3, 2);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 1), 0.0);
}
TEST(StaticMembers, new_set_constants_OK)
{
    Matrix result = Matrix::constants(3, 2, 2.0);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 1), 2.0);
}
