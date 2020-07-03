//
// Created by Administrator on 2018/1/30.
//

#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__


#include <GLES3/gl3.h>

class ShaderProgram{
public:
    ShaderProgram():_programObject(0){}
    ~ShaderProgram(){
        if(_programObject!=0){
            glDeleteProgram(_programObject);
        }
    }
public:
    GLuint create(const char* vfs, const char* ffs);
    bool isReady()const{
        return _programObject>0;
    }
    GLuint getProgramObject()const{
        return _programObject;
    }
    void use()const;
private:
    GLuint _programObject;
};


#endif //__SHADERPROGRAM_H__
