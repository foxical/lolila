//
// Created by Administrator on 2017/3/29.
//

#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix(const int &m, const int &n):_col(m),_row(n),_items(new float[m*n]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = 0.0;
    }
}

Matrix::Matrix(const Matrix & o):_col(o._col),_row(o._row),_items(new float[o._col*o._row]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = o._items[i];
    }
}

Matrix::~Matrix() {
    delete[] _items;
}

int Matrix::col() const {
    return _col;
}

int Matrix::row() const {
    return _row;
}

int Matrix::itemCount() const {
    return _col*_row;
}

Matrix Matrix::add(const Matrix& A,const Matrix& B){
    if( A.col()!=B.col() || A.row()!=B.row() ){
        throw runtime_error("Matrix's spec is  not equal!");
    }
    Matrix result(A.col(),A.row());
    const int itemCount = result.itemCount();
    for(int i=0;i<itemCount;++i){
        result._items[i] = A._items[i]+B._items[i];
    }
    return result;
}

Matrix Matrix::add(const Matrix & A) const {
    return add(*this,A);
}

Matrix Matrix::minus(const Matrix& A,const Matrix& B){
    if( A.col()!=B.col() || A.row()!=B.row() ){
        throw runtime_error("Matrix's spec is  not equal!");
    }
    Matrix result(A.col(),A.row());
    const int itemCount = result.itemCount();
    for(int i=0;i<itemCount;++i){
        result._items[i] = A._items[i]-B._items[i];
    }
    return result;
}

Matrix Matrix::minus(const Matrix & A) const {
    return minus(*this,A);
}

Matrix Matrix::scalarMultiply(const Matrix& o,const float& scalar){
    Matrix result(o);
    const int itemCount = result.itemCount();
    for(int i=0;i<itemCount;++i){
        result._items[i] *= scalar;
    }
    return result;
}

Matrix Matrix::scalarMultiply(const float& scalar)const{
    return scalarMultiply(*this,scalar);
}

string Matrix::toString()const{
    char buff[128];
    string result;
    for( int r=0;r<_row;r++){
        result.append("|");
        for(int c=0;c<_col;++c){
            if(c>0){
                result.append(",");
            }
            sprintf(buff,"%g",_items[c+r*_row]);
            result.append(buff);

        }
        result.append("|\n");
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix& A){

    const int oldItemCount = itemCount();
    const int newItemCount = A.itemCount();
    if( newItemCount>oldItemCount){
        delete[] _items;
        _items = new float[newItemCount];
    }
    _col=A._col;
    _row=A._row;
    for(int i=0;i<newItemCount;++i){
        _items[i] = A._items[i];
    }
    return *this;
}

void Matrix::set(const int& col,const int& row,const float & val){
    if( col<0||col>=_col){
        throw out_of_range("col is out of range!");
    }
    if( row<0||row>=_row){
        throw out_of_range("row is out of range!");
    }
    _items[ col*_col+row] = val;
}
