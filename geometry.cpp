#include <iostream>
#include <vector>
#include <cassert>

#include "geometry.h"

Mat3f::Mat3f() {

}

Mat3f Mat3f::operator*(Mat3f& a) {
	
	Mat3f result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = 0.0f;
			for (int k = 0; k < 3; k++) {
				result[i][j] += rows[i][k] * a.rows[k][j];
			}
		}
	}
	return result;
}

Vec3f Mat3f::operator*(Vec3f& a) {
	Vec3f result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			result[i] = 0.0f;
			for (int k = 0; k < 3; k++) {
				result[i] += rows[i][k] * a[k];
			}
		}
	}
	return result;
}

Mat3f Mat3f::transpose() {
	Mat3f result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = rows[j][i];
		}
	}
	return result;
}

Mat3f Mat3f::inverse() {
	return Mat3f::identity();
}

Mat3f Mat3f::identity() {
	Mat3f E;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			E[i][j] = (i == j ? 1.0f : 0.0f);
		}
	}
	return E;
}

std::ostream& operator<<(std::ostream& s, Mat3f& m) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			s << m[i][j];
			if (j < 2)s << "\t";
		}
		s << "\n";
	}
	return s;
}

#pragma region Mat4f



Mat4f::Mat4f()
{
}

Mat4f Mat4f::operator*(Mat4f& a)
{
	Mat4f result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				result[i][j] += rows[i][k] * a.rows[k][j];
			}
		}
	}
	return result;
}

Vec4f Mat4f::operator*(Vec4f& a)
{
	Vec4f result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			result[i] = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				result[i] += rows[i][k] * a[k];
			}
		}
	}
	return result;
}

Mat4f Mat4f::transpose()
{
	Mat4f result;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = rows[j][i];
		}
	return result;
}

Mat4f Mat4f::inverse()
{
	return Mat4f::identity();
}

Mat4f Mat4f::identity()
{
	Mat4f E;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			E[i][j] = (i == j ? 1.0f : 0.0f);
		}
	return E;
}

std::ostream& operator<<(std::ostream& s, Mat4f& m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			s << m[i][j];
			if (j < 3) s << "\t";
		}
		s << "\n";
	}
	return s;
}
#pragma endregion

Matrix::Matrix(Vec3f v) : m(std::vector<std::vector<float> >(4, std::vector<float>(1, 1.f))), rows(4), cols(1) {
	m[0][0] = v.x;
	m[1][0] = v.y;
	m[2][0] = v.z;
}


Matrix::Matrix(int r, int c) : m(std::vector<std::vector<float> >(r, std::vector<float>(c, 0.f))), rows(r), cols(c) { }

int Matrix::nrows() {
	return rows;
}

int Matrix::ncols() {
	return cols;
}

Matrix Matrix::identity(int dimensions) {
	Matrix E(dimensions, dimensions);
	for (int i = 0; i < dimensions; i++) {
		for (int j = 0; j < dimensions; j++) {
			E[i][j] = (i == j ? 1.f : 0.f);
		}
	}
	return E;
}

std::vector<float>& Matrix::operator[](const int i) {
	assert(i >= 0 && i < rows);
	return m[i];
}

Matrix Matrix::operator*(const Matrix& a) {
	assert(cols == a.rows);
	Matrix result(rows, a.cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			result.m[i][j] = 0.f;
			for (int k = 0; k < cols; k++) {
				result.m[i][j] += m[i][k] * a.m[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::operator*(Vec4f& a)
{
	Matrix result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			result[i][j] = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				result[i][j] += m[i][k] * a[k];
			}
		}
	}
	return result;
}

Matrix Matrix::transpose() {
	Matrix result(cols, rows);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			result[j][i] = m[i][j];
	return result;
}

Matrix Matrix::inverse() {
	assert(rows == cols);
	// augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
	Matrix result(rows, cols * 2);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			result[i][j] = m[i][j];
	for (int i = 0; i < rows; i++)
		result[i][i + cols] = 1;
	// first pass
	for (int i = 0; i < rows - 1; i++) {
		// normalize the first row
		for (int j = result.cols - 1; j >= 0; j--)
			result[i][j] /= result[i][i];
		for (int k = i + 1; k < rows; k++) {
			float coeff = result[k][i];
			for (int j = 0; j < result.cols; j++) {
				result[k][j] -= result[i][j] * coeff;
			}
		}
	}
	// normalize the last row
	for (int j = result.cols - 1; j >= rows - 1; j--)
		result[rows - 1][j] /= result[rows - 1][rows - 1];
	// second pass
	for (int i = rows - 1; i > 0; i--) {
		for (int k = i - 1; k >= 0; k--) {
			float coeff = result[k][i];
			for (int j = 0; j < result.cols; j++) {
				result[k][j] -= result[i][j] * coeff;
			}
		}
	}
	// cut the identity matrix back
	Matrix truncate(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			truncate[i][j] = result[i][j + cols];
	return truncate;
}

std::ostream& operator<<(std::ostream& s, Matrix& m) {
	for (int i = 0; i < m.nrows(); i++) {
		for (int j = 0; j < m.ncols(); j++) {
			s << m[i][j];
			if (j < m.ncols() - 1) s << "\t";
		}
		s << "\n";
	}
	return s;
}