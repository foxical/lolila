//
// Created by Administrator on 2018/1/31.
//

#ifndef __SIMPLESHADER_H__
#define __SIMPLESHADER_H__

#ifndef __SHADERPROGRAM_H__
#include "ShaderProgram.h"
#endif

#include <glm/glm.hpp>

class Matrix;


class SimpleShader{
public:
    SimpleShader();
    ~SimpleShader();
public:

    bool init();
    void use()const;

    /**
     * @deprecated
     */
    void setProjectMatrix(const Matrix&)const;
    /**
    * @deprecated
    */
    void setViewMatrix(const Matrix&)const;
    /**
    * @deprecated
    */
    void setModelMatrix(const Matrix&)const;


    void setProjectMatrix(const glm::mat4&)const;
    void setViewMatrix(const glm::mat4&)const;
    void setModelMatrix(const glm::mat4&)const;


private:
    /**
   * @deprecated
   */
    void setMatrix(const GLchar* , const Matrix&)const;

    void setMatrix(const GLchar*, const glm::mat4&)const;

private:
    ShaderProgram _shaderProgram;
};

#endif //__SIMPLESHADER_H__
