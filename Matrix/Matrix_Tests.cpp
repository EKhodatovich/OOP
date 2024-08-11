#include "gtest/gtest.h"
#include "Matrix.hpp"

Matrix Same_Size_Mat()
{
    Matrix result{ 3,3 };
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            result.coeffRef(i, j) = 2 * (double)(i + j);
            result.coeffRef(i, j);
        }
    }
    return result;
}
Matrix Same_Size_Vect()
{
    Matrix result{ 3,1 };
    for (size_t i = 0; i < 3; i++)
    {
        result.coeffRef(i, 0) = i*2;
    }
    return result;
}

Matrix Mat_x_x(size_t size)
{
    Matrix result{ size,size };
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            result.coeffRef(i, j) = (i==j ? 0.0 : 1.0);
        }
    }
    return result;
}

namespace
{
    Matrix same_size_mat = Same_Size_Mat();
    Matrix mat_4_4 = Mat_x_x(4);
    Matrix mat_5_5 = Mat_x_x(5);
    Matrix same_size_vect = Same_Size_Vect();
    Matrix diff_size_mat{ 2,1 };
    Matrix empty_mat{};
    double value = 2.0;
    double precision = 0.001;
}

class Square_Matrix : public ::testing::Test {
protected:
    virtual void SetUp(void) {
        mat = Matrix(3,3);
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                mat.coeffRef(i, j) = i + j;
            }
        }
    }
    virtual void TearDown(void) {
    }

    Matrix mat;
};


TEST_F(Square_Matrix, data_OK) {
    EXPECT_TRUE(mat.data());
}
TEST_F(Square_Matrix, cols_3) {
    EXPECT_EQ(mat.cols(), 3);
}
TEST_F(Square_Matrix, rows_3) {
    EXPECT_EQ(mat.rows(), 3);
}
TEST_F(Square_Matrix, validity_OK) {
    EXPECT_TRUE(mat.isValid());
}
TEST_F(Square_Matrix, coeffRef_x_x_FAIL) {
    try
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(0, 4), 1);
        EXPECT_DOUBLE_EQ(mat.coeffRef(4, 0), 1);
        EXPECT_DOUBLE_EQ(mat.coeffRef(4, 4), 1);
    }
    catch (std::out_of_range& err)
    {
        SUCCEED();
    }

}


TEST_F(Square_Matrix, and_Emat_mult_FAIL) {
    Matrix result = mat * empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Square_Matrix, and_Emat_summ_FAIL) {
    Matrix result = mat + empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Square_Matrix, and_Emat_substr_FAIL) {
    Matrix result = mat - empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST_F(Square_Matrix, and_DSmat_mult_FAIL) {
    Matrix result = mat * diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Square_Matrix, and_DSmat_summ_FAIL) {
    Matrix result = mat + diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST_F(Square_Matrix, and_DSmat_substr_FAIL) {
    Matrix result = mat - diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}

TEST_F(Square_Matrix, assign_OK1) {

    {
        Matrix result = mat;
        auto m1 = result;
    }
}


TEST_F(Square_Matrix, and_SSvect_mult_OK) {
    Matrix result = mat * same_size_vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.coeffRef(0, 0), 10);
    EXPECT_EQ(result.coeffRef(1, 0), 16);
    EXPECT_EQ(result.coeffRef(2, 0), 22);
}
TEST_F(Square_Matrix, and_SSvect_summ_FAIL) {
    Matrix result = mat + same_size_vect;
    EXPECT_FALSE(result.isValid());
}
TEST_F(Square_Matrix, and_SSvect_substr_FAIL) {
    Matrix result = mat - same_size_vect;
    EXPECT_FALSE(result.isValid());
}


TEST_F(Square_Matrix, and_SSmat_mult_OK) {
    Matrix result = mat * same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 10,16,22,16,28,40,22,40,58 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3),values[i]);
    }
}
TEST_F(Square_Matrix, and_SSmat_sum_OK) {
    Matrix result = mat + same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,3,6,3,6,9,6,9,12 };


    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}


TEST_F(Square_Matrix, and_IDmat_sum_and_assing_OK) {
    Matrix ID1 = Matrix::identity(3, 3);
    Matrix ID2 = Matrix::identity(3, 3);
    Matrix result = ID1 + ID2;
    for (size_t i = 0; i < 3;i++)
    {
        for (size_t j = 0; j < 3;j++)
        {
            EXPECT_DOUBLE_EQ((i == j ? 2.0 : 0.0), result.data()[i * result.cols() + j]);
            EXPECT_DOUBLE_EQ((i == j ? 2.0 : 0.0), result.coeffRef(i, j));
        }
    }
}



TEST_F(Square_Matrix, and_SSmat_substr_OK) {
    Matrix result = mat - same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,-1,-2,-1,-2,-3,-2,-3,-4 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}





TEST_F(Square_Matrix, and_double_mult_OK) {
    Matrix result = mat * value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,2,4,2,4,6,4,6,8 };
    for (size_t i = 0; i<9;i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i/3, i%3), values[i]);
    }
}
TEST_F(Square_Matrix, and_double_div_OK) {
    Matrix result = mat / value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,0.5,1,0.5,1,1.5,1,1.5,2 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}



TEST_F(Square_Matrix, assign_OK) {
    Matrix result = mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i/3, i%3), mat.coeffRef(i/3, i%3));
    }
}



TEST_F(Square_Matrix, and_Emat_mult_and_assign_FAIL) {
    mat = empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST_F(Square_Matrix, and_Emat_summ_and_assign_FAIL) {
    mat += empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST_F(Square_Matrix, and_Emat_substr_and_assign_FAIL) {
    mat -= empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}



TEST_F(Square_Matrix, and_DSmat_mult_and_assign_FAIL) {
    mat *= diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}
TEST_F(Square_Matrix, and_DSmat_summ_and_assign_FAIL) {
    mat += diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}
TEST_F(Square_Matrix, and_DSmat_substr_and_assign_FAIL) {
    mat -= diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}


TEST_F(Square_Matrix, and_SSvect_mult_and_assign_OK) {
    mat *= same_size_vect;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.coeffRef(0, 0), 10);
    EXPECT_EQ(mat.coeffRef(1, 0), 16);
    EXPECT_EQ(mat.coeffRef(2, 0), 22);
}
TEST_F(Square_Matrix, and_SSvect_summ_and_assign_FAIL) {
    mat += same_size_vect;
    EXPECT_FALSE(mat.isValid());
}
TEST_F(Square_Matrix, and_SSvect_substr_and_assign_FAIL) {
    mat -= same_size_vect;
    EXPECT_FALSE(mat.isValid());
}


TEST_F(Square_Matrix, and_SSmat_mult_and_assign_OK) {
    mat *= same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 10,16,22,16,28,40,22,40,58 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3),values[i]);
    }
}
TEST_F(Square_Matrix, and_SSmat_sum_and_assign_OK) {
    mat += same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,3,6,3,6,9,6,9,12 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}





TEST_F(Square_Matrix, and_SSmat_substr_and_assign_OK) {
    mat -= same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,-1,-2,-1,-2,-3,-2,-3,-4 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}


TEST_F(Square_Matrix, and_double_mult_and_assign_OK) {
    mat *= value;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,2,4,2,4,6,4,6,8 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}
TEST_F(Square_Matrix, and_double_div_and_assign_OK) {
    mat /= value;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,0.5,1,0.5,1,1.5,1,1.5,2 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}





TEST_F(Square_Matrix, resize_0_0_FAIL)
{
    mat.resize(0, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST_F(Square_Matrix, resize_1_0_FAIL)
{
    mat.resize(1, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST_F(Square_Matrix, resize_1_1_OK)
{
    mat.resize(1, 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
}


TEST_F(Square_Matrix, set_identity_OK)
{
    mat.setIdentity();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 2), 1);
}
TEST_F(Square_Matrix, set_zero_OK)
{
    mat.coeffRef(0, 0) = 3;
    mat.setZero();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 2), 0);
}
TEST_F(Square_Matrix, set_constants_OK)
{
    mat.setConstants(3.0);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 2), 3.0);
}

TEST_F(Square_Matrix, resize_and_set_constants_OK)
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
TEST_F(Square_Matrix, resize_and_set_identity_OK)
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
TEST_F(Square_Matrix, resize_and_set_zero_OK)
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



TEST_F(Square_Matrix, transpose_OK)
{
    mat.coeffRef(0, 1) = 8;
    mat.coeffRef(0, 2) = 16;
    Matrix result = mat.transpose();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 1), 3);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 2), 4);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 8);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 16);
}

TEST_F(Square_Matrix, det_OK)
{
    mat.coeffRef(0, 2) = 3;
    double result = mat.det();
    EXPECT_NEAR(result, -1, precision);
}

TEST_F(Square_Matrix, det_4_4_OK)
{
    Matrix result{ 3,3 };
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            result.coeffRef(i, j) = (i == 0 ? 1 : (i == j ? 0 : 1));
        }
    }
    EXPECT_DOUBLE_EQ(result.det(), 1.0);
}
TEST_F(Square_Matrix, inverse_OK)
{
    mat.coeffRef(0, 2) = 3;
    Matrix result = mat.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 1, -5, 3,-2,6,-3,1,-2,1 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_NEAR(result.coeffRef(i / 3, i % 3), values[i], precision);
    }
    result *= mat;
    for (size_t i = 0; i < 3;i++)
    {
        for (size_t j = 0; j < 3;j++)
        {
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.data()[i * result.cols() + j], precision);
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.coeffRef(i, j), precision);
        }
    }
}

TEST_F(Square_Matrix, inverse_4_4_OK)
{
    Matrix result = mat_4_4.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);
    EXPECT_TRUE(result.isValid());
    double values[16];
    for (size_t i = 0; i < 4;i++)
    {
        for (size_t j = 0; j < 4;j++)
        {
            values[i * 4 + j] = (i == j ? (double)-0.6667 : 0.3333);
        }
    }
    for (size_t i = 0; i < 16;i++)
    {
        EXPECT_NEAR(result.coeffRef(i / 4, i % 4), values[i], precision);
    }
    result *= mat_4_4;
    for (size_t i = 0; i < 4;i++)
    {
        for (size_t j = 0; j < 4;j++)
        {
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.coeffRef(i, j), precision);
        }
    }
}
TEST_F(Square_Matrix, inverse_5_5_OK)
{
    Matrix result = mat_5_5.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 5);
    EXPECT_EQ(result.cols(), 5);
    EXPECT_TRUE(result.isValid());
    double values[25];
    for (size_t i = 0; i < 5;i++)
    {
        for (size_t j = 0; j < 5;j++)
        {
            values[i * 5 + j] = (i == j ? (double)-0.75 : 0.25);
        }
    }
    for (size_t i = 0; i < 25;i++)
    {
        EXPECT_NEAR(result.coeffRef(i / 5, i % 5), values[i], precision);
    }
    result *= mat_5_5;
    for (size_t i = 0; i < 5;i++)
    {
        for (size_t j = 0; j < 5;j++)
        {
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.coeffRef(i, j), precision);
        }
    }
}

TEST_F(Square_Matrix, double_and_mat_mult_OK)
{
    Matrix result = value * mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,2,4,2,4,6,4,6,8 };
    for (size_t i = 0; i < 9;i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}

TEST_F(Square_Matrix, det_5_5_OK)
{
    Matrix result{ 5, 5 };
    result.coeffRef(0, 0) = 2;
    result.coeffRef(1, 0) = 2;
    result.coeffRef(2, 0) = -1;
    result.coeffRef(3, 0) = -3;
    result.coeffRef(4, 0) = 2;
    result.coeffRef(0, 1) = 2;
    result.coeffRef(1, 1) = 2;
    result.coeffRef(2, 1) = 2;
    result.coeffRef(3, 1) = 3;
    result.coeffRef(4, 1) = 1;
    result.coeffRef(0, 2) = 0;
    result.coeffRef(1, 2) = 2;
    result.coeffRef(2, 2) = 0;
    result.coeffRef(3, 2) = 0;
    result.coeffRef(4, 2) = 2;
    result.coeffRef(0, 3) = 0;
    result.coeffRef(1, 3) = 0;
    result.coeffRef(2, 3) = 1;
    result.coeffRef(3, 3) = 0;
    result.coeffRef(4, 3) = -1;
    result.coeffRef(0, 4) = 0;
    result.coeffRef(1, 4) = 1;
    result.coeffRef(2, 4) = 0;
    result.coeffRef(3, 4) = 3;
    result.coeffRef(4, 4) = 3;

    double res = result.det();
    EXPECT_DOUBLE_EQ(res, 24);

}
