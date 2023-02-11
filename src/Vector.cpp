#include "Math.h"

Vector::Vector(double *nums, int size)
    : isDynamicVector(false)
{
    this->size = size;
    this->vector = nums;
}

Vector::Vector(double num, int size)
    : isDynamicVector(true)
{
    this->size = size;

    vector = new double[size];
    for(int i = 0; i < size; i++)
    {
        vector[i] = num;
    }
}

Vector::Vector(int size)
    : isDynamicVector(true)
{
    this->size = size;

    vector = new double[size];
    for(int i = 0; i < size; i++)
    {
        vector[i] = 0.f;
    }
}

Vector::~Vector()
{
    if (isDynamicVector)
    {
        delete[] vector;
    }
}

int Vector::getSize()
{
    return size;
}

uint32_t Vector::setSizedData(double *nums, int size)
{
    if (this->size != size)
    {
        return ErrorCode::incorrectVectorSize;
    }

    for(int i = 0; i < size; i++)
    {
        vector[i] = nums[i];
    }

    return ErrorCode::success;
}

uint32_t Vector::getElement(int i, double *element)
{
    if (i >= size || i < 0)
    {
        return ErrorCode::indexOutsideVector;
    }

    *element = vector[i];

    return ErrorCode::success;
}

double* Vector::getAllElements()
{
    return vector;
}
