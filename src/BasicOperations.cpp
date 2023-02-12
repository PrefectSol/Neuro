#include "Math.h"

uint32_t BasicOperations::transposeMatrix(Matrix &matrix, Matrix *result)
{
    if (matrix.getCols() != result->getRows() ||
        matrix.getRows() != result->getCols())
    {
        return ErrorCode::invalidMatrixSize;
    }

    for(int i = 0; i < matrix.getRows(); i++)
    {
        for(int j = 0; j < matrix.getCols(); j++)
        {
            result->matrix[j][i] = matrix.matrix[i][j];
        }
    }

    return ErrorCode::success;
}

uint32_t BasicOperations::multiplyMatrix2Vector(Matrix &matrix, Vector &vector, Vector *result)
{
    bool isInvalidMatrix = matrix.getCols() != vector.getSize();
//    bool isInvalidVector = vector.getSize() != result->getSize();
    if (isInvalidMatrix)
    {
        return ErrorCode::invalidArguments;
    }

    double nums[result->getSize()];
    for(int i = 0; i < matrix.getRows(); i++)
    {
        double sum = 0;
        for(int j = 0; j < matrix.getCols(); j++)
        {
            double matrixElement, vectorElement;
            matrix.getElement(i, j, &matrixElement);
            vector.getElement(j, &vectorElement);

            sum += matrixElement * vectorElement;
        }

        nums[i] = sum;
    }
    
    result->setSizedData(nums, result->getSize());

    return ErrorCode::success;
}

uint32_t BasicOperations::sumVector2Vector(Vector &vector1, Vector &vector2, Vector *result)
{
    if (vector1.getSize() != vector2.getSize() || vector1.getSize() != result->getSize())
    {
        return ErrorCode::incorrectVectorSize;
    }

    double nums[vector1.getSize()];
    for(int i = 0; i < vector1.getSize(); i++)
    {
        double vec1Element, vec2Element;
        vector1.getElement(i, &vec1Element);
        vector2.getElement(i, &vec2Element);

        nums[i] = vec1Element + vec2Element;
    }

    result->setSizedData(nums, result->getSize());

    return ErrorCode::success;
}

uint32_t BasicOperations::activateNeuronLayer(double (*function)(double x), Vector &layer, Vector *result)
{
    if (layer.getSize() != result->getSize())
    {
        return ErrorCode::incorrectVectorSize;
    }

    double nums[layer.getSize()];
    for(int i = 0; i < layer.getSize(); i++)
    {
        double element;
        layer.getElement(i, &element);
        
        nums[i] = function(element);
    }

    result->setSizedData(nums, layer.getSize());

    return ErrorCode::success;
}

uint32_t BasicOperations::sumMatrix2VMatrix(Matrix &matrix1, Matrix &matrix2, Matrix *result)
{
    if (matrix1.getCols() != matrix2.getCols() ||
        matrix1.getRows() != matrix2.getRows() ||
        matrix1.getCols() != result->getCols() ||
        matrix1.getRows() != result->getRows())
    {
        return ErrorCode::invalidMatrixSize;
    }

    for(int i = 0; i < result->getRows(); i++)
    {
        for(int j = 0; j < result->getCols(); j++)
        {
            double element1, element2;

            element1 = matrix1.getElement(i, j, &element1);
            element2 = matrix2.getElement(i, j, &element2);
            result->setElement(i, j, element1 + element2);
        }
    }

    return ErrorCode::success;
}
