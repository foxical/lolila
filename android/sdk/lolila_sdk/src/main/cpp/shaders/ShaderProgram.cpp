//
// Created by Administrator on 2018/1/30.
//

#include <malloc.h>
#include "ShaderProgram.h"
#include "../base/utils/GLUtils.h"
#include "../base/utils/AndroidLog.h"

GLuint ShaderProgram::create(const char* vShaderStr, const char* fShaderStr){

    if(_programObject!=0){
        glDeleteProgram(_programObject);
        _programObject=0;
    }

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint programObject;
    GLint linked;

    // Load the vertex/fragment shaders
    vertexShader = GLUtils::LoadShader ( GL_VERTEX_SHADER, vShaderStr );
    fragmentShader = GLUtils::LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );

    // Create the program object
    programObject = glCreateProgram ( );

    if ( programObject == 0 ){
        LOGE( "glCreateProgram error");
        return 0;
    }

    glAttachShader ( programObject, vertexShader );
    glAttachShader ( programObject, fragmentShader );

    // Link the program
    glLinkProgram ( programObject );

    // Check the link status
    glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

    if ( !linked ){
        GLint infoLen = 0;
        glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
        if ( infoLen > 1 )
        {
            char *infoLog = (char *) malloc (sizeof ( char ) * infoLen );
            glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
            LOGE( "Error linking program:\n%s\n", infoLog );
            free ( infoLog );
        }
        glDeleteProgram ( programObject );
        return 0;
    }

    // Store the program object
    _programObject = programObject;
    return programObject;
}

void ShaderProgram::use()const{
    if(!isReady()){
        LOGE("_programObject is not ready! try to execute create function first.");
        return;
    }
    glUseProgram(_programObject);
}


