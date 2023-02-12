#include "Math.h"

Matrix::Matrix(int rows, int cols, bool isRandomValues)
    : rows(rows), cols(cols)
{
    if (rows < 0 || cols < 0)
    {
        throw std::runtime_error("Cannot create matrix.");
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
        }
    }
}

Matrix::Matrix(int rows, int cols, double **value)
    : rows(rows), cols(cols)
{
    if (rows < 0 || cols < 0)
    {
        throw std::runtime_error("Cannot create matrix.");
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
            matrix[i][j] = value[i][j];
        }
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

int Matrix::getRows()
{
    return rows;
}

int Matrix::getCols()
{
    return cols;
}

uint32_t Matrix::getElement(int i, int j, double *element)
{
    if ((i >= rows || i < 0) || (j >= cols || j < 0))
    {
        return ErrorCode::indexOutsideMatrix;
    }

    *element = matrix[i][j];

    return ErrorCode::success;
}

uint32_t Matrix::setData(Matrix &source)
{
    if (cols != source.getCols() || rows != source.getRows())
    {
        return ErrorCode::invalidMatrixSize;
    }

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            double element;
            source.getElement(i, j, &element);

            matrix[i][j] = element;
        }
    }

    return ErrorCode::success;
}

uint32_t Matrix::setElement(int i, int j, double value)
{
    if (i >= rows || i < 0 ||
        j >= cols || j < 0)
    {
        return ErrorCode::indexOutsideMatrix;
    }

    matrix[i][j] = value;

    return ErrorCode::success;
}
