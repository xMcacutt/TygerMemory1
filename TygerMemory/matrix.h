#pragma once
#ifdef TYGERMEM_EXPORTS
#define TYGERMEM __declspec(dllexport)
#else
#define TYGERMEM __declspec(dllimport)
#endif
#include "vector4f.h"

struct TYGERMEM Matrix
{
    // Could instead be Data[4][4], but having a vector4f field makes editing the position directly easier
    float Data[3][4];
    Vector4f Position;

    void SetIdentity();
    // Ty has weird matrix functions that are member functions, but also take in an extra matrix 
    // (usually the same matrix the function is called on for matrix 1, but not always)
    void Scale(Matrix* pMatrix, Vector4f* scale);
    void Scale(Matrix* pMatrix, float scalar);
    void Multiply(Matrix* pMatrix1, Matrix* pMatrix2);
};
