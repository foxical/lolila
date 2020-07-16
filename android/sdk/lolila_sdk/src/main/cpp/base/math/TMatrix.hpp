//
// Created by tam on 2020/7/3.
//

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
    ~TMatrix();
public:
    int col()const;
    int row()const;
    int itemCount()const;

public:

    T get(const int& rowIdx,const int& colIdx)const;
    T get(const int& idx)const;

public:
    string toString()const;
    const char* c_str() const;

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
