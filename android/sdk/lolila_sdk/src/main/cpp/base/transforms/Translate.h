//
// Created by Administrator on 2017/10/20.
//

#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

class Vector;
class Matrix;

class Translate {
public:
    static void buildTranslateMatrix(const Vector& T, Matrix& M);
private:
    Translate();
    ~Translate();
};


#endif //__TRANSLATE_H__
