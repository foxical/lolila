//
// Created by Administrator on 2018/1/31.
//

#ifndef __SIMPLESHADER_H__
#define __SIMPLESHADER_H__

#ifndef __SHADERPROGRAM_H__
#include "ShaderProgram.h"
#endif


class Matrix;

class SimpleShader{
public:
    SimpleShader();
    ~SimpleShader();
public:

    bool init();
    void use()const;

    void setProjectMatrix(const Matrix&)const;
    void setViewMatrix(const Matrix&)const;
    void setModelMatrix(const Matrix&)const;

protected:



private:

    void setMatrix(const GLchar* , const Matrix&)const;

private:
    ShaderProgram _shaderProgram;
};

#endif //__SIMPLESHADER_H__
