#ifndef MATH_H
#define MATH_H

#include "Algorithm.h"
#include "AuditLog.h"

class Matrix
{
public:
    Matrix(int rows, int cols, bool isRandomValues = true);

    ~Matrix();

    int getRows();
    
    int getCols();

    uint32_t getElement(int i, int j, double *element);

protected:

private:
    double **matrix;

    const int rows;
    const int cols;
};

class Vector
{
public:
    Vector(double *nums, int size);

    Vector(int size);

    ~Vector();

    int getSize();
    
    uint32_t setSizedData(double *nums, int size);

    uint32_t getElement(int i, double *element);
    
protected:

private:
    
    const bool isDynamicVector;

    double *vector;
    int size;
};

namespace BasicOperations
{
    uint32_t multiplyMatrix2Vector(Matrix &matrix, Vector &vector, Vector *result);

    uint32_t sumVector2Vector(Vector &vector1, Vector &vector2, Vector *result);
};

#endif // !MATH_H