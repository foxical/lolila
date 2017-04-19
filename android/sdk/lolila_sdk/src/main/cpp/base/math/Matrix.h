//
// Created by Administrator on 2017/3/29.
//

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <string>
using namespace std;

class Matrix{
public:

    Matrix(const int& row,const int& col);
    Matrix(const Matrix&);
    Matrix(const int& row,const int& col,const float[]);
    ~Matrix();
public:
    int col()const;
    int row()const;
    int itemCount()const;

public:

    Matrix add(const Matrix&)const;
    Matrix minus(const Matrix&)const;
    Matrix scalarMultiply(const float&)const;
    Matrix multiply(const Matrix&)const;
    Matrix transpose()const;
    float determinant()const;
    Matrix cofactors()const;
    Matrix invert()const;

public:

    static Matrix add(const Matrix& ,const Matrix&);
    static Matrix minus(const Matrix& ,const Matrix&);
    static Matrix scalarMultiply(const Matrix&,const float&);
    static Matrix multiply(const Matrix& ,const Matrix&);
    static Matrix transpose(const Matrix&);


public:

    static Matrix createIdentityMatrix(const int n);

public:

    bool isSingular()const;
    bool isSquare()const;
    bool isInvertible()const;

public:

    string toString()const;
    const char* c_str() const;

public:
    void set(const int& rowIdx,const int& colIdx,const float& val);
    void set(const int& idx,const float& val);
    float get(const int& rowIdx,const int& colIdx)const;
    float get(const int& idx)const;

public:
    //Matrix& operator=(const Matrix&);

private:
    Matrix();
private:
    const int _row;
    const int _col;
    float* _items;
};

#endif //__MATRIX_H__
