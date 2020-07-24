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
#include "../utils/AndroidLog.h"

template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const int& row,const int& col):_col(col),_row(row),_items(new T[row*col]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = 0L; // T must override '=' operator, and default constructor
    }
}

template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const int& row,const int& col,const double items[]):_col(col),_row(row),_items(new T[row*col]){
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = items[i];
    }
}

template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const TMatrix<T,OutputAdapter> & o):_col(o._col),_row(o._row),_items(new T[o._col*o._row]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = o._items[i];
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
const T& TMatrix<T,OutputAdapter>::get(const int& rowIdx,const int& colIdx)const{
    if( colIdx<0||colIdx>=_col){
        throw out_of_range("colIdx is out of range!");
    }
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range("rowIdx is out of range!");
    }
    return get( rowIdx*_col+colIdx);
}

template <typename T,typename OutputAdapter>
const T& TMatrix<T,OutputAdapter>::get(const int& idx)const{
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

template <typename T,typename OutputAdapter>
bool TMatrix<T,OutputAdapter>::isZeroRow(const int& rowIdx)const{
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    for( int colIdx=0;colIdx<_col;++colIdx){
        const T& Mij =  get(rowIdx,colIdx);
        if( OutputAdapter::isZero( Mij )==false){
            return false;
        }
    }

    return true;
}

template <typename T,typename OutputAdapter>
int TMatrix<T,OutputAdapter>::getFirstOneColIdx(const int& rowIdx)const{
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    for( int colIdx=0;colIdx<_col;++colIdx){
        const T& Mij=  get(rowIdx,colIdx);
        if(OutputAdapter::isZero( Mij )){
            continue;//
        }else if(OutputAdapter::isEqualOne( Mij)){
            return colIdx;
        }else{
            return -1;
        }
    }

    return -99;
}

template <typename T,typename OutputAdapter>
bool TMatrix<T,OutputAdapter>::isMostSimplest(void)const{
    int lastZeroRowIdx=-1;
    int lastFirstOneColIdx=-1;

    for(int rowIdx=0;rowIdx<_row;++rowIdx){
        int firstOneColIdxOfRow = getFirstOneColIdx(rowIdx);
        if( firstOneColIdxOfRow==-1 ){
            return false; // can not find the ‘first one’ element
        }else if( firstOneColIdxOfRow==-99){
            lastZeroRowIdx = rowIdx; // this row is zero row, save the row idx in 'lastZeroRowIdx'
            continue;
        }

        if(firstOneColIdxOfRow<=lastFirstOneColIdx){
            return false; // the col idx is less then the last first one element's col idx
        }

        if(lastZeroRowIdx!=-1){
            return false; // the zero row is above of this row
        }

        // check the elements that with same column in other rows, they must be all zero
        const int& col = firstOneColIdxOfRow;
        for(int r=0;r<_row;++r){
            if(r!=rowIdx){
                if(OutputAdapter::isZero(get(r,col))==false){
                    return false;
                }
            }
        }

        // !! this row is OK!! ,continue
        lastFirstOneColIdx = firstOneColIdxOfRow;
    }

    return true;
}

template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::elementary_line_transformation(const int& rowIdx){
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    const int& curRowIdx = rowIdx;

    int bingoColIdx=-1;
    const T* pFirstNonZeroVal=NULL;
    for( int colIdx=0;colIdx<_col;++colIdx){
        const T& Mij=  get(curRowIdx,colIdx);
        if( OutputAdapter::isZero( Mij)==false){
            bingoColIdx=colIdx;
            pFirstNonZeroVal=&Mij;
            break;
        }
    }

    if(bingoColIdx==-1){
        LOGD("cannot find non zero value in row[%d], elementary_line_transformation abort!",curRowIdx);
        return;
    }

    const T& firstNonZeroVal = *pFirstNonZeroVal;
    LOGD("found non zero value in row[%d]=> %s",curRowIdx,OutputAdapter::toString(firstNonZeroVal).c_str());

    if( OutputAdapter::isEqualOne(firstNonZeroVal)){
        //ok
    }else{
        T reciprocal = OutputAdapter::reciprocal(firstNonZeroVal);
        for( int colIdx=0;colIdx<_col;++colIdx){
            const int idx= curRowIdx*_col+colIdx;
            _items[idx]*=reciprocal;
        }
    }

    for(int otherRowIdx=0; otherRowIdx<_row;++otherRowIdx){
        if( otherRowIdx==curRowIdx){
            continue;
        }
        T nval = _items[otherRowIdx*_col+bingoColIdx];
        if( OutputAdapter::isZero(nval)){
            continue;
        }
        nval*=-1L;

        for( int colIdx=0;colIdx<_col;++colIdx){
            const int cidx= curRowIdx*_col+colIdx;
            const int nidx= otherRowIdx*_col+colIdx;
            _items[nidx]+= (_items[cidx]*nval);
        }
    }

    //LOGD("first value of row[%d] is:%s\n",curRowIdx, OutputAdapter::toString(firstNonZeroVal).c_str());
}

template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::elementary_line_transformation(){
    for(int r=0;r<_row;++r){
        elementary_line_transformation(r);
    }
}