#pragma once

#include <iostream>
#include <vector>
#include <cmath>




template <typename T> class Matrix
{
private:
	unsigned rows;
	unsigned cols;
	//matrix data
	std::vector<std::vector<T> > data;

	void initMatrix(std::vector<std::vector<T> >&, unsigned, unsigned);

	
	

public:
	//usefull static tools
	static const double pi ;
	static double deg2rad(double);

	//constructors
	Matrix();
	Matrix(unsigned rowNum, unsigned colNum, const T& initParam);
	~Matrix();

	//methods
	unsigned get_rows() const;
	unsigned get_cols() const;
	void print_data();
	Matrix<T>& singular();
	Matrix<T>& rotX(double);
	Matrix<T>& rotY(double);
	Matrix<T>& rotZ(double);
	
	//Method for bvh files motion calculation
	Matrix<T>& homogenous_transform();
	Matrix<T>& input_offset(const double offset[]);

	//operators overloading
	Matrix<T>& operator=(const Matrix<T>& r);
	T& operator()(const unsigned& row, const unsigned& col);
	const T& operator()(const unsigned& row, const unsigned& col) const;

	//matrix
	Matrix<T> operator+(const Matrix<T>& r);
	Matrix<T>& operator+=(const Matrix<T>& r);
	Matrix<T> operator-(const Matrix<T>& r);
	Matrix<T>& operator-=(const Matrix<T>& r);
	Matrix<T> operator*(const Matrix<T>& r);
	Matrix<T>& operator*=(const Matrix<T>& r);

	//scalar
	Matrix<T> operator+(const T& r);
	Matrix<T> operator-(const T& r);
	Matrix<T> operator*(const T& r);
	Matrix<T> operator/(const T& r);

	//vector
	std::vector<T> operator*(const std::vector<T>& r);





};

//const double pi = std::acos(-1);

template <typename T>
Matrix<T>::Matrix()
{
}
/*
template <typename T>
void Matrix<T>::initMatrix(std::vector<std::vector<double> >& data, unsigned cols, unsigned rows)
{	

	std::vector<std::vector<double> > tempData(cols, std::vector<double>(rows, 0));
	data = tempData;
} */
template <typename T>
Matrix<T>::Matrix(unsigned rowsNumber, unsigned colsNumber,  const T& initParam)
{
	this->rows = rowsNumber;
	this->cols = colsNumber;
	this->data.resize(rows);
	for (unsigned i = 0; i < data.size(); i++)
		data[i].resize(cols, initParam);
	//initMatrix(this->data,this->rows, this->cols);
}
template <typename T>
Matrix<T>::~Matrix()
{
}

template<typename T>
unsigned Matrix<T>::get_rows() const
{
	return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const
{
	return this->cols;
}

template<typename T>
void Matrix<T>::print_data()
{
	std::cout << "Matrix:" << std::endl; 
	for (unsigned i= 0; i < this->data.size(); i++)
	{
		for (unsigned j=0; j < this->data[i].size(); j++)
			{ std::cout << this->data[i][j] << " ";}
		std::cout << std::endl;
	}
}

template<typename T>
Matrix<T>& Matrix<T>::singular()
{
	for(unsigned i=0; i < this->get_rows(); i++)
		this->data[i][i] = 1.0;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::homogenous_transform()
{
	cols++;
	rows++;
	data.resize(rows);
	for (unsigned i = 0; i < data.size(); i++)
		data[i].resize(cols);

	for (unsigned i = 0; i < rows; i++)
		data[i][cols-1] = 1.0;

	for (unsigned i = 0; i < cols - 1; i++)
		data[rows-1][i] = 0.0; 

	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::input_offset(const double offset[])
{	
	for (unsigned i = 0; i < rows-1; i++)
	{
		data[i][cols-1] = offset[i];
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& r)
{	
	if (&r == this)
		return *this;

	unsigned new_rows = r.get_rows();
	unsigned new_cols = r.get_cols();
	data.resize(new_rows);
	for (unsigned i = 0; i < data.size(); i++)
		data[i].resize(new_cols);

	for (unsigned i = 0; i < new_rows; i++) {
		for (unsigned j = 0; j < new_cols; j++)
		{
			data[i][j] = r(i, j);
		}
	}
	rows = new_rows;
	cols = new_cols;
	return *this;

}

template<typename T>
T & Matrix<T>::operator()(const unsigned & row, const unsigned & col)
{
	return this->data[row][col];
}

template<typename T>
const T & Matrix<T>::operator()(const unsigned & row, const unsigned & col) const
{
	return this->data[row][col];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& r)
{
	Matrix result(rows, cols, 0.0);

		for (unsigned i = 0; i < rows; i++)
			for (unsigned j = 0; j < cols; j++)
			{
				result(i, j) = this->data[i][j] + r(i, j);
			}
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& r)
{
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
		{
			 this->data[i][j] += r(i, j);
		}
	return *this;

}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& r)
{
	Matrix result(rows, cols, 0.0);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
		{
			result(i, j) = this->data[i][j] - r(i, j);
		}
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& r)
{
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
		{
			this->data[i][j] -= r(i, j);
		}
	return *this;

}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& r)
{	
	unsigned rows = r.get_rows();
	unsigned cols = r.get_cols();
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			for (unsigned k = 0; k < rows; k++)
				result(i, j) += this->data[i][k] * r(k, j);
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& r)
{
	Matrix result = (*this) * r;
	*this = result;
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] + r;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] - r;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] * r;
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator/(const T & r)
{
	Matrix result(rows, cols, 0.0);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result(i, j) = this->data[i][j] / r;
		}
	}

	return result;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& r)
{
	std::vector<T> result;
	result.resize(rows);
	for (unsigned i = 0; i<rows; i++) {
		for (unsigned j = 0; j<cols; j++) {
			result[i] = this->data[i][j] * r[j];
		}
	}

	return result;
}
template<typename T>
double Matrix<T>::deg2rad(double angle)
{	
	double result =  std::acos(-1) / 180.0*angle; 
	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::rotX(double angle)
{
	double radians = Matrix<double>::deg2rad(angle);
	Matrix<double> rotation_matrix(4, 4, 0.0);
	//rotationa around x axis declaration
	rotation_matrix(0, 0) = 1.0;
	rotation_matrix(0, 1) = 0.0;
	rotation_matrix(0, 2) = 0.0;
	rotation_matrix(0, 3) = 0.0;

	rotation_matrix(1, 0) = 0.0;
	rotation_matrix(1, 1) = std::cos(radians);
	rotation_matrix(1, 2) = -(std::sin(radians));
	rotation_matrix(1, 3) = 0.0;

	rotation_matrix(2, 0) = 0.0;
	rotation_matrix(2, 1) = std::sin(radians);
	rotation_matrix(2, 2) = std::cos(radians);
	rotation_matrix(2, 3) = 0.0;

	rotation_matrix(3, 0) = 0.0;
	rotation_matrix(3, 1) = 0.0;
	rotation_matrix(3, 2) = 0.0;
	rotation_matrix(3, 3) = 1.0;
	//-------------------------------------

	Matrix<double> result = (*this) * rotation_matrix;
	*this = result;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::rotY(double angle)
{
	double radians = Matrix<double>::deg2rad(angle);
	Matrix<double> rotation_matrix(4, 4, 0.0);
	//rotationa around x axis declaration
	rotation_matrix(0, 0) = std::cos(radians);
	rotation_matrix(0, 1) = 0.0;
	rotation_matrix(0, 2) = std::sin(radians);
	rotation_matrix(0, 3) = 0.0;

	rotation_matrix(1, 0) = 0.0;
	rotation_matrix(1, 1) = 1.0;
	rotation_matrix(1, 2) = 0.0;
	rotation_matrix(1, 3) = 0.0;

	rotation_matrix(2, 0) = -(std::sin(radians));
	rotation_matrix(2, 1) = 0.0;
	rotation_matrix(2, 2) = std::cos(radians);
	rotation_matrix(2, 3) = 0.0;

	rotation_matrix(3, 0) = 0.0;
	rotation_matrix(3, 1) = 0.0;
	rotation_matrix(3, 2) = 0.0;
	rotation_matrix(3, 3) = 1.0;
	//-------------------------------------

	//std::cout << std::endl;
	Matrix<double> result = (*this) * rotation_matrix;
	*this = result;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::rotZ(double angle)
{
	double radians = Matrix<double>::deg2rad(angle);
	Matrix<double> rotation_matrix(4, 4, 0.0);
	//rotationa around x axis declaration
	rotation_matrix(0, 0) = std::cos(radians);
	rotation_matrix(0, 1) = -(std::sin(radians));
	rotation_matrix(0, 2) = 0.0;
	rotation_matrix(0, 3) = 0.0;

	rotation_matrix(1, 0) = std::sin(radians);
	rotation_matrix(1, 1) = std::cos(radians);
	rotation_matrix(1, 2) = 0.0;
	rotation_matrix(1, 3) = 0.0;

	rotation_matrix(2, 0) = 0.0;
	rotation_matrix(2, 1) = 0.0;
	rotation_matrix(2, 2) = 1.0;
	rotation_matrix(2, 3) = 0.0;

	rotation_matrix(3, 0) = 0.0;
	rotation_matrix(3, 1) = 0.0;
	rotation_matrix(3, 2) = 0.0;
	rotation_matrix(3, 3) = 1.0;
	//-------------------------------------

	//std::cout << std::endl;
	Matrix<double> result = (*this) * rotation_matrix;
	*this = result;
	return *this;
}

