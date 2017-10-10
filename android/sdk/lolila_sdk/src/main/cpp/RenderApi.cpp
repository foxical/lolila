//
// Created by Administrator on 2017/10/10.
//

#include <jni.h>
#include <GLES3/gl3.h>
#include <malloc.h>
#include "base/utils/GLUtils.h"
#include "base/utils/AndroidLog.h"

static GLint   gl_programObject=-1;
static GLsizei gl_viewport_width=-1;
static GLsizei gl_viewport_height=-1;

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_init(
        JNIEnv *env,
        jobject /* this */) {

    LOGI("RenderApi_init begin");

    char vShaderStr[] =
            "#version 300 es                          \n"
                    "layout(location = 0) in vec4 vPosition;  \n"
                    "void main()                              \n"
                    "{                                        \n"
                    "   gl_Position = vPosition;              \n"
                    "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
                    "precision mediump float;                     \n"
                    "out vec4 fragColor;                          \n"
                    "void main()                                  \n"
                    "{                                            \n"
                    "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
                    "}                                            \n";

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
        return;
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
        return;
    }

    // Store the program object
    gl_programObject = programObject;

    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );

    LOGI("RenderApi_init end.");
    return;
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_resize(
        JNIEnv *env,
        jobject obj, jint width, jint height ) {
    LOGI("RenderApi_resize w:%i,h:%i",width,height);
    gl_viewport_width = width;
    gl_viewport_height = height;


}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_draw(
        JNIEnv *env,
        jobject /* this */) {
    //LOGI("RenderApi_draw begin");

    GLfloat vVertices[] = {  //0.0f,  0.5f, 0.0f,
            //-0.5f, -0.5f, 0.0f,
            //0.5f, -0.5f, 0.0f
            0.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            1.0f,1.0f,0.0f,
            1.0f,0.0f,0.0f
    };

    // Set the viewport
    glViewport ( 0, 0, gl_viewport_width,
            /*gl_viewport_height*/gl_viewport_width
    ); // 视口的尺寸传正方形直观一点，否则渲染时坐标会按视口比例进行变换，会变形

    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT );

    // Use the program object
    glUseProgram ( gl_programObject );

    // Load the vertex data
    glVertexAttribPointer (
            0, // 第0号数组，将第0号数组和客户缓冲区关联
            3, // 每个顶点坐标使用3个分量表示，XYZ
            GL_FLOAT,
            GL_FALSE,
            0, // 由于改数组仅仅是存放坐标，没有颜色，因此跨距是0
            vVertices // 客户缓冲区指针
    );
    glEnableVertexAttribArray ( 0 );

    glDrawArrays ( GL_TRIANGLE_FAN ,
                   0, // draw begin from index 0
                   4  // total 3 vertices
    );


    //LOGI("RenderApi_draw end");
}