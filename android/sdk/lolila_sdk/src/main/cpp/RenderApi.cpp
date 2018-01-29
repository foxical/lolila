//
// Created by Administrator on 2017/10/10.
//

#include <jni.h>
#include <GLES3/gl3.h>
#include <malloc.h>
#include <math.h>
#include "base/utils/GLUtils.h"
#include "base/utils/AndroidLog.h"
#include "base/math/Matrix.h"
#include "base/geometry/Vector.h"
#include "base/geometry/Projections.h"
#include "base/transforms/Rotation.h"
#include "base/transforms/Translate.h"
#include "base/transforms/MVPTransform.h"
#include "base/transforms/Camera.h"
#include "base/utils/esUtil.h"
#include "base/utils/FloatUtils.h"
#include "base/utils/VBOHelper.h"


static GLint   gl_programObject=-1;
static GLsizei gl_viewport_width=-1;
static GLsizei gl_viewport_height=-1;


static Matrix projectMat(4,4);
static Matrix rotateMat1(4,4);
static Matrix rotateMat2(4,4);
static Matrix translateMat(4,4);
static Matrix viewMat(4,4);
static Camera camera;
static VBOHelper vboHelper(GL_ARRAY_BUFFER);

// Vertex daata
static GLfloat  *vertices;
static GLuint   *indices;
static int       numIndices;
static ESMatrix mvp;
static ESMatrix pm;
static ESMatrix tm;
static ESMatrix rm;


int esGenCube ( float scale, GLfloat **vertices, GLfloat **normals,
                           GLfloat **texCoords, GLuint **indices )
{
    int i;
    int numVertices = 24;
    int numIndices = 36;

    GLfloat cubeVerts[] =
            {
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f,  0.5f,
                    0.5f, -0.5f,  0.5f,
                    0.5f, -0.5f, -0.5f,
                    -0.5f,  0.5f, -0.5f,
                    -0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f,  0.5f, -0.5f,
                    0.5f,  0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, 0.5f,
                    -0.5f,  0.5f, 0.5f,
                    0.5f,  0.5f, 0.5f,
                    0.5f, -0.5f, 0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f, -0.5f,
            };

    GLfloat cubeNormals[] =
            {
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
            };

    GLfloat cubeTex[] =
            {
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    1.0f, 0.0f,
            };

    // Allocate memory for buffers
    if ( vertices != NULL )
    {
        *vertices = (GLfloat *) malloc (sizeof ( GLfloat ) * 3 * numVertices );
        memcpy ( *vertices, cubeVerts, sizeof ( cubeVerts ) );

        for ( i = 0; i < numVertices * 3; i++ )
        {
            ( *vertices ) [i] *= scale;
        }
    }

    if ( normals != NULL )
    {
        *normals = (GLfloat *) malloc (sizeof ( GLfloat ) * 3 * numVertices );
        memcpy ( *normals, cubeNormals, sizeof ( cubeNormals ) );
    }

    if ( texCoords != NULL )
    {
        *texCoords = (GLfloat *) malloc (sizeof ( GLfloat ) * 2 * numVertices );
        memcpy ( *texCoords, cubeTex, sizeof ( cubeTex ) ) ;
    }


    // Generate the indices
    if ( indices != NULL )
    {
        GLuint cubeIndices[] =
                {
                        0, 2, 1,
                        0, 3, 2,
                        4, 5, 6,
                        4, 6, 7,
                        8, 9, 10,
                        8, 10, 11,
                        12, 15, 14,
                        12, 14, 13,
                        16, 17, 18,
                        16, 18, 19,
                        20, 23, 22,
                        20, 22, 21
                };

        *indices = (GLuint *) malloc (sizeof ( GLuint ) * numIndices );
        memcpy ( *indices, cubeIndices, sizeof ( cubeIndices ) );
    }

    return numIndices;
}

static float degree=45.0f;
static int delay_fr=0;

static const float PI  = FloatUtils::PI;//3.14159265f

static float near = 1.0f;
static float far = 20.0f;
static float fov=60.0f;

static int projectType=0; // 0: 透视投影，1：正视投影

static void updateProjectMat(){


    far = near + 20.0f;

    if( projectType==0) {
        MVPTransform::buildFrustumMatrix(gl_viewport_width, gl_viewport_height, near,far, fov, projectMat);
    }else{
        MVPTransform::buildOrthoMatrix(gl_viewport_width, gl_viewport_height, near, far, fov, projectMat);
    }
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_init(
        JNIEnv *env,
        jobject /* this */) {

    LOGI("RenderApi_init begin");

/**
 *  gl_Position is a built-in vertex shader output variable, whose type is defined by the OpenGL specification to be a vec4.
    position is a vertex shader attribute, and since the introduction of programmable shaders, you (as the developer) are in full control of its format.
    Most likely, you have per-vertex 3D coordinates (hence, just 3 floats per vertex),
    that you configured as the vertex shader input via a call to glVertexAttribPointer (or similar),
    telling OpenGL to pull 3 floats at a time from a buffer for the position attribute.
    Since gl_Position wants 4 floats, the expansion to vec4 (by filling in the w to 1.0) becomes necessary in the vertex shader.
 */


    char vShaderStr[] =
            "#version 300 es                          \n"
                    "layout(location = 0) in vec3 vPosition;  \n"    // 顶点属性， 通过布局限定符指定在0位置

                    "uniform mat4 projection;                  \n"    // 统一变量，名字叫做‘projection’，把客户代码的投影矩阵传递给着色器
                    "uniform mat4 rotation1;                   \n"
                    "uniform mat4 rotation2;                   \n"
                    "uniform mat4 translate;                   \n"
                    "uniform mat4 view;                        \n"
                    "void main()                               \n"
                    "{                                         \n"
                    "   gl_Position =  projection * view * translate * rotation2 * rotation1 * vec4(vPosition,1.0); \n"    // 对每个顶点执行透视变换
                    "}                                         \n";

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


    Rotation::buildRotationMatrix(Vector(1.0f,.0f,.0f),45.0f,rotateMat1);
    Translate::buildTranslateMatrix(Vector(.0f,.0f,-10.0f),translateMat);


    numIndices = esGenCube ( 1.0, &vertices,
                                       NULL, NULL, &indices );


    glEnable(GL_DEPTH_TEST);


    camera.resetPos();
    projectType=0;
    fov=60.f;
    near=1.0f;


    const float w = 1.0f;
    const float z = -1.0f;


    GLfloat vVertices[] = {  //0.0f,  0.5f, 0.0f,

            // face 0
            0.0f,0.0f, 0.0,
            0.0f,w,    0.0,
            w,   w,    0.0,
            w,   0.0f, 0.0,

            // face 1
            0.0, w, 0.0,
            0.0, w,  z,
            w,w,z,
            w,w,0.0,
    };

    LOGD("vVertices size:%d", sizeof(vVertices));
    vboHelper.bindData(sizeof(vVertices),vVertices,GL_STATIC_DRAW);

    LOGI("RenderApi_init end.");
    return;
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_resize(
        JNIEnv *env,
        jobject obj, jint width, jint height ) {
    LOGI("RenderApi_resize w:%i,h:%i, aspect:%f",width,height,(float)width/(float)height);
    gl_viewport_width = width;
    gl_viewport_height = height;
    updateProjectMat();
}





extern "C" void Java_com_foxical_lolila_sdk_RenderApi_draw(
        JNIEnv *env,
        jobject /* this */) {
    //LOGI("RenderApi_draw begin");


    // Set the viewport
    glViewport ( 0, 0, gl_viewport_width, gl_viewport_height  );


    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Use the program object
    glUseProgram ( gl_programObject );



    ///*  以下代码片段演示了物体绕Y轴旋转
    {
        degree += 1.0f;
        if (degree >= 360.0f) {
            degree -= 360.0f;
        }
        delay_fr=0;
    }
    const Vector vUp(0,1,0);
    Rotation::buildRotationMatrix(vUp, degree,rotateMat2);

    camera.buildLookAtMatrix(viewMat);

    int matLoc = -1;

    matLoc = glGetUniformLocation(gl_programObject, "projection");
    glUniformMatrix4fv(matLoc, 1, GL_TRUE, projectMat.value_ptr() );
    matLoc = glGetUniformLocation(gl_programObject, "rotation1");
    glUniformMatrix4fv(matLoc, 1, GL_TRUE, rotateMat1.value_ptr());
    matLoc = glGetUniformLocation(gl_programObject, "rotation2");
    glUniformMatrix4fv(matLoc, 1, GL_TRUE, rotateMat2.value_ptr());
    matLoc = glGetUniformLocation(gl_programObject, "translate");
    glUniformMatrix4fv(matLoc, 1, GL_TRUE, translateMat.value_ptr());
    matLoc = glGetUniformLocation(gl_programObject, "view");
    glUniformMatrix4fv(matLoc, 1, GL_TRUE, viewMat.value_ptr());





    // Load the vertex data
    VBOHelper::VertexAttribPointer vertexAttribPointer(&vboHelper,
                                                           0, // 第0号顶点属性和客户缓冲区关联， 第0号位置通过着色器语言指定
                                                           3, // 每个顶点坐标使用3个分量表示，XYZ
                                                           GL_FLOAT,
                                                           GL_FALSE,
                                                           3 * sizeof(GLfloat));



    for(int i=0;i<2;++i) {

        glDrawArrays(GL_TRIANGLE_FAN,
                     i*4, // draw begin from index per face
                     4  // total 4 vertices per face
        );
    }


    //LOGI("RenderApi_draw end");
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraMoveForward(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveForward();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraMoveBack(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveBack();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraMoveLeft(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveLeft();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraMoveRight(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveRight();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraMoveUp(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveUp();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraMoveDown(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveDown();
}
extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraPitchUp(
        JNIEnv *env,
        jobject /* this */) {
    camera.pitchUp();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraPitchDown(
        JNIEnv *env,
        jobject /* this */) {
    camera.pitchDown();
}
extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraYawLeft(
        JNIEnv *env,
        jobject /* this */) {
    camera.yawLeft();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_cameraYawRight(
        JNIEnv *env,
        jobject /* this */) {
    camera.yawRight();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_zoomIn(
        JNIEnv *env,
        jobject /* this */) {
    fov+=1.0f;
    if( fov>60.0f){
        fov=60.0f;
    }
    updateProjectMat();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_zoomOut(
        JNIEnv *env,
        jobject /* this */) {
    fov-=1.0f;
    if( fov<1.0f){
        fov=1.0f;
    }
    updateProjectMat();
}


extern "C" void Java_com_foxical_lolila_sdk_RenderApi_useFrustumPrj(
        JNIEnv *env,
        jobject /* this */) {
    projectType=0;
    updateProjectMat();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_useOrthoPrj(
        JNIEnv *env,
        jobject /* this */) {
    projectType=1;
    near=5.0f;
    updateProjectMat();
}

extern "C" void Java_com_foxical_lolila_sdk_RenderApi_pushNearPlane(
        JNIEnv *env,
        jobject /* this */) {
    near+=1.0f;
    updateProjectMat();
}