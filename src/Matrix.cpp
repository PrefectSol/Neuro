#include "Matrix.h"

Matrix::Matrix(int rows, int cols, bool isRandomValues)
    : rows(rows), cols(cols), size(rows * cols)
{
    if (rows < 0 || cols < 0)
    {
        throw std::runtime_error("Cannot create the matrix.");
    }

    if (!isRandomValues || size == 0)
    {
        isZero = true;
        return;
    }

    matrix = new double*[rows];
    for(int i = 0; i < rows; i++)
    {
        matrix[i] = new double[cols];
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            matrix[i][j] = isRandomValues ? getRandomDouble() : 0;
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

Matrix::~Matrix()
{
    for(int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
}

int Matrix::getSize()
{
    return size;
}

int Matrix::getRows()
{
    return rows;
}

int Matrix::getCols()
{
    return cols;
}

bool Matrix::isZeroMatrix()
{
    return isZero;
}

int Matrix::getValue(int i, int j)
{
    return matrix[i][j];
}

uint32_t Matrix::setValue(int i, int j, int value)
{
    if ((i >= rows || i < 0) || (j >= cols || j < 0))
    {
        return ErrorCode::indexOutsideTheMatrix;
    }

    matrix[i][j] = value;

    return ErrorCode::success;
}

uint32_t Matrix::multiply(const Matrix &mat1, const Matrix &mat2, Matrix result)
{
    return ErrorCode::success;
}

uint32_t Matrix::sum(const Matrix &mat1, const Matrix &mat2, Matrix result)
{
    return ErrorCode::success;
}