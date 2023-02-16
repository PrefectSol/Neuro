#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../Algorithm.h"
#include "../AuditLog.h"

template<class T>
class Vector
{
public:
    Vector(T *nums, size_t size);

    Vector(T num, size_t size);

    Vector(size_t size);

    ~Vector();

    size_t getSize();
    
    uint32_t setSizedData(const T *nums, size_t size);
    
    T *vector;

protected:

private:
    const bool isDynamicVector;

    const size_t size;
};

template<class T>
Vector<T>::Vector(T *nums, size_t size)
    : isDynamicVector(false), size(size)
{
    this->vector = nums;
}

template<class T>
Vector<T>::Vector(T num, size_t size)
    : isDynamicVector(true), size(size)
{
    vector = new double[size];
    for(int i = 0; i < size; i++)
    {
        vector[i] = num;
    }
}

template<class T>
Vector<T>::Vector(size_t size)
    : isDynamicVector(true), size(size)
{
    vector = new double[size];
    for(int i = 0; i < size; i++)
    {
        vector[i] = 0.f;
    }
}

template<class T>
Vector<T>::~Vector()
{
    if (isDynamicVector)
    {
        delete[] vector;
    }
}

template<typename T>
size_t Vector<T>::getSize()
{
    return size;
}

template<typename T>
uint32_t Vector<T>::setSizedData(const T *nums, size_t size)
{
    if (this->size != size)
    {
        return ErrorCode::invalidVectorSize;
    }

    for(int i = 0; i < size; i++)
    {
        vector[i] = nums[i];
    }

    return ErrorCode::success;
}

#endif // !VECTOR_HPP