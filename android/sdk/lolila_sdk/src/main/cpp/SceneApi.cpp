//
// Created by Administrator on 2017/10/10.
//

#include <jni.h>
#include <GLES3/gl3.h>
#include <malloc.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "base/utils/GLUtils.h"
#include "base/utils/AndroidLog.h"
#include "base/math/Matrix.h"
#include "base/geometry/Vector.h"
#include "base/geometry/Projections.h"
#include "base/transforms/Rotation.h"
#include "base/transforms/Translate.h"
#include "base/transforms/MVPTransform.h"
#include "base/transforms/Camera.h"
#include "base/utils/FloatUtils.h"
#include "shaders/SimpleShader.h"
#include "shaders/SimpleVAO.h"
#include "shapes/SimpleLine.h"


#include "course/DrawingContext.h"
#include "course/AbstractCourse.h"
#include "course/CourseFactory.h"
#include "base/transforms/Camera2.h"

static GLsizei gl_viewport_width=-1;
static GLsizei gl_viewport_height=-1;


static Matrix projectMat(4,4);
static Matrix rotateMat1(4,4);
static Matrix rotateMat2(4,4);
static Matrix translateMat(4,4);
static Matrix viewMat(4,4);
static Camera2 camera;




static float degree=45.0f;
static int delay_fr=0;

static const float PI  = FloatUtils::PI;//3.14159265f

static float near = 1.0f;
static float far = 20.0f;
static float fov=60.0f;

static int projectType=0; // 0: 透视投影，1：正视投影

static Vector def_sc(0,0,0-near-4);

// for test only!!
//////////////////////////////////

static SimpleShader shader;
//static SimpleVAO vao;
//static SimpleLine lineVertex(1.0, 0.0, 0.0, 1.0);

static AbstractCourse* course=NULL;

static glm::mat4 mat4_projection;
static glm::mat4 mat4_view;

//////////////////////////////////


static void updateProjectMat(){

    if(course!=NULL){
        const Matrix* customPrjMat = course->getCustomProjection();
        if( customPrjMat!=NULL){
            projectMat.set(*customPrjMat);
            return;
        }
    }

    far = near + 20.0f;

    if( projectType==0) {
        MVPTransform::buildFrustumMatrix(gl_viewport_width, gl_viewport_height, near,far, fov, projectMat);
    }else{
        MVPTransform::buildOrthoMatrix(gl_viewport_width, gl_viewport_height, near, far, fov, projectMat);
    }

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    mat4_projection = glm::perspective(glm::radians(fov), (float) gl_viewport_width / (float)gl_viewport_height, 0.1f, 100.0f);
}



extern "C" void Java_com_foxical_lolila_sdk_SceneApi_init(
        JNIEnv *env,
        jobject,jint prjType, jint courseNo /* this */) {

    LOGI("RenderApi_init begin");


    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
    glEnable(GL_DEPTH_TEST);
    glLineWidth(8.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    projectType=prjType;
    fov=60.f;
    near=1.0f;

    shader.init();
    camera.resetPos();
    camera.setSceneCenterPos(&def_sc);

    course = CourseFactory::createCourse(courseNo);
    if(course!=NULL){
        course->load();
        if( course->getSceneCenterV()!=NULL) {
            camera.setSceneCenterPos(course->getSceneCenterV());
        }
    }

    camera.lookAtSceneCenter();
    //camera.buildLookAtMatrix(viewMat);

    LOGI("RenderApi_init end.");
    return;
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_resize(
        JNIEnv *env,
        jobject obj, jint width, jint height ) {
    LOGI("RenderApi_resize w:%i,h:%i, aspect:%f",width,height,(float)width/(float)height);
    gl_viewport_width = width;
    gl_viewport_height = height;
    updateProjectMat();
}





extern "C" void Java_com_foxical_lolila_sdk_SceneApi_draw(
        JNIEnv *env,
        jobject /* this */) {
    //LOGI("RenderApi_draw begin");

    // Set the viewport
    glViewport ( 0, 0, gl_viewport_width, gl_viewport_height  );


    // Clear the color buffer
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    shader.use();
    shader.setProjectMatrix(mat4_projection);
    shader.setViewMatrix( camera.buildLookAtMatrix() );

    DrawingContext dc(shader);
    if(course!=NULL) {
        course->onDrawStep(dc);
    }

    //LOGI("RenderApi_draw end");
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// 摄像机操作
//////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraMoveForward(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveForward();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraMoveBack(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveBack();
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraMoveLeft(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveLeft();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraMoveRight(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveRight();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraMoveUp(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveUp();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraMoveDown(
        JNIEnv *env,
        jobject /* this */) {
    camera.moveDown();

}
extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraPitchUp(
        JNIEnv *env,
        jobject /* this */) {
    camera.pitchUp();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraPitchDown(
        JNIEnv *env,
        jobject /* this */) {
    camera.pitchDown();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraYawLeft(
        JNIEnv *env,
        jobject /* this */) {
    camera.yawLeft();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraYawRight(
        JNIEnv *env,
        jobject /* this */) {
    camera.yawRight();

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraRotateLeft(
        JNIEnv *env,
        jobject /* this */) {
    LOGD("cameraRotateLeft");
    camera.rotateAroundSceneCenter(-1.0,false,false,true);
    //camera.rotateAroundSceneCenterLockY(-1.0);

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraRotateRight(
        JNIEnv *env,
        jobject /* this */) {
    LOGD("cameraRotateRight");
    camera.rotateAroundSceneCenter(1.0,false,false,true);
    //camera.rotateAroundSceneCenterLockY(1.0);

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraRotateUp(
        JNIEnv *env,
        jobject /* this */) {
    //LOGD("cameraRotateUp");
    camera.rotateAroundSceneCenter(-1.0,true,false,false);

}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraRotateDown(
        JNIEnv *env,
        jobject /* this */) {
    //LOGD("cameraRotateDown");
    camera.rotateAroundSceneCenter(1.0,true,false,false);

}

//////////////////////////////////////////////////////////////////////////////////////////////////
// 投影操作
//////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_zoomIn(
        JNIEnv *env,
        jobject /* this */) {
    fov+=1.0f;
    if( fov>60.0f){
        fov=60.0f;
    }
    updateProjectMat();
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_zoomOut(
        JNIEnv *env,
        jobject /* this */) {
    fov-=1.0f;
    if( fov<1.0f){
        fov=1.0f;
    }
    updateProjectMat();
}


extern "C" void Java_com_foxical_lolila_sdk_SceneApi_useFrustumPrj(
        JNIEnv *env,
        jobject /* this */) {
    projectType=0;
    near = 1.0f;
    updateProjectMat();
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_useOrthoPrj(
        JNIEnv *env,
        jobject /* this */) {
    projectType=1;
    near=5.0f;
    updateProjectMat();
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_pushNearPlane(
        JNIEnv *env,
        jobject /* this */) {
    near+=1.0f;
    updateProjectMat();
}



//////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_nextStep(
        JNIEnv *env,
        jobject /* this */) {
    if(course!=NULL){
        course->nextStep();
    }
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_prevStep(
        JNIEnv *env,
        jobject /* this */) {
    if(course!=NULL){
        course->prevStep();
    }
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_resetStep(
        JNIEnv *env,
        jobject /* this */) {

    camera.resetPos();
    camera.setSceneCenterPos(&def_sc);
    if(course!=NULL) {
        course->reset();
        if (course->getSceneCenterV() != NULL) {
            camera.setSceneCenterPos(course->getSceneCenterV());
        }
    }
    camera.lookAtSceneCenter();


}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_term(
        JNIEnv *env,
        jobject /* this */) {
    if(course!=NULL){
        delete course;
    }
}

extern "C" void Java_com_foxical_lolila_sdk_SceneApi_cameraLookAtSceneCenter(
        JNIEnv *env,
        jobject /* this */) {
    camera.lookAtSceneCenter();

}

//////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getCameraYawAngle(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getYaw(Vector(0,0,0));
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getCameraPitchAngle(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getPitch(Vector(0,0,0));
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getCameraPosX(
        JNIEnv *env,
        jobject /* this */) {

    return camera.getCameraPos().x();
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getCameraPosY(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getCameraPos().y();
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getCameraPosZ(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getCameraPos().z();
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getScenePosX(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getSceneCenterPos().x();
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getScenePosY(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getSceneCenterPos().y();
}

extern "C" jfloat Java_com_foxical_lolila_sdk_SceneApi_getScenePosZ(
        JNIEnv *env,
        jobject /* this */) {
    return camera.getSceneCenterPos().z();
}
