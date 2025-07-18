#include "gtest/gtest.h"
#include "Matrix.hpp"

static Matrix Same_Size_Vect()
{
    Matrix result{ 3 };
    for (size_t i = 0; i<3; i++)
    {
        result.coeffRef(0, i) = 2 * i;
    }
    return result;
}

static Matrix Same_Size_Vect_Trans()
{
    Matrix result{ 3,1 };
    for (size_t i = 0; i < 3; i++)
    {
        result.coeffRef(i, 0) = 2 * i;
    }
    return result;
}

static Matrix Mat()
{
    Matrix result{ 3,2 };
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            result.coeffRef(i, j) = i + j;
        }
    }
    return result;
}

namespace
{
    const Matrix same_size_vect = Same_Size_Vect();
    const Matrix same_size_vect_trans = Same_Size_Vect_Trans();
    const Matrix diff_size_vect{ 2,1 };
    const Matrix mat = Mat();
    const Matrix empty_mat{};
    const double value = 2.0;
}

class Three_Vector : public ::testing::Test {
protected:
    virtual void SetUp(void) {
        vect = Matrix(3);
        vect.coeffRef(0, 0) = 0;
        vect.coeffRef(0, 1) = 1;
        vect.coeffRef(0, 2) = 2;
    }
    virtual void TearDown(void) { }

    // объекты тестового окружения, доступные в каждом тесте
    Matrix vect;
};


TEST_F(Three_Vector, data_OK) {
    EXPECT_TRUE(vect.data());
}
TEST_F(Three_Vector, cols_3) {
    EXPECT_EQ(vect.cols(), 3);
}
TEST_F(Three_Vector, rows_1) {
    EXPECT_EQ(vect.rows(), 1);
}
TEST_F(Three_Vector, validity_OK) {
    EXPECT_TRUE(vect.isValid());
}
TEST_F(Three_Vector, coeffRef_0_2_OK) {
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0,1), 1);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0,2), 2);
}
TEST_F(Three_Vector, coeffRef_x_x_FAIL) {
    try
    {
        EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 1);
        EXPECT_DOUBLE_EQ(vect.coeffRef(0, 4), 1);
        EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 1);
    }
    catch (std::out_of_range& err)
    {
        SUCCEED();
    }

}


TEST_F(Three_Vector, and_Emat_mult_FAIL) {
    Matrix result = vect * empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, and_Emat_summ_FAIL) {
    Matrix result = vect + empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, and_Emat_substr_FAIL) {
    Matrix result = vect - empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST_F(Three_Vector, and_DSvect_mult_FAIL) {
    Matrix result = vect * diff_size_vect;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, and_DSvect_summ_FAIL) {
    Matrix result = vect + diff_size_vect;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, and_DSvect_substr_FAIL) {
    Matrix result = vect - diff_size_vect;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST_F(Three_Vector, and_SSvect_mult_FAIL) {
    Matrix result = vect * same_size_vect;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, and_SSvect_summ_OK) {
    Matrix result = vect + same_size_vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 3);
}
TEST_F(Three_Vector, and_SSvect_substr_OK) {
    Matrix result = vect - same_size_vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), -1);
}


TEST_F(Three_Vector, and_SSvectTrans_mult_OK) {
    Matrix result = vect * same_size_vect_trans;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 10);
}
TEST_F(Three_Vector, and_SSvectTrans_sum_FAIL) {
    Matrix result = vect + same_size_vect_trans;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, and_SSvectTrans_sub_FAIL) {
    Matrix result = vect - same_size_vect_trans;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}

TEST_F(Three_Vector, and_SSmatTrans_mult_OK) {
    Matrix result = vect * mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 5);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 8);
}


TEST_F(Three_Vector, and_double_mult_OK) {
    Matrix result = vect * value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 2);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 4);
}
TEST_F(Three_Vector, and_double_div_OK) {
    Matrix result = vect / value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 0.5);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 1);
}



TEST_F(Three_Vector, assign_OK) {
    Matrix result = vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    for (size_t i =0; i<3; i++)
    EXPECT_DOUBLE_EQ(result.coeffRef(0, i), vect.coeffRef(0, i));
}



TEST_F(Three_Vector, and_Emat_mult_and_assign_FAIL) {
    vect = empty_mat;
    EXPECT_FALSE(vect.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST_F(Three_Vector, and_Emat_summ_and_assign_FAIL) {
    vect += empty_mat;
    EXPECT_FALSE(vect.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST_F(Three_Vector, and_Emat_substr_and_assign_FAIL) {
    vect -= empty_mat;
    EXPECT_FALSE(vect.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}



TEST_F(Three_Vector, and_DSmat_mult_and_assign_FAIL) {
    vect *= diff_size_vect;
    EXPECT_FALSE(vect.isValid());
    EXPECT_TRUE(diff_size_vect.isValid());
}
TEST_F(Three_Vector, and_DSmat_summ_and_assign_FAIL) {
    vect += diff_size_vect;
    EXPECT_FALSE(vect.isValid());
    EXPECT_TRUE(diff_size_vect.isValid());
}
TEST_F(Three_Vector, and_DSmat_substr_and_assign_FAIL) {
    vect -= diff_size_vect;
    EXPECT_FALSE(vect.isValid());
    EXPECT_TRUE(diff_size_vect.isValid());
}


TEST_F(Three_Vector, and_SSvect_mult_and_assign_FAIL) {
    vect *= same_size_vect;
    EXPECT_FALSE(vect.isValid());
}
TEST_F(Three_Vector, and_SSvect_summ_and_assign_OK) {
    vect += same_size_vect;
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 3);
}
TEST_F(Three_Vector, and_SSvect_substr_and_assign_OK) {
    vect -= same_size_vect;
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), -1);
}


TEST_F(Three_Vector, and_SSvectTrans_mult_and_assign_OK) {
    vect *= same_size_vect_trans;
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 1);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 10);
}
TEST_F(Three_Vector, and_SSvectTrans_sum_and_assign_FAIL) {
    vect += same_size_vect_trans;
    EXPECT_FALSE(vect.isValid());
}
TEST_F(Three_Vector, and_SSvectTrans_sub_and_assign_FAIL) {
    vect -= same_size_vect_trans;
    EXPECT_FALSE(vect.isValid());
}

TEST_F(Three_Vector, and_SSvectmat_mult_and_assign_OK) {
    vect *= mat;
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 2);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 5);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 8);
}

TEST_F(Three_Vector, and_double_mult_and_assign_OK) {
    vect *= value;
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 2);
}
TEST_F(Three_Vector, and_double_div_and_assign_OK) {
    vect /= value;
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0.5);
}





TEST_F(Three_Vector, resize_0_0_FAIL)
{
    vect.resize(0, 0);
    EXPECT_FALSE(vect.isValid());
}
TEST_F(Three_Vector, resize_1_0_FAIL)
{
    vect.resize(1, 0);
    EXPECT_FALSE(vect.isValid());
}
TEST_F(Three_Vector, resize_1_1_OK)
{
    vect.resize(1, 1);
    EXPECT_TRUE(vect.isValid());
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 1);
}


TEST_F(Three_Vector, set_identity_OK)
{
    vect.setIdentity();
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 1);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 0);
}
TEST_F(Three_Vector, set_zero_OK)
{
    vect.coeffRef(0, 0) = 3;
    vect.setZero();
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 0);
}
TEST_F(Three_Vector, set_constants_OK)
{
    vect.setConstants(3.0);
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 3.0);
}

TEST_F(Three_Vector, resize_and_set_constants_OK)
{
    vect.setConstants(3, 2, 2.0);
    EXPECT_TRUE(vect.isValid());
    EXPECT_EQ(vect.rows(), 3);
    EXPECT_EQ(vect.cols(), 2);

    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 1), 2.0);
}
TEST_F(Three_Vector, resize_and_set_identity_OK)
{
    vect.setIdentity(3, 2);
    EXPECT_TRUE(vect.isValid());
    EXPECT_EQ(vect.rows(), 3);
    EXPECT_EQ(vect.cols(), 2);

    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 1), 0.0);
}
TEST_F(Three_Vector, resize_and_set_zero_OK)
{
    vect.setZero(3, 2);
    EXPECT_TRUE(vect.isValid());
    EXPECT_EQ(vect.rows(), 3);
    EXPECT_EQ(vect.cols(), 2);

    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 1), 0.0);
}



TEST_F(Three_Vector, transpose_OK)
{
    Matrix result = vect.transpose();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 1);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 2);
}
TEST_F(Three_Vector, inverse_OK)
{
    Matrix result = vect.inverse();
    //EXPECT_FALSE(result.isValid());
}
TEST_F(Three_Vector, det_OK)
{
    double result = vect.det();
    EXPECT_NE(result, result);
}
TEST_F(Three_Vector, double_and_mat_mult_OK)
{
    Matrix result = value * vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 2);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 4);
}
