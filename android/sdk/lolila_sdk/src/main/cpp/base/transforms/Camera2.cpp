//
// Created by Administrator on 2017/11/6.
//

#include "Camera2.h"
#include "MVPTransform.h"
#include "Rotation.h"
#include "../math/Matrix.h"
#include "../utils/FloatUtils.h"
#include "../utils/AndroidLog.h"
#include "Translate.h"
#include "MultiTransform.h"
#include <math.h>
#include <stdexcept>
#include <glm/ext/matrix_transform.hpp>

static const float PI  = FloatUtils::PI;//3.14159265f

static const float s_def_speed = .5f;

static const float s_def_ra_step = 1.0f;

// 默认相机位置
static const float s_def_pos_x = 0.0f;
static const float s_def_pos_y = 0.0f;
static const float s_def_pos_z = 3.0f;
static const Vector s_def_pos(s_def_pos_x,s_def_pos_y,s_def_pos_z);

// 定义一个front向量，无论什么pos向量与这个相加，都保证lookAt(观察点)位于pos的前面，不会出现向后看的情形
static const float s_def_front_x=0.0f;
static const float s_def_front_y=0.0f;
static const float s_def_front_z=-1.0f;

//默认的世界坐标系的上向量
static const Vector s_up(0.0,1.0,0.0);
static const Vector s_right(1.0,0.0,0.0);
static const Vector s_direct(0.0,0.0,1.0);

static const float s_def_pitch=0.0f;
static const float s_def_yaw = -90.0f;

static const float s_def_rah = 0.0f;
static const float s_def_rav = 0.0f;

Camera2::Camera2():_pos(s_def_pos_x,s_def_pos_y,s_def_pos_z),
                 _front(s_def_front_x,s_def_front_y,s_def_front_z),
                 _up(s_up),
                 _sceneCenterPos(0,0,0),
                 _speed(s_def_speed){

}

Camera2::~Camera2(){

}



void Camera2::resetPos(){
    _pos = s_def_pos;
    _front=Vector(s_def_front_x,s_def_front_y,s_def_front_z);
    _up=s_up;
    _speed=s_def_speed;

}

void Camera2::moveUp() {
    _pos = Vector::add(_pos,Vector::scalarMultiply(_up.normalize(),_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera2::moveDown() {
    _pos = Vector::minus(_pos,Vector::scalarMultiply(_up.normalize(),_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera2::moveLeft(){
    Vector temp = Vector::cross(_front,_up).normalize();
    _pos = Vector::minus(_pos,Vector::scalarMultiply(temp,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera2::moveRight(){
    Vector temp = Vector::cross(_front,_up).normalize();
    _pos = Vector::add(_pos,Vector::scalarMultiply(temp,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera2::moveForward(){
    _pos = Vector::add(_pos,Vector::scalarMultiply(_front,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera2::moveBack(){
    _pos = Vector::minus(_pos,Vector::scalarMultiply(_front,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}


void Camera2::pitchDown(){
    pitch(-s_def_ra_step);
}

void Camera2::pitchUp(){
    pitch(s_def_ra_step);
}

void Camera2::pitch(float angle){
    /*
    const float curPitch = getFrontPitch();
    LOGD("before pitch:%f\n",curPitch);
    const float final_angle = curPitch + angle;
    if( final_angle<=-90.0f || final_angle >= 90.0f){
        LOGD("limit exceed!");
        return;
    }
    */

    // 先计算俯仰旋转轴，通过 front X UP 获得
    MultiTransform t;
    t.rotate(angle,pitchAxis());
    _front = MultiTransform::doTransform(t.getMat(),_front);

    LOGD("after pitch:%f\n",getFrontPitch());
}

float Camera2::getFrontPitch()const{
    float sina = _front.y();
    float arc_sina = asinf(sina);
    const float pa = /*fabsf*/( arc_sina* 180.0f / PI);
    return pa;
}

float Camera2::getFrontYaw()const{
    float cosa = _front.x();
    float arc_cosa = acosf(cosa);
    const float pa = ( arc_cosa* 180.0f / PI);
    return pa;
}

void Camera2::yawLeft(){
    yaw(s_def_ra_step);
}

void Camera2::yawRight() {
    yaw(-s_def_ra_step);
}

void Camera2::yaw(float angle) {
    /*
    const float curYaw = getFrontYaw();
    LOGD("before yaw:%f\n",curYaw);
    const float final_angle = curYaw + angle;
    if( final_angle<=0.0f || final_angle >= 180.0f){
        LOGD("limit exceed!");
        return;
    }
     */

    // 只能以up轴作为旋转轴
    MultiTransform t;
    t.rotate(angle,yawAxis());
    _front = MultiTransform::doTransform(t.getMat(),_front);

    LOGD("after yaw:%f\n",getFrontYaw());
}

glm::mat4 Camera2::buildLookAtMatrix()const{
    glm::vec3 vec_up(_up.x(),_up.y(),_up.z());
    glm::vec3 vec_front(_front.x(),_front.y(),_front.z());
    glm::vec3 vec_pos(_pos.x(),_pos.y(),_pos.z());

    return glm::lookAt(
            vec_pos,           // Camera is here
            vec_pos+vec_front, // and looks here : at the same position, plus "direction"
            vec_up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Camera2::setSceneCenterPos(const Vector* cv){
    if(cv!=NULL){
        _sceneCenterPos = *cv;
    }
}

void Camera2::lookAtSceneCenter(){

    if( _pos.isEqual(_sceneCenterPos)){
        return;
    }

    _front = Vector(
            _sceneCenterPos.x()-_pos.x(),
            _sceneCenterPos.y()-_pos.y(),
            _sceneCenterPos.z()-_pos.z()
    ).normalize();

}

float Camera2::getYaw(const Vector& scv)const{

    if(_pos.isEqual(scv)){
        return 0.0f;
    }

    float yaw=0.0f;

    // 四种特殊情况
    if( FloatUtils::isEqual(_pos.x(),scv.x()) ){
        if( _pos.z()>=scv.z()){
            yaw = -90.0f;
        }else if( _pos.z()<scv.z()){
            yaw = -270.0f;
        }

    }else if( FloatUtils::isEqual(_pos.z(),scv.z()) ){
        if( _pos.x()>=scv.x()){
            yaw = -180.0f;
        }else if( _pos.x()<scv.x()){
            yaw = 0.0f;
        }

    }else {

        // 讨论X-Z平面，把场景中心点的XZ坐标进行变换，以_POS作为原点
        const float ncx = scv.x() - _pos.x();
        const float ncz = scv.z() - _pos.z();
        // 计算夹角的绝对值
        const float ya = fabsf(atanf(ncx / ncz) * 180.0f / PI);


        if (_pos.z() > scv.z() && _pos.x() < scv.x()) { // SCV在pos的第一象限
            yaw = (-90.0f) + ya;
        } else if (_pos.z() > scv.z() && _pos.x() > scv.x()) { // SCV在pos的第2象限
            yaw = (-90.0f) - ya;
        } else if (_pos.z() < scv.z() && _pos.x() > scv.x()) { // SCV在pos的第3象限
            yaw = (-270.0f) + ya;
        } else if (_pos.z() < scv.z() && _pos.x() < scv.x()) { // SCV在pos的第4象限
            yaw = (-270.0f) - ya;
        }

    }

    return yaw;
}

float Camera2::getPitch(const Vector& scv)const{


#if 0    // stupid

    const Vector& scv = _sceneCenterPos;
    if(FloatUtils::isEqual(_pos.y(),scv.y()) && FloatUtils::isEqual(_pos.z(),scv.z())){
        return;
    }

    // 四种特殊情况
    if( FloatUtils::isEqual(_pos.y(),scv.y()) ){
        if( _pos.z()>scv.z()){
            _pitch = 0.0f;
        }else if( _pos.z()<scv.z()){
            _pitch = 180.0f;
        }else{
            throw runtime_error(" lookAtSceneCenterPitch isEqual(_pos.z(),scv.z()) ");
        }

    }else if( FloatUtils::isEqual(_pos.z(),scv.z()) ){
        if( _pos.y()>scv.y()){
            _pitch = 270.0f;
        }else if( _pos.y()<scv.y()){
            _pitch = 90.0f;
        }else{
            throw runtime_error(" lookAtSceneCenterPitch isEqual(_pos.y(),scv.y())");
        }

    }else {

        // 讨论YZ平面，把场景中心点的YZ坐标进行变换，以_POS作为原点
        const float ncy = scv.y() - _pos.y();
        const float ncz = scv.z() - _pos.z();
        // 计算夹角的绝对值
        const float pa = fabsf(atanf(ncy / ncz) * 180.0f / PI);

        if (_pos.z() < scv.z() && _pos.y() < scv.y()) { // SCV在pos的第一象限
            //LOGD("enter 1 s");
            _pitch = (180.0f) - pa;
        } else if (_pos.z() > scv.z() && _pos.y() < scv.y()) { // SCV在pos的第2象限
            _pitch = pa;
        } else if (_pos.z() > scv.z() && _pos.y() > scv.y()) { // SCV在pos的第3象限
            _pitch = (360.0f) - pa;
        } else if (_pos.z() < scv.z() && _pos.y() > scv.y()) { // SCV在pos的第4象限
            //LOGD("enter 4 s");
            _pitch = (180.0f) + pa;
        }
    }
#endif

    if(_pos.isEqual(scv)){
        return 0.0f;
    }

    // 以_POS作为原点，把场景中心点的坐标进行变换，
    const float ncx = scv.x() - _pos.x();
    const float ncy = scv.y() - _pos.y();
    const float ncz = scv.z() - _pos.z();

    const Vector P(ncx,ncy,ncz);
    const Vector Q(ncx,0.0,ncz);
    const float cosa = Vector::dot(P,Q)/(P.length()*Q.length()); // 内积公式
    const float arc = acosf(cosa);
    const float pa = fabsf( arc* 180.0f / PI);

    //LOGD("PL:%f,D.P:%f",P.length(),Vector::dot(P,Q));
    //LOGD("lookAtSceneCenterPitch P:%s,Q:%s,cosa:%f,arc:%f,pa:%f",P.c_str(),Q.c_str(),cosa,arc,pa);

    float pitch=0.0f;

    if(FloatUtils::isEqual(pa,0.0f)){
        pitch=0.0f;
    }else{
        if(_pos.y()>scv.y()){
            pitch = 360.0f-pa;
        }else{
            pitch = pa;
        }
    }
    return pitch;
}

void Camera2::rotateAroundSceneCenterLockY(float angle){
//    if(FloatUtils::isEqual(angle,0.0f)){
//        return;
//    }
//    if( _pos.isEqual(_sceneCenterPos)){
//        return;
//    }
//
//    const Vector axis(0,1,0);
//
//    const float ax = _sceneCenterPos.x();
//    const float ay = _sceneCenterPos.y();
//    const float az = _sceneCenterPos.z();
//    //LOGD("before rotate,px:%f,py:%f,pz:%f",_pos.x(),_pos.y(),_pos.z());
//    Vector before( _pos.x()-ax,_pos.y()-ay,_pos.z()-az);
//    Vector after = Rotation::doTransform(axis,angle,before);
//    _pos = Vector(after.x()+ax,after.y()+ay,after.z()+az);
//
//    _front = Rotation::doTransform(axis,angle,_front);
//    // Also re-calculate the Right and Up vector
//    _right = Vector::cross(_front,s_up).normalize();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//    _up = Vector::cross(_right, _front).normalize();
//    Vector vDTemp = Vector::add(_pos,_front);
//    _direct = Vector::minus(_pos,vDTemp).normalize();
}

glm::vec3 Camera2::pitchAxis()const{
    return  glm::cross(glm::vec3(_front.x(),_front.y(),_front.z()),glm::vec3(_up.x(),_up.y(),_up.z()));
}

glm::vec3 Camera2::yawAxis()const{
    return glm::vec3(_up.x(),_up.y(),_up.z());
}

void Camera2::rotateAroundSceneCenter(float angle,
                                     bool lockCameraR,
                                     bool lockCameraD,
                                     bool lockCameraU ){

    if(FloatUtils::isEqual(angle,0.0f)){
        return;
    }
    if( _pos.isEqual(_sceneCenterPos)){
        return;
    }

    glm::vec3 axis;
    if( lockCameraR){
        axis = pitchAxis();
    }else if(lockCameraU){
        axis = yawAxis();
    }else if(lockCameraD){
        return;
    }


    const float ax = _sceneCenterPos.x();
    const float ay = _sceneCenterPos.y();
    const float az = _sceneCenterPos.z();
    //LOGD("before rotate,px:%f,py:%f,pz:%f",_pos.x(),_pos.y(),_pos.z());
    Vector before( _pos.x()-ax,_pos.y()-ay,_pos.z()-az);
    MultiTransform t;
    t.rotate(angle,axis);
    Vector after = MultiTransform::doTransform(t.getMat(),before);
    _pos = Vector(after.x()+ax,after.y()+ay,after.z()+az);
    //LOGD("  vPos:%s",_pos.c_str());


    rotateFront(angle,lockCameraR,lockCameraD,lockCameraU);

}

void Camera2::rotateFront( float angle,
                          bool lockCameraR,
                          bool lockCameraD,
                          bool lockCameraU){

    if(lockCameraR){

        pitch(angle);

    }else if(lockCameraU){
        yaw(angle);

    }else if( lockCameraD){
        return; // not support yet!!
    }

}
