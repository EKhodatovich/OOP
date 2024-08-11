#include <cmath>
#include <cstring>
#include <stdexcept>
#include "Matrix.hpp"

namespace
{
	const double precision = 0.01;
}

Matrix::Matrix(size_t rows, size_t cols) : rows_num(rows), columns_num(cols)
{
	if (rows != 0 && cols != 0)
	{
		head = new double[cols * rows]();
	}
}

Matrix::Matrix(size_t cols) : Matrix(1,cols) { }



Matrix::~Matrix() 
{
	delete[] head;
}

Matrix::Matrix(const Matrix& mat) : Matrix (mat.rows_num, mat.columns_num)
{
	if (head)
	{
		std::memcpy(head, mat.head, mat.rows_num * mat.columns_num * sizeof(double));
	}
}



Matrix Matrix::operator*(const Matrix& mat) const
{
	if (!isValid() || !mat.isValid() || columns_num != mat.rows_num)
	{
		return Matrix();
	}
	Matrix result( rows_num, mat.columns_num);
	double mult_result = 0;
	for (size_t result_i_index = 0; result_i_index < result.rows_num; ++result_i_index)
	{
		for (size_t result_j_index = 0; result_j_index < result.columns_num; ++result_j_index)
		{
			for (size_t operands_index = 0; operands_index <  columns_num; ++operands_index)
			{
				mult_result +=  coeffRef(result_i_index, operands_index) * mat.coeffRef(operands_index, result_j_index);
			}
			result.coeffRef(result_i_index, result_j_index) = mult_result;
			mult_result = 0;
		}
	}
	return result;
}




static double sum(double a, double b)
{
	return a + b;
}
static double sub(double a, double b)
{
	return a - b;
}


Matrix Matrix::operator+(const Matrix& mat) const
{
	return matrix_sum(mat, sum);
}

Matrix Matrix::operator-(const Matrix& mat) const
{
	return matrix_sum(mat, sub);
}

Matrix Matrix::matrix_sum(const Matrix& mat, double(*operation)(double a, double b)) const
{
	if (!isValid() || !mat.isValid() || columns_num != mat.columns_num || rows_num != mat.rows_num)
	{
		return Matrix();
	}
	Matrix result(rows_num, columns_num);
	for (size_t i_index = 0; i_index < result.rows_num; ++i_index)
	{
		for (size_t j_index = 0; j_index < result.columns_num; ++j_index)
		{
			result.coeffRef(i_index, j_index) = operation(coeffRef(i_index, j_index), mat.coeffRef(i_index, j_index));
		}
	}
	return result;
}


static double mult(double a, double b)
{
	return a * b;
}
static double div(double a, double b)
{
	return a / b;
}

Matrix Matrix::operator*(double value) const
{
	return multiply(value, mult);
}

Matrix Matrix::operator/(double value) const
{
    if (std::abs(value) - precision < 0)
	{
        throw std::invalid_argument("Division by zero");
	}
	return multiply(value, div);
}




Matrix Matrix::multiply(double value, double(*operation)(double a, double b)) const
{
	if (!isValid())
	{
		return Matrix();
	}
	Matrix result(rows_num, columns_num);
	for (size_t i_index = 0; i_index < result.rows_num; ++i_index)
	{
		for (size_t j_index = 0; j_index < result.columns_num; ++j_index)
		{
			result.coeffRef(i_index, j_index) = operation(coeffRef(i_index, j_index), value);
		}
	}
	return result;
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	if (this == &mat)
	{
		return *this;
	}
	delete [] head;
	rows_num = mat.rows_num;
	columns_num = mat.columns_num;
	if (rows_num!=0 && columns_num !=0 )
	{
		head = new double[columns_num * rows_num]();
		std::memcpy(head, mat.head, mat.rows_num*mat.columns_num*sizeof(double));
	}
	else
	{
		head = nullptr;
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& mat)
{
	*this = *this * mat;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& mat)
{
	*this = *this + mat;
	return *this;
}


Matrix& Matrix::operator-=(const Matrix& mat)
{
	*this = *this - mat;
	return *this;
}

Matrix& Matrix::operator*=(double value)
{
	*this = *this * value;
	return *this;
}
Matrix& Matrix::operator/=(double value)
{
	*this = *this / value;
	return *this;
}

bool Matrix::isValid() const
{
	return rows_num!=0 && columns_num!=0;
}

void Matrix::resize(size_t rows, size_t cols)
{
	delete []head;
	rows_num = rows;
	columns_num = cols;
	if (rows_num != 0 && columns_num != 0)
	{
		head = new double[columns_num * rows_num]();
	}
	else
	{
		head = nullptr;
	}
}

const double* Matrix::data() const
{
	return head;
}
double* Matrix::data()
{
	return head;
}

const double& Matrix::coeffRef(size_t rowIdx, size_t colIdx) const
{
	return coef(rowIdx, colIdx);
}

double& Matrix::coeffRef(size_t rowIdx, size_t colIdx)
{
	return coef(rowIdx, colIdx);
}

double& Matrix::coef(size_t rowIdx, size_t colIdx) const
{
	if (rows_num == 0 || columns_num == 0 || rowIdx > rows_num - 1 || colIdx > columns_num - 1)
	{
		throw std::out_of_range("(i,j) is out of range");
	}
	return *(head + rowIdx * columns_num + colIdx);
}


size_t Matrix::rows() const
{
	return rows_num;
}
size_t Matrix::cols() const
{
	return columns_num;
}

Matrix& Matrix::setIdentity()
{
	setConstants(0.0);
	for (size_t i_index = 0; i_index < rows_num && i_index<columns_num; ++i_index)
	{
		coeffRef(i_index, i_index) = 1;
	}
	return *this;
}
Matrix& Matrix::setZero()
{
	return setConstants(0.0);
}
Matrix& Matrix::setConstants(const double value)
{
	std::fill_n(head, rows_num*columns_num, value);
	return *this;
}

Matrix& Matrix::setIdentity(size_t rows, size_t cols)
{
	setConstants(rows, cols, 0.0);
	for (size_t i_index = 0; i_index < rows_num && i_index < columns_num; ++i_index)
	{
		coeffRef(i_index, i_index) = 1;
	}
	return *this;
}
Matrix& Matrix::setZero(size_t rows, size_t cols)
{
	return setConstants(rows, cols, 0.0);
}
Matrix& Matrix::setConstants(size_t rows, size_t cols, const double value)
{
	resize(rows, cols);
	return setConstants(value);
}


Matrix Matrix::transpose() const
{
	if (!isValid())
	{
		return Matrix();
	}
	Matrix result = Matrix(columns_num, rows_num);

	for (size_t i_index = 0; i_index < result.rows_num; ++i_index)
	{
		for (size_t j_index = 0; j_index < result.columns_num; ++j_index)
		{
			result.coeffRef(i_index, j_index) = coeffRef(j_index, i_index);
		}
	}
	return result;
}




static void find_max_leading_elem(const Matrix& upper_trian, const size_t super_j_index, double &max, size_t &curr_elem_i_index)
{
	double curr_elem = 0;
	for (size_t i_index = super_j_index; i_index < upper_trian.rows(); ++i_index)
	{
		curr_elem = upper_trian.coeffRef(i_index, super_j_index);
		if (fabs(curr_elem) > fabs(max))
		{
			max = curr_elem;
			curr_elem_i_index = i_index;
		}
	}
}

static double line_swap(Matrix& upper_trian, const size_t super_j_index, const double max,  const size_t curr_elem_i_index)
{
	if (super_j_index != curr_elem_i_index)
	{
		for (size_t j_index = 0; j_index < upper_trian.cols(); ++j_index)
		{
			std::swap(upper_trian.coeffRef(super_j_index, j_index), upper_trian.coeffRef(curr_elem_i_index, j_index));
			upper_trian.coeffRef(super_j_index, j_index) /= max;
		}
		return -1 * max;
	}
	for (size_t j_index = 0; j_index < upper_trian.cols(); ++j_index)
	{
		upper_trian.coeffRef(super_j_index, j_index) /= max;
	}
	return max;
}
static void matrix_rebuild(Matrix& upper_trian, const size_t super_j_index)
{
	double norm_fact = 0;
	for (size_t i_index = super_j_index + 1; i_index < upper_trian.rows(); ++i_index)
	{
		norm_fact = upper_trian.coeffRef(i_index, super_j_index);
		for (size_t j_index = super_j_index; j_index < upper_trian.cols(); ++j_index)
		{
			upper_trian.coeffRef(i_index, j_index) -= upper_trian.coeffRef(super_j_index, j_index) * norm_fact;
		}
	}
}

double Matrix::det() const
{
	if (!isValid() || columns_num != rows_num)
	{
		return std::nan("0");
	}
	if (columns_num == 1)
	{
		return head[0];
	}
	double result = 1;

	Matrix upper_trian = *this;
	for (size_t super_j_index = 0; super_j_index < upper_trian.columns_num; ++super_j_index)
	{
		double max = 0;

		size_t curr_elem_i_index = 0;
		find_max_leading_elem(upper_trian, super_j_index, max, curr_elem_i_index);
        if (std::abs (max - 0) < precision)
		{
			return 0;
		}
		result *=line_swap(upper_trian, super_j_index, max, curr_elem_i_index);
		matrix_rebuild(upper_trian, super_j_index);
	}
	return result;
}


double Matrix::algebraic_addition(size_t element_i, size_t element_j) const
{
	if (rows_num == 1)
	{
		return 1;
	}
	Matrix mat = Matrix(rows_num - 1, columns_num - 1);

	size_t i_jump = 0;
	size_t j_jump = 0;
	for (size_t i_index = 0; i_index < mat.rows_num; ++i_index)
	{
		if (i_index == element_i)
		{
			++i_jump;
		}
		j_jump = 0;
		for (size_t j_index = 0; j_index < mat.columns_num; ++j_index)
		{
			if (j_index == element_j)
			{
				++j_jump;
			}
			mat.coeffRef(i_index, j_index) = coeffRef(i_index + i_jump, j_index + j_jump);
		}
	}
	return ((element_i + element_j) % 2 != 0) ? -mat.det() : mat.det();
}

Matrix Matrix::inverse() const
{
	double determ = det();

    if (determ != determ || std::abs(determ - 0) < precision)
	{
		return Matrix();
	}
	Matrix result = Matrix(columns_num, rows_num);
	for (size_t i_index = 0; i_index < rows_num; ++i_index)
	{
		for (size_t j_index = 0; j_index < columns_num; ++j_index)
		{
			result.coeffRef(i_index, j_index) = algebraic_addition(j_index, i_index) / determ;
		}
	}
	return result;
}

Matrix Matrix::identity(size_t rows, size_t cols)
{
	Matrix result = Matrix(rows, cols);
	result.setIdentity();
	return result;
}
Matrix Matrix::zeros(size_t rows, size_t cols)
{
	Matrix result = Matrix(rows, cols);
	result.setZero();
	return result;
}
Matrix Matrix::constants(size_t rows, size_t cols, const double value)
{
	Matrix result = Matrix(rows, cols);
	result.setConstants(value);
	return result;
}

Matrix operator*(double value, const Matrix& mat)
{
	return mat * value;
}
