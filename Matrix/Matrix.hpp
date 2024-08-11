#pragma once

#include <cstddef>
class Matrix final {
	size_t rows_num {};
	size_t columns_num {};
	double* head = nullptr;

public:
    Matrix() {rows_num = 0; columns_num = 0; head = nullptr;};
	Matrix(size_t cols);
	Matrix(size_t rows, size_t cols);
	~Matrix();

	Matrix(const Matrix& mat);

	Matrix operator*(const Matrix& mat) const;
	Matrix operator-(const Matrix& mat) const;
	Matrix operator+(const Matrix& mat) const;

	Matrix operator*(double value) const;
	Matrix operator/(double value) const;

	Matrix& operator=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);

	Matrix& operator*=(double value);
	Matrix& operator/=(double value);

	bool isValid() const;

	void resize(size_t rows, size_t cols);

	const double& coeffRef(size_t rowIdx, size_t colIdx) const;
	double& coeffRef(size_t rowIdx, size_t colIdx);

	const double* data() const;
	double* data();

	size_t rows() const;
	size_t cols() const;

	Matrix& setIdentity();
	Matrix& setZero();
	Matrix& setConstants(const double value);

	Matrix& setIdentity(size_t rows, size_t cols);
	Matrix& setZero(size_t rows, size_t cols);
	Matrix& setConstants(size_t rows, size_t cols, const double value);

	Matrix transpose() const;
	Matrix inverse() const;
	double det() const;

	static Matrix identity(size_t rows, size_t cols);
	static Matrix zeros(size_t rows, size_t cols);
	static Matrix constants(size_t rows, size_t cols, const double value);



	friend Matrix operator*(const double value, const Matrix& mat);

private:
	Matrix matrix_sum(const Matrix& mat, double(*oper)(double a, double b)) const;
	Matrix multiply(double value, double(*oper)(double a, double b)) const;
	double algebraic_addition(size_t element_i, size_t element_j) const;
	double& coef(size_t rowIdx, size_t colIdx) const;
};
