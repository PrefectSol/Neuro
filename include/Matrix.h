#ifndef MATRIX_H
#define MATRIX_H

#include "Algorithm.h"
#include "AuditLog.h"

class Matrix
{
public:
    Matrix(int rows, int cols, bool isRandomValues = true);

    ~Matrix();

    static uint32_t multiply(const Matrix &mat1, const Matrix &mat2, Matrix result);

    static uint32_t sum(const Matrix &mat1, const Matrix &mat2, Matrix result);

    bool isZeroMatrix();
    
    int getSize();

    int getRows();

    int getCols();

    int getValue(int i, int j);

    uint32_t setValue(int i, int j, int value);

protected:

private:
    bool isZero;

    const int rows;
    const int cols;
    const int size;

    double **matrix;
};

#endif // !MATRIX_H