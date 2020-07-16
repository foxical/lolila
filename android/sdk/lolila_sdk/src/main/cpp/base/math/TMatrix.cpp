//
// Created by tam on 2020/7/3.
//

#include "TMatrix.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <math.h>

template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const int& row,const int& col):_col(col),_row(row),_items(new T[row*col]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = 0L; // T must override '=' operator, and default constructor
    }
}

template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::~TMatrix() {
    delete[] _items;
}

template <typename T,typename OutputAdapter>
int TMatrix<T,OutputAdapter>::col() const {
    return _col;
}

template <typename T,typename OutputAdapter>
int TMatrix<T,OutputAdapter>::row() const {
    return _row;
}

template <typename T,typename OutputAdapter>
int TMatrix<T,OutputAdapter>::itemCount() const {
    return _col*_row;
}

template <typename T,typename OutputAdapter>
T TMatrix<T,OutputAdapter>::get(const int& rowIdx,const int& colIdx)const{
    if( colIdx<0||colIdx>=_col){
        throw out_of_range("colIdx is out of range!");
    }
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range("rowIdx is out of range!");
    }
    return get( rowIdx*_col+colIdx);
}

template <typename T,typename OutputAdapter>
T TMatrix<T,OutputAdapter>::get(const int& idx)const{
    if( idx<0||idx>=itemCount()){
        throw out_of_range("index is out of range!");
    }
    return _items[idx];
}

template <typename T,typename OutputAdapter>
string TMatrix<T,OutputAdapter>::toString()const{
    std::stringstream output;

    output<<("\n");

    for( int r=0;r<_row;r++){
        output<<("|");
        for(int c=0;c<_col;++c){
            if(c>0){
                output<<(",");
            }
            output<<OutputAdapter::toString(get(r,c));
        }
        output<<("|\n");
    }

    return output.str();
}

template <typename T,typename OutputAdapter>
const char* TMatrix<T,OutputAdapter>::c_str() const {
    return toString().c_str();
}


