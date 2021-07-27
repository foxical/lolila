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


// forward def
template <typename T,typename OutputAdapter>
static double det(const TMatrix<T,OutputAdapter>& M);
template <typename T,typename OutputAdapter>
static double Cij(const TMatrix<T,OutputAdapter>& M,const int& i,const int& j);


template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const int& row,const int& col):_col(col),_row(row),_items(new T[row*col]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = 0.0f; // T must override '=' operator, and default constructor
    }
}

////*
template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const int& row,const int& col,const double items[]):_col(col),_row(row),_items(new T[row*col]){
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = items[i];
    }
}
///*/

template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const TMatrix<T,OutputAdapter> & o):_col(o._col),_row(o._row),_items(new T[o._col*o._row]) {
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = o._items[i];
    }
}


template <typename T,typename OutputAdapter>
TMatrix<T,OutputAdapter>::TMatrix(const T items[],const int& row,const int& col):_col(col),_row(row),_items(new T[row*col]){
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = items[i];
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
void  TMatrix<T,OutputAdapter>::zero(){

    const int c = itemCount();
    for(int i=0;i<c;++i){
        _items[i] = 0.0f;
    }
}

template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::set(const int& idx,const T & val){
    if( idx<0||idx>=itemCount()){
        throw out_of_range("index is out of range!");
    }
    _items[ idx] = val;
}

template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::set(const int& rowIdx,const int& colIdx,const T & val){
    if( colIdx<0||colIdx>=_col){
        throw out_of_range("col index is out of range!");
    }
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range("row index is out of range!");
    }
    set( rowIdx*_col + colIdx, val);
}

template <typename T,typename OutputAdapter>
void  TMatrix<T,OutputAdapter>::set(const TMatrix<T,OutputAdapter>& clone){
    if( _col!=clone._col||_row!=clone._row){
        throw runtime_error("col or row is not equal!");
    }
    const int c = itemCount();
    for(int i=0;i<c;++i){
        _items[i] = clone._items[i];
    }
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

/**
 * 判断指定的行是否试全零行
 * @tparam T
 * @tparam OutputAdapter
 * @param rowIdx
 * 指定的行索引
 * @return
 */
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

/***
 * 找出指定行中，第一个‘1’元素的列索引
 * @tparam T
 * @tparam OutputAdapter
 * @param rowIdx
 * @return
 * 返回值大于=0 表示，找到第一个1元素，返回值就是1元素所在的列索引
 * 返回值-1表示这一行的第一个非零元素不是1元素
 * 返回值-99表示这一行全部都是0元素
 */
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

/**
 * 判断是否符合最简矩阵的要求
 * @tparam T
 * @tparam OutputAdapter
 * @return
 */
template <typename T,typename OutputAdapter>
bool TMatrix<T,OutputAdapter>::isMostSimplest(void)const{
    // 记录上一个全零行的行索引
    int lastZeroRowIdx=-1;
    // 记录上一个1元素的列索引
    int lastFirstOneColIdx=-1;

    for(int rowIdx=0;rowIdx<_row;++rowIdx){

        // 查找这一行的第一个1元素
        int firstOneColIdxOfRow = getFirstOneColIdx(rowIdx);
        if( firstOneColIdxOfRow==-1 ){ // 第一个元素不是1， 直接判定为失败
            return false; // can not find the ‘first one’ element
        }else if( firstOneColIdxOfRow==-99){ // 这一行全部都是0， 记录下行索引号，继续循环
            lastZeroRowIdx = rowIdx; // this row is zero row, save the row idx in 'lastZeroRowIdx'
            continue;
        }

        // 能够到达这里，表示已经发现了第一个1元素，并且这一行不是全0行

        // 如果这一行发现的第一个1元素的列索引没有超过上一行发现的，判定为失败
        if(firstOneColIdxOfRow<=lastFirstOneColIdx){
            return false; // the col idx is less then the last first one element's col idx
        }

        // 这一行不是全0行，但此前发现了全零行，不符合要求，判定为失败
        if(lastZeroRowIdx!=-1){
            return false; // the zero row is above of this row
        }

        // 检查第一个1元素所在列的其他行的元素，必须全部是0，否则判定为失败
        // check the elements that with same column in other rows, they must be all zero
        const int& col = firstOneColIdxOfRow;
        for(int r=0;r<_row;++r){
            if(r!=rowIdx){
                if(OutputAdapter::isZero(get(r,col))==false){
                    return false;
                }
            }
        }

        // 这一行检查OK，记录下第一个1元素的列索引，
        // !! this row is OK!! ,continue
        lastFirstOneColIdx = firstOneColIdxOfRow;
    }

    return true;
}

/**
 * 对这一行执行初等行变换
 * @tparam T
 * @tparam OutputAdapter
 * @param rowIdx
 * 指定的行索引
 * @param j
 * 第J列
 */
template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::elementary_line_transformation(const int& rowIdx,const int& j){
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    //findMkj找出的那个数值，即这一行第J列的数值
    const T& Mkj = get(rowIdx,j);
    //LOGD("i:%i,j:%i,Mkj found! :%s",rowIdx,j,OutputAdapter::toString(Mkj).c_str());

    // 求出MKJ的倒数
    T reciprocal = OutputAdapter::reciprocal(Mkj);
    //LOGD("reciprocal(Mkj)=>%s",OutputAdapter::toString(reciprocal).c_str());

    // 这一行的全部元素乘以倒数，结果使（rowIdx,j）的元素为1
    for( int colIdx=0;colIdx<_col;++colIdx){
        const int idx= rowIdx*_col+colIdx;
        _items[idx]*=reciprocal;
        //LOGD("cur row:%i, col:%i, trans to=>%s",rowIdx,colIdx,OutputAdapter::toString(_items[idx]).c_str());
    }

    // 对于除了这行以外的所有行，执行以下操作
    for(int otherRowIdx=0; otherRowIdx<_row;++otherRowIdx){
        if( otherRowIdx==rowIdx){
            continue;
        }

        // 如果其他行第J列是0，跳过，继续循环
        T nval = _items[otherRowIdx*_col+j];
        if( OutputAdapter::isZero(nval)){
            continue;
        }

        // 把这个数变为负数
        nval*=-1L;
        //LOGD("nval:%s",OutputAdapter::toString(nval).c_str());
        for( int colIdx=0;colIdx<_col;++colIdx){
            const int cidx= rowIdx*_col+colIdx;
            const int nidx= otherRowIdx*_col+colIdx;
            //LOGD("other row:%i, col:%i, before=>%s",otherRowIdx,colIdx,OutputAdapter::toString(_items[nidx]).c_str());
            //LOGD("cur row:%i, col:%i, =>%s",rowIdx,colIdx,OutputAdapter::toString(_items[cidx]).c_str());
            T temp;
            temp = _items[cidx]*nval; // 目标行所有元素乘以NVAL
            //LOGD("temp:%s",OutputAdapter::toString(temp).c_str());
            _items[nidx]+= temp;     // 再加到其他行上
            //LOGD("other row:%i, col:%i, trans to=>%s",otherRowIdx,colIdx,OutputAdapter::toString(_items[nidx]).c_str());
        }
    }

    //LOGD("first value of row[%d] is:%s\n",curRowIdx, OutputAdapter::toString(firstNonZeroVal).c_str());
}





template <typename T,typename OutputAdapter>
bool TMatrix<T,OutputAdapter>::isSquare() const {
    return _row==_col;
}

template <typename T,typename OutputAdapter>
double TMatrix<T,OutputAdapter>::determinant()const{
    return det(*this);
}

/**
 * 交换两行
 * @tparam T
 * @tparam OutputAdapter
 * @param from
 * @param to
 */
template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::swapRow(const int& from, const int& to){
    if( from<0||from>=_row){
        throw out_of_range(" from<0||from>=_row");
    }
    if( to<0||to>=_row){
        throw out_of_range(" to<0||to>=_row");
    }

    for( int colIdx=0;colIdx<_col;++colIdx){
        const int f_idx= from*_col+colIdx;
        const int t_idx= to*_col+colIdx;
        const T  bak =  _items[f_idx];
        _items[f_idx] = _items[t_idx];
        _items[t_idx] = bak;
    }
}

/**
 * 在指定的行索引开始，找出第J列元素数值（绝对值）最大的元素（不等于0）
 * @tparam T
 * @tparam OutputAdapter
 * @param fromRow
 * 从这行开始查找
 * @param j
 * 指定的列索引
 * @return
 * 查找失败：返回-1,表示从fromRow开始以下的所有行，第J列元素都是0
 */
template <typename T,typename OutputAdapter>
int TMatrix<T,OutputAdapter>::findMkj(const int& fromRow,const int& j)const{
    if( fromRow<0||fromRow>=_row){
        throw out_of_range(" fromRow<0||fromRow>=_row");
    }
    if( j<0||j>=_col){
        throw out_of_range(" j<0||j>=_col");
    }

    T Mkj;
    Mkj=0.0f;
    int k=-1;
    for( int r=fromRow;r<_row;++r){
        T  bak =  OutputAdapter::abs(_items[r*_col+j]);
        if( bak>Mkj){ // 找到就记录下行号
            Mkj=bak;
            k=r;
        }
    }

    return k;
}

/**
 * 对整个矩阵执行初等行变换
 * @tparam T
 * @tparam OutputAdapter
 */
template <typename T,typename OutputAdapter>
void TMatrix<T,OutputAdapter>::elementary_line_transformation(){

    int j=0;

    for(int i=0;i<_row;++i){
        int k = -1;
        while(true) {
            k=findMkj(i, j);
            if(k>=i){
                break;
            }
            j++;
            if(j>=_col){
                return;
            }
        }

        if(k>i){
            swapRow(k,i);
        }


        elementary_line_transformation(i,j);

        j++;
        if(j>=_col){
            return;
        }
    }

}

template <typename T,typename OutputAdapter>
const T* TMatrix<T,OutputAdapter>::value_ptr()const{
    return _items;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static inner helper
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * remove the given row and col , return a 'trim' matrix
 * @tparam T
 * @tparam OutputAdapter
 * @param M
 * @param rowIdxToRemove
 * @param colIdxtoRemove
 * @return
 */
template <typename T,typename OutputAdapter>
static TMatrix<T,OutputAdapter> del(const TMatrix<T,OutputAdapter>& M, const int& rowIdxToRemove, const int& colIdxtoRemove){

    const int row = M.row();
    const int col = M.col();
    if( colIdxtoRemove<0||colIdxtoRemove>=col){
        throw out_of_range("colIdxtoRemove is out of range!");
    }
    if( rowIdxToRemove<0||rowIdxToRemove>=row){
        throw out_of_range("rowIdxToRemove is out of range!");
    }

    const int rrow=row-1;
    const int rcol=col-1;
    T  trimItems[rrow*rcol];
    int idx=0;
    for( int r=0;r<row;++r){
        for(int c=0;c<col;++c){
            if( r==rowIdxToRemove || c== colIdxtoRemove){
                continue;
            }
            trimItems[idx++] = M.get(r,c);
        }
    }
    return TMatrix<T,OutputAdapter>(trimItems,rrow,rcol);
}

template <typename T,typename OutputAdapter>
static double Cij(const TMatrix<T,OutputAdapter>& M,const int& i,const int& j){
    return powf(-1.0f,i+j) * det( del(M,i,j));
}

template <typename T,typename OutputAdapter>
static double det(const TMatrix<T,OutputAdapter>& M){
    if(!M.isSquare()){
        throw runtime_error("M must be a square Matrix!");
    }
    if( M.row()==1){
        return M.get(0,0);
    }
    const int k=1; /* k is a const value, range from [1,n]*/
    const int n = M.row();
    double result=0.0;
    for( int i=0;i<n;i++){
        result +=   ((double)M.get(i,k)) * Cij(M,i,k);
    }
    return result;
}
