#include "pch.h"
#include "Matrix.hpp"
#include <iostream>


namespace
{
    Matrix other_mat = Matrix(1, 1);
    const double value = 2;
}

class EmptyMatrix : public ::testing::Test {
protected:
    virtual void SetUp(void) {
        other_mat.coeffRef(0, 0) = 1;
    }
    virtual void TearDown(void) {
    }
    Matrix mat{};
};

TEST_F(EmptyMatrix, data_FAIL) {
    EXPECT_FALSE(mat.data());
}
TEST_F(EmptyMatrix, cols_0) {
    EXPECT_EQ(mat.cols(), 0);
}
TEST_F(EmptyMatrix, rows_0) {
    EXPECT_EQ(mat.rows(), 0);
}
TEST_F(EmptyMatrix, validity_FAIL) {
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, and_mat_mult_FAIL) {
    Matrix result = mat * other_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, and_mat_summ_FAIL) {
    Matrix result = mat + other_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, and_mat_substr_FAIL) {
    Matrix result = mat - other_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, and_double_mult_FAIL) {
    Matrix result = mat * value;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, and_double_div_FAIL) {
    Matrix result = mat / value;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}



TEST_F(EmptyMatrix, assign_of_empty_FAIL) {
    Matrix result = mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, assing_to_empty_OK)
{
    mat = other_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
}

TEST_F(EmptyMatrix, and_mat_mult_and_assign_FAIL) {
    mat *= other_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(other_mat.isValid());
}
TEST_F(EmptyMatrix, and_mat_summ_and_assign_FAIL) {
    mat += other_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(other_mat.isValid());
}
TEST_F(EmptyMatrix, and_mat_substr_and_assign_FAIL) {
    mat -= other_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(other_mat.isValid());
}
TEST_F(EmptyMatrix, and_double_mult_and_assign_FAIL) {
    mat *= value;
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, and_double_div_and_assign_FAIL) {
    mat /= value;
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, resize_0_0_FAIL)
{
    mat.resize(0, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, resize_1_0_FAIL)
{
    mat.resize(1, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, resize_1_1_OK)
{
    mat.resize(1, 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
}

TEST_F(EmptyMatrix, coeffRef_0_0_FAIL)
{
    try
    {
        mat.coeffRef(0, 0);
    }
    catch (std::out_of_range)
    {
        SUCCEED();
    }
}
TEST_F(EmptyMatrix, coeffRef_1_1_FAIL)
{
    try
    {
        mat.coeffRef(1, 1);
    }
    catch (std::out_of_range)
    {
        SUCCEED();
    }
}

TEST_F(EmptyMatrix, set_identity_FAIL)
{
    mat.setIdentity();
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, set_zero_FAIL)
{
    mat.setZero();
    EXPECT_FALSE(mat.isValid());
}
TEST_F(EmptyMatrix, set_constants_FAIL)
{
    mat.setConstants(2.0);
    EXPECT_FALSE(mat.isValid());
}

TEST_F(EmptyMatrix, resize_and_set_constants_OK)
{
    mat.setConstants(3, 2, 2.0);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 2.0);
}
TEST_F(EmptyMatrix, resize_and_set_identity_OK)
{
    mat.setIdentity(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}
TEST_F(EmptyMatrix, resize_and_set_zero_OK)
{
    mat.setZero(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}
TEST_F(EmptyMatrix, transpose_FAIL)
{
    Matrix result = mat.transpose();
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, inverse_FAIL)
{
    Matrix result = mat.inverse();
    EXPECT_FALSE(result.isValid());
}
TEST_F(EmptyMatrix, det_NaN)
{
    double result = mat.det();
    EXPECT_NE(result, result);
}
TEST_F(EmptyMatrix, double_and_mat_mult_FAIL)
{
    Matrix result = value * mat;
    EXPECT_FALSE(result.isValid());
}