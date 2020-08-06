//
// Created by Administrator on 2017/3/29.
//

#include "Matrix.h"
#include "../utils/FloatUtils.h"
#include "../utils/LogQueue.h"
#include <stdexcept>
#include <math.h>

Matrix::Matrix(const int &row, const int &col):_col(col),_row(row),_items(new float[row*col]) {
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


// * Fucking float array
Matrix::Matrix(const int& row,const int& col,const float items[]):_col(col),_row(row),_items(new float[col*row]){
    const int itemCount = _col*_row;
    for(int i=0;i<itemCount;++i){
        _items[i] = items[i];
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
    Matrix result(A._row,A._col);
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
    Matrix result(A.row(),A.col());
    const int itemCount = result.itemCount();
    for(int i=0;i<itemCount;++i){
        result._items[i] = FloatUtils::minus(A._items[i],B._items[i]);
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
    result.append("\n");
    for( int r=0;r<_row;r++){
        result.append("|");
        for(int c=0;c<_col;++c){
            if(c>0){
                result.append(",");
            }
            sprintf(buff,"%.8lf",get(r,c));
            result.append(buff);

        }
        result.append("|\n");
    }
    return result;
}

const char* Matrix::c_str() const {
    return toString().c_str();
}

const float* Matrix::value_ptr()const{
    return _items;
}

/*
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
*/

void  Matrix::zero(){

    const int c = itemCount();
    for(int i=0;i<c;++i){
        _items[i] = 0.0f;
    }
}

void Matrix::set(const int& idx,const float & val){
    if( idx<0||idx>=itemCount()){
        throw out_of_range("index is out of range!");
    }
    _items[ idx] = val;
}

void Matrix::set(const int& rowIdx,const int& colIdx,const float & val){
    if( colIdx<0||colIdx>=_col){
        throw out_of_range("col index is out of range!");
    }
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range("row index is out of range!");
    }
    set( rowIdx*_col + colIdx, val);
}

void  Matrix::set(const Matrix& clone){
    if( _col!=clone._col||_row!=clone._row){
        throw runtime_error("col or row is not equal!");
    }
    const int c = itemCount();
    for(int i=0;i<c;++i){
        _items[i] = clone._items[i];
    }
}

float Matrix::get(const int& idx)const{
    if( idx<0||idx>=itemCount()){
        throw out_of_range("index is out of range!");
    }
    return _items[idx];
}

float Matrix::get(const int& rowIdx,const int& colIdx)const{
    if( colIdx<0||colIdx>=_col){
        throw out_of_range("colIdx is out of range!");
    }
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range("rowIdx is out of range!");
    }
    return get( rowIdx*_col+colIdx);
}

Matrix  Matrix::multiply(const Matrix& A,const Matrix& B){
    if( A.col() != B.row() ){
        throw runtime_error(" col of A must equal row of B ");
    }

    const int k = A.col();
    Matrix result(A.row(),B.col());
    for( int rowIdx=0;rowIdx<result._row;++rowIdx){
        for( int colIdx=0;colIdx<result._col;++colIdx){
            float  val=0.0;
            for(int ik=0;ik<k;ik++){
                val += A.get(rowIdx,ik) * B.get(ik,colIdx);
            }
            result.set(rowIdx,colIdx,val);
        }
    }
    return result;
}

Matrix  Matrix::multiply(const Matrix& B)const{
    return multiply(*this,B);
}

Matrix Matrix::transpose(const Matrix& O){
    Matrix result(O.col(),O.row());
    for( int rowIdx=0;rowIdx<result._row;++rowIdx){
        for( int colIdx=0;colIdx<result._col;++colIdx){
            result.set( rowIdx,colIdx,O.get(colIdx,rowIdx));
        }
    }
    return result;
}

Matrix  Matrix::transpose()const{
    return transpose(*this);
}

Matrix Matrix::createIdentityMatrix(const int n){
    if( n<=0){
        throw out_of_range(" n<=0!");
    }
    Matrix result(n,n);
    for(int i=0;i<n;++i){
        result.set(i,i,1.0);
    }
    return result;
}

bool Matrix::isSingular()const{

    int zeroCountOfCol[_col];
    for( int colIdx=0;colIdx<_col;++colIdx){
        zeroCountOfCol[colIdx]=0;
    }

    for( int rowIdx=0;rowIdx<_row;++rowIdx){
        int zeroCountOfRow=0;
        for( int colIdx=0;colIdx<_col;++colIdx){
           if(FloatUtils::isEqual(_items[rowIdx*_row+colIdx],0.0f)){
               zeroCountOfRow++;
               zeroCountOfCol[colIdx]++;
           }
        }
        if( zeroCountOfRow == _col){
            return true;
        }
    }
    for( int colIdx=0;colIdx<_col;++colIdx){
        if(zeroCountOfCol[colIdx]==_row){
            return true;
        }
    }
    return false;
}

bool Matrix::isSquare() const {
    return _row==_col;
}

bool Matrix::isInvertible()const{
    return isSquare() && !FloatUtils::isEqual(determinant(), 0.0f);
}

// forward def
static float det(const Matrix& M);
static float Cij(const Matrix& M,const int& i,const int& j);

float Matrix::determinant()const{
    return det(*this);
}

Matrix Matrix::cofactors()const{
    if(!isSquare()){
        throw runtime_error("M must be a square Matrix!");
    }

    Matrix mT(transpose());
    const int row= mT.row();
    const int col= mT.col();
    Matrix result(row,col);
    for( int r=0;r<row;++r){
        for(int c=0;c<col;++c){
            result.set(r,c,Cij(mT,r,c));
        }
    }
    return result;
}

Matrix Matrix::invert()const{
    if(!isSquare()){
        throw runtime_error("M must be a square Matrix!");
    }
    const float det = determinant();
    if( FloatUtils::isEqual(det,0.0f)){
        throw runtime_error("DET ==0 ");
    }
    return scalarMultiply(cofactors(),1.0f/det);
}


void Matrix::elementary_line_transformation(const int& rowIdx){
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    const int& curRowIdx = rowIdx;

    int bingoColIdx=-1;
    float firstNonZeroVal=0.0;
    for( int colIdx=0;colIdx<_col;++colIdx){
        const float Mij=  get(curRowIdx,colIdx);
        if(FloatUtils::isEqual( Mij,0.0f)==false){
            bingoColIdx=colIdx;
            firstNonZeroVal=Mij;
            break;
        }
    }

    if(bingoColIdx==-1){
        LogQueue::push("cannot find non zero value in row[%d], elementary_line_transformation abort!",curRowIdx);
        return;
    }



    LogQueue::push("first value of row[%d] is:%f\n",curRowIdx,firstNonZeroVal);

}

bool Matrix::isZeroRow(const int& rowIdx)const{
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    for( int colIdx=0;colIdx<_col;++colIdx){
        const float Mij=  get(rowIdx,colIdx);
        if(FloatUtils::isEqual( Mij,0.0f)==false){
            return false;
        }
    }

    return true;
}

int Matrix::getFirstOneColIdx(const int& rowIdx)const{
    if( rowIdx<0||rowIdx>=_row){
        throw out_of_range(" rowIdx<0||rowIdx>=_row");
    }

    for( int colIdx=0;colIdx<_col;++colIdx){
        const float Mij=  get(rowIdx,colIdx);
        if(FloatUtils::isEqual( Mij,0.0f)){
            continue;//
        }else if(FloatUtils::isEqual( Mij,1.0f)){
            return colIdx;
        }else{
            return -1;
        }
    }

    return -99;
}

bool  Matrix::isMostSimplest(void)const{

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

        // check the elements that with same column in other rows, they must be zero all
        const int& col = firstOneColIdxOfRow;
        for(int r=0;r<_row;++r){
            if(r!=rowIdx){
                if(FloatUtils::isEqual(get(r,col),0.0f)==false){
                    return false;
                }
            }
        }

        // !! this row is OK!! ,continue
        lastFirstOneColIdx = firstOneColIdxOfRow;
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// static inner helper
/////////////////////////////////////////////////////////////////////////////////////////////////

static Matrix del(const Matrix& M, const int& rowIdxToRemove, const int& colIdxtoRemove){

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
    float  trimItems[rrow*rcol];
    int idx=0;
    for( int r=0;r<row;++r){
        for(int c=0;c<col;++c){
            if( r==rowIdxToRemove || c== colIdxtoRemove){
                continue;
            }
            trimItems[idx++] = M.get(r,c);
        }
    }
    return Matrix(rrow,rcol,trimItems);
}



static float Cij(const Matrix& M,const int& i,const int& j){
    return powf(-1.0f,i+j) * det( del(M,i,j));
}

static float det(const Matrix& M){
    if(!M.isSquare()){
        throw runtime_error("M must be a square Matrix!");
    }
    if( M.row()==1){
        return M.get(0,0);
    }
    const int k=1;
    const int n = M.row();
    float result=0.0;
    for( int i=0;i<n;i++){
        result += M.get(i,k) * Cij(M,i,k);
    }
    return result;
}
