#ifndef MATH_H
#define MATH_H

#include "Algorithm.h"
#include "AuditLog.h"

class Matrix
{
public:
    Matrix(int rows, int cols, bool isRandomValues = true);

    Matrix(int rows, int cols, double **value);

    ~Matrix();

    int getRows();
    
    int getCols();

    uint32_t getElement(int i, int j, double *element);

    uint32_t setData(Matrix &source);

    uint32_t setElement(int i, int j, double value);

    double **matrix;

protected:

private:
    const int rows;
    const int cols;
};

class Vector
{
public:
    Vector(double *nums, int size);

    Vector(double num, int size);

    Vector(int size);

    ~Vector();

    int getSize();
    
    uint32_t setSizedData(double *nums, int size);

    uint32_t getElement(int i, double *element);

    double* getAllElements();
    
    double *vector;

protected:

private:
    
    const bool isDynamicVector;

    int size;
};

namespace BasicOperations
{
    uint32_t transposeMatrix(Matrix &matrix, Matrix *result);

    uint32_t multiplyMatrix2Vector(Matrix &matrix, Vector &vector, Vector *result);

    uint32_t sumVector2Vector(Vector &vector1, Vector &vector2, Vector *result);

    uint32_t sumMatrix2VMatrix(Matrix &matrix1, Matrix &matrix2, Matrix *result);

    uint32_t activateNeuronLayer(double (*function)(double x), Vector &layer, Vector *result);
};

#endif // !MATH_H