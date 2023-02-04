#include "Math.h"

uint32_t BasicOperations::multiplyMatrix2Vector(Matrix &matrix, Vector &vector, Vector *result)
{
    bool isInvalidMatrix = matrix.getCols() != vector.getSize();
    bool isInvalidVector = vector.getSize() != result->getSize();
    if (isInvalidMatrix || isInvalidVector)
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
    if (vector1.getSize() != vector2.getSize() != result->getSize())
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
