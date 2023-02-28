#ifndef BASICOPERATIONS_HPP
#define BASICOPERATIONS_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

template <typename T>
uint32_t transposeMatrix(Matrix<T> &matrix, Matrix<T> *result)
{
    if (matrix.getCols() != result->getRows() ||
        matrix.getRows() != result->getCols())
    {
        return ErrorCode::invalidMatrixSize;
    }

    for(size_t i = 0; i < matrix.getRows(); i++)
    {
        for(size_t j = 0; j < matrix.getCols(); j++)
        {
            result->matrix[j][i] = matrix.matrix[i][j];
        }
    }

    return ErrorCode::success;
}

template <typename T>
Matrix<T> operator*(Matrix<T> &left, Matrix<T> &right)
{
    if (left.getCols() != right.getRows()) 
    {
        throw std::invalid_argument("Incorrect matrix sizes.");
    }

    Matrix<T> result(left.getRows(), right.getCols());
    for (size_t i = 0; i < result.getRows(); i++) 
    {
        for (size_t j = 0; j < result.getCols(); j++) 
        {
            size_t sum = 0;
            for (size_t k = 0; k < left.getCols(); k++) 
            {
                sum += left.matrix[i][k] * right.matrix[k][j];
            }

            result.matrix[i][j] = sum;
        }
    }

    return result;
}

template <typename T>
Vector<T> operator*(Matrix<T> &matrix, Vector<T> &vector)
{
    if (matrix.getCols() != vector.getSize())
    {
        throw std::invalid_argument("Incorrect sizes.");
    }

    Vector<T> result(matrix.getRows());
    for (int i = 0; i < matrix.getRows(); i++)
    {
        for (int j = 0; j < matrix.getCols(); j++)
        {
            result.vector[i] = matrix.matrix[i][j] * vector.vector[j];
        }
    }

    return result;
}

template <typename T>
Matrix<T> operator*(Vector<T> &rowVector, Vector<T> &colVector)
{
    Matrix<T> result(rowVector.getSize(), colVector.getSize());
    for (int i = 0; i < rowVector.getSize(); i++) 
    {
        for (int j = 0; j < colVector.getSize(); j++) 
        {
            result.matrix[i][j] = rowVector.vector[i] * colVector.vector[j];
        }
    }

    return result;
}

template <typename T>
Matrix<T> operator*(T num, Matrix<T> &matrix)
{
    Matrix<T> result(matrix.getRows(), matrix.getCols());
    for (int i = 0; i < matrix.getRows(); i++) 
    {
        for (int j = 0; j < matrix.getCols(); j++) 
        {
            result.matrix[i][j] *= num;
        }
    }

    return result;
}

template <typename T>
Matrix<T> operator-(Matrix<T> &matrix1, Matrix<T> &matrix2)
{
    if ((matrix1.getCols() != matrix2.getCols()) ||
        (matrix1.getRows() != matrix2.getRows()))
    {
        throw std::invalid_argument("Incorrect sizes.");
    }

    Matrix<T> result(matrix1.getRows(), matrix1.getCols());
    for (int i = 0; i < matrix1.getRows(); i++) 
    {
        for (int j = 0; j < matrix1.getCols(); j++) 
        {
            result.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
        }
    }

    return result;
}

template <typename T>
Vector<T> operator+(Vector<T> &left, Vector<T> &right)
{
    if (left.getSize() != right.getSize())
    {
        throw std::invalid_argument("Incorrect vector sizes.");
    }

    Vector<T> result(left.getSize());
    for (size_t i = 0; i < left.getSize(); i++)
    {
        result.vector[i] = left.vector[i] + right.vector[i];
    }

    return result;
}

template <typename T>
uint32_t activateNeuronLayer(double (*function)(double x), Vector<T> &layer, Vector<T> *result)
{
    if (layer.getSize() != result->getSize())
    {
        return ErrorCode::invalidVectorSize;
    }

    T nums[layer.getSize()];
    for(size_t i = 0; i < layer.getSize(); i++)
    {   
        nums[i] = function(layer.vector[i]);
    }

    result->setSizedData(nums, layer.getSize());

    return ErrorCode::success;
}

#endif // !BASICOPERATIONS_HPP