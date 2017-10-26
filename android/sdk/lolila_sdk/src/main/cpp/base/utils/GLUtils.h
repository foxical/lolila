//
// Created by Administrator on 2017/10/10.
//

#ifndef __GLUTILS_H_
#define __GLUTILS_H_

#include <GLES3/gl3.h>

class GLUtils{

public:

    static GLuint LoadShader ( GLenum type, const char *shaderSrc );



private:
    GLUtils();
    ~GLUtils();
};

#endif //__GLUTILS_H_
