#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../Algorithm.h"
#include "../AuditLog.h"

template<class T>
class Matrix
{
public:
    Matrix(size_t rows, size_t cols, bool isRandomValues = true);

    Matrix(size_t rows, size_t cols, T **values);

    ~Matrix();

    uint32_t setData(Matrix<T> &source);

    size_t getRows();
    
    size_t getCols();

    T **matrix;

protected:

private:
    const size_t rows;
    const size_t cols;
};

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols, bool isRandomValues)
    : rows(rows), cols(cols)
{
    if (rows < 0 || cols < 0)
    {
        throw std::runtime_error("Cannot create matrix.");
    }

    matrix = new T*[rows];
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = new T[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            matrix[i][j] = isRandomValues ? getRandomDouble() : 0;
        }
    }
}

template<class T>
Matrix<T>::Matrix(size_t rows, size_t cols, T **values)
    : rows(rows), cols(cols)
{
    if (rows < 0 || cols < 0)
    {
        throw std::runtime_error("Cannot create matrix.");
    }

    matrix = new T*[rows];
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = new T[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            matrix[i][j] = values[i][j];
        }
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    for(int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

template<typename T>
size_t Matrix<T>::getRows()
{
    return rows;
}

template<typename T>
size_t Matrix<T>::getCols()
{
    return cols;
}

template<typename T>
uint32_t Matrix<T>::setData(Matrix<T> &source)
{
    if (cols != source.cols || rows != source.rows)
    {
        return ErrorCode::invalidMatrixSize;
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            matrix[i][j] = source.matrix[i][j];
        }
    }

    return ErrorCode::success;
}

#endif // !MATRIX_HPP