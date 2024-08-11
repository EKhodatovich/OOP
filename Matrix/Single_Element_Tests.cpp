#include "gtest/gtest.h"
#include "Matrix.hpp"


static Matrix Same_Size_Mat(double value)
{
    Matrix result{ 1,1 };
    result.coeffRef(0, 0) = value;
    return result;
}
namespace
{
    Matrix same_size_mat = Same_Size_Mat(2);
    Matrix diff_size_mat{2,3};
    Matrix empty_mat{};
    const double value = 2.0;
}

class SingleElementMatrix : public ::testing::Test {
protected:
    virtual void SetUp(void) {
        mat.coeffRef(0, 0) = 1;
    }
    virtual void TearDown(void) {
    }
    Matrix mat{1,1};
};

TEST_F(SingleElementMatrix, data_OK) {
    EXPECT_TRUE(mat.data());
}
TEST_F(SingleElementMatrix, cols_1) {
    EXPECT_EQ(mat.cols(), 1);
}
TEST_F(SingleElementMatrix, rows_1) {
    EXPECT_EQ(mat.rows(), 1);
}
TEST_F(SingleElementMatrix, validity_OK) {
    EXPECT_TRUE(mat.isValid());
}
TEST_F(SingleElementMatrix, coeffRef_0_0_OK) {
    mat.coeffRef(0, 0) = 1;
    EXPECT_DOUBLE_EQ(mat.coeffRef(0,0), 1);
}
TEST_F(SingleElementMatrix, coeffRef_x_x_FAIL) {
    try 
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 1);
        EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 1);
        EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 1);
    }
    catch (std::out_of_range& err)
    {
        SUCCEED();
    }

}


TEST_F(SingleElementMatrix, and_Emat_mult_FAIL) {
    Matrix result = mat * empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(SingleElementMatrix, and_Emat_summ_FAIL) {
    Matrix result = mat + empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(SingleElementMatrix, and_Emat_substr_FAIL) {
    Matrix result = mat - empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST_F(SingleElementMatrix, and_DSmat_mult_FAIL) {
    Matrix result = mat * diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(SingleElementMatrix, and_DSmat_summ_FAIL) {
    Matrix result = mat + diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(SingleElementMatrix, and_DSmat_substr_FAIL) {
    Matrix result = mat - diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST_F(SingleElementMatrix, and_SSmat_mult_OK) {
    Matrix result = mat * same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2);
}
TEST_F(SingleElementMatrix, and_SSmat_summ_OK) {
    Matrix result = mat + same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 3);
}
TEST_F(SingleElementMatrix, and_SSmat_substr_OK) {
    Matrix result = mat - same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), -1);
}


TEST_F(SingleElementMatrix, and_double_mult_OK) {
    Matrix result = mat * value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2);
}
TEST_F(SingleElementMatrix, and_double_div_OK) {
    Matrix result = mat / value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0.5);
}



TEST_F(SingleElementMatrix, assign_OK) {
    Matrix result = mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), mat.coeffRef(0, 0));
}

TEST_F(SingleElementMatrix, and_Emat_mult_and_assign_FAIL) {
    mat = empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST_F(SingleElementMatrix, and_Emat_summ_and_assign_FAIL) {
    mat += empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST_F(SingleElementMatrix, and_Emat_substr_and_assign_FAIL) {
    mat -= empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}

TEST_F(SingleElementMatrix, and_DSmat_mult_and_assign_FAIL) {
    mat *= diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}
TEST_F(SingleElementMatrix, and_DSmat_summ_and_assign_FAIL) {
    mat += diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}
TEST_F(SingleElementMatrix, and_DSmat_substr_and_assign_FAIL) {
    mat -= diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}

TEST_F(SingleElementMatrix, and_SSmat_mult_and_assign_OK) {
    mat *= same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2);
}
TEST_F(SingleElementMatrix, and_SSmat_summ_and_assign_OK) {
    mat += same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 3);
}
TEST_F(SingleElementMatrix, and_SSmat_substr_and_assign_OK) {
    mat -= same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), -1);
}


TEST_F(SingleElementMatrix, and_double_mult_and_assign_OK) {
    mat *= value;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2);
}
TEST_F(SingleElementMatrix, and_double_div_and_assign_OK) {
    mat /= value;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0.5);
}





TEST_F(SingleElementMatrix, resize_0_0_FAIL)
{
    mat.resize(0, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST_F(SingleElementMatrix, resize_1_0_FAIL)
{
    mat.resize(1, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST_F(SingleElementMatrix, resize_1_1_OK)
{
    mat.resize(1, 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
}


TEST_F(SingleElementMatrix, set_identity_OK)
{
    mat.coeffRef(0, 0) = 3;
    mat.setIdentity();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
}
TEST_F(SingleElementMatrix, set_zero_OK)
{
    mat.setZero();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0);
}
TEST_F(SingleElementMatrix, set_constants_OK)
{
    mat.setConstants(2.0);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2.0);
}

TEST_F(SingleElementMatrix, resize_and_set_constants_OK)
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
TEST_F(SingleElementMatrix, resize_and_set_identity_OK)
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
TEST_F(SingleElementMatrix, resize_and_set_zero_OK)
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



TEST_F(SingleElementMatrix, transpose_OK)
{
    Matrix result = mat.transpose();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
}
TEST_F(SingleElementMatrix, inverse_OK)
{
    mat.coeffRef(0, 0) = -4;
    Matrix result = mat.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), -0.25);
}
TEST_F(SingleElementMatrix, det_OK)
{
    double result = mat.det();
    EXPECT_EQ(result, mat.coeffRef(0,0));
}
TEST_F(SingleElementMatrix, double_and_mat_mult_OK)
{
    Matrix result = value * mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2);
}
