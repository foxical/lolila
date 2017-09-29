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
    Matrix(const int& row,const int& col,const double[]);
    ~Matrix();
public:
    int col()const;
    int row()const;
    int itemCount()const;

public:

    Matrix add(const Matrix&)const;
    Matrix minus(const Matrix&)const;
    Matrix scalarMultiply(const double&)const;
    Matrix multiply(const Matrix&)const;
    Matrix transpose()const;
    double determinant()const;
    Matrix cofactors()const;
    Matrix invert()const;

public:

    static Matrix add(const Matrix& ,const Matrix&);
    static Matrix minus(const Matrix& ,const Matrix&);
    static Matrix scalarMultiply(const Matrix&,const double&);
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
    void set(const int& rowIdx,const int& colIdx,const double& val);
    void set(const int& idx,const double& val);
    double get(const int& rowIdx,const int& colIdx)const;
    double get(const int& idx)const;

public:
    //Matrix& operator=(const Matrix&);

private:
    Matrix();
private:
    const int _row;
    const int _col;
    double* _items;
};

#endif //__MATRIX_H__
