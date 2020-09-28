//
// Created by Administrator on 2018/1/31.
//

#include "SimpleShader.h"
#include "../base/math/Matrix.h"
#include "../base/utils/AndroidLog.h"

SimpleShader::SimpleShader(){

}

SimpleShader::~SimpleShader(){

}

bool SimpleShader::init(){

    const char* vShaderStr =
            "#version 300 es                           \n"
            "layout(location = 0) in vec3 vPosition;   \n"    // 顶点属性， 通过布局限定符指定在0位置
            "layout(location = 1) in vec4 vColor;      \n"    // 颜色， 通过布局限定符指定在1位置

            "uniform mat4 projection;                  \n"    // 统一变量，名字叫做‘projection’，把客户代码的投影矩阵传递给着色器
            "uniform mat4 view;                        \n"
            "uniform mat4 model;                       \n"

            "out vec4 fColor;                          \n"  // 输出顶点颜色

            "void main()                               \n"
            "{                                         \n"
            "gl_Position =  projection * view * model * vec4(vPosition,1.0); \n"    // 对每个顶点执行透视变换
            "fColor = vColor;                          \n"  // 直接输出颜色
            "}                                         \n";

    const char* fShaderStr =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "in vec4 fColor;                              \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "fragColor = fColor;                          \n"
            "}                                            \n";

    return _shaderProgram.create(vShaderStr,fShaderStr)!=0;
}

void SimpleShader::use() const {
    _shaderProgram.use();
}

void SimpleShader::setProjectMatrix(const Matrix& M)const{
    setMatrix("projection",M);
}
void SimpleShader::setViewMatrix(const Matrix& M)const{
    setMatrix("view",M);
}
void SimpleShader::setModelMatrix(const Matrix& M)const{
    setMatrix("model",M);
}

void SimpleShader::setMatrix(const GLchar* name, const Matrix& M)const{
    int matLoc = -1;
    matLoc = glGetUniformLocation(_shaderProgram.getProgramObject(), name);
    glUniformMatrix4fv(matLoc, 1, GL_TRUE, M.value_ptr() );
}
