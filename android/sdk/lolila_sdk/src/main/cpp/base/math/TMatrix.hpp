//
// Created by tam on 2020/7/3.
//
/**
 * 元素按行优先的顺序存放
 * 在使用glUniformMatrix4fv设置时，必须设置转置标志为真
 */

#ifndef __TMATRIX_HPP__
#define __TMATRIX_HPP__

#ifndef __TEMPLATEEXPORTDEF_H__
#include "../utils/TemplateExportDef.h"
#endif

#include <string>
using namespace std;

EXPORT
template <typename T,typename OutputAdapter>
class TMatrix{
public:
    TMatrix(const int& row,const int& col);
    TMatrix(const int& row,const int& col,const double[]);
    TMatrix(const TMatrix<T,OutputAdapter>&);
    TMatrix(const T[],const int& row,const int& col);
    ~TMatrix();
public:
    int col()const;
    int row()const;
    int itemCount()const;

public:

    const T& get(const int& rowIdx,const int& colIdx)const;
    const T& get(const int& idx)const;
    void zero();
    void set(const int& rowIdx,const int& colIdx,const T& val);
    void set(const int& idx,const T& val);
    void set(const TMatrix<T,OutputAdapter>&);

public:


    string toString()const;

    const char* c_str() const;

    /**
        * check if is zero row
        * @param rowIdx
        * @return
        */
    bool isZeroRow(const int& rowIdx)const;

    /**
     * get the col index of first '1' element of this row
     * @param rowIdx
     * @return
     * -1: '1' element is not found in this row, and this row contains none zero value
     * -99: the given row is a 'zero' row
     */
    int getFirstOneColIdx(const int& rowIdx)const;

    /**
     * check if is the most simplest
     * @return
     */
    bool isMostSimplest(void)const;

    /**
    * 对指定的行执行初等行变换
    * @param rowIdx
    */
    void elementary_line_transformation(const int& rowIdx, const int& j);

    void elementary_line_transformation();



    bool isSquare()const;
    bool isInvertible()const;

    double determinant()const;


    void swapRow(const int& from, const int& to);

    /**
     * find the row, which Mkj has the max value
     * @param fromRow
     * from row index
     * @param j
     * column index
     * @return
     * the 'k' row index
     */
    int findMkj(const int& fromRow,const int& j)const;

public:
    const T* value_ptr()const;

private:
    TMatrix();
private:
    const int _row;
    const int _col;
    T* _items;
};

#if !defined(USE_EXPORT_TEMPLATE)
#include "TMatrix.cpp"
#endif

#endif //__TMATRIX_HPP__
