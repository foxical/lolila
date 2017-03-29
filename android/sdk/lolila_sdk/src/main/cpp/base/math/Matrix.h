//
// Created by Administrator on 2017/3/29.
//

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <string>
using namespace std;

class Matrix{
public:

    Matrix(const int& m,const int& n);
    Matrix(const Matrix&);
    ~Matrix();
public:
    int col()const;
    int row()const;
    int itemCount()const;

public:

    Matrix add(const Matrix&)const;
    Matrix minus(const Matrix&)const;
    Matrix scalarMultiply(const float&)const;

public:

    static Matrix add(const Matrix& ,const Matrix&);
    static Matrix minus(const Matrix& ,const Matrix&);
    static Matrix scalarMultiply(const Matrix&,const float&);

public:

    string toString()const;
public:
    void set(const int& col,const int& row,const float& val);

public:
    Matrix& operator=(const Matrix&);

private:
    Matrix();
private:
    int _row;
    int _col;
    float* _items;
};

#endif //__MATRIX_H__
