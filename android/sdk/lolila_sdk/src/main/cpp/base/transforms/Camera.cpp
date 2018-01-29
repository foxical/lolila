//
// Created by Administrator on 2017/11/6.
//

#include "Camera.h"
#include "MVPTransform.h"
#include "../math/Matrix.h"
#include "../utils/FloatUtils.h"
#include <math.h>

static const float PI  = FloatUtils::PI;//3.14159265f

static const float s_def_speed = 0.1f;

// 默认相机位置
static const float s_def_pos_x = 0.0f;
static const float s_def_pos_y = 0.0f;
static const float s_def_pos_z = 3.0f;

// 定义一个front向量，无论什么pos向量与这个相加，都保证lookAt(观察点)位于pos的前面，不会出现向后看的情形
static const float s_def_front_x=0.0f;
static const float s_def_front_y=0.0f;
static const float s_def_front_z=-1.0f;

//默认的世界坐标系的上向量
static const Vector s_up(0.0,1.0,0.0);

static const float s_def_pitch=0.0f;
static const float s_def_yaw = -90.0f;

Camera::Camera():_pos(s_def_front_x,s_def_front_y,s_def_front_z),
                 _front(s_def_front_x,s_def_front_y,s_def_front_z),
                 _up(s_up),
                 _speed(s_def_speed),
                 _pitch(s_def_pitch),
                 _yaw(s_def_yaw){

}

Camera::~Camera(){

}



void Camera::resetPos(){
    _pos = Vector(s_def_front_x,s_def_front_y,s_def_front_z);
    _front=Vector(s_def_front_x,s_def_front_y,s_def_front_z);
    _up=s_up;
    _speed=s_def_speed;
    _pitch=s_def_pitch;
    _yaw = s_def_yaw;
    updateVectors();
}

void Camera::moveUp() {
    _pos = Vector::add(_pos,Vector::scalarMultiply(s_up.normalize(),_speed));
}

void Camera::moveDown() {
    _pos = Vector::minus(_pos,Vector::scalarMultiply(s_up.normalize(),_speed));
}

void Camera::moveLeft(){
    //cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    Vector temp = Vector::cross(_front,s_up).normalize();
    _pos = Vector::minus(_pos,Vector::scalarMultiply(temp,_speed));
}

void Camera::moveRight(){
    //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    Vector temp = Vector::cross(_front,s_up).normalize();
    _pos = Vector::add(_pos,Vector::scalarMultiply(temp,_speed));
}

void Camera::moveForward(){
    //cameraPos += cameraSpeed * cameraFront;
    _pos = Vector::add(_pos,Vector::scalarMultiply(_front,_speed));
}

void Camera::moveBack(){
    //cameraPos -= cameraSpeed * cameraFront;
    _pos = Vector::minus(_pos,Vector::scalarMultiply(_front,_speed));


}

void Camera::pitchDown(){

    if( (_pitch-1.0f)<-89.0f){
        return;
    }
    _pitch -= 1.0f;
    updateVectors();
}

void Camera::pitchUp(){
    if( (_pitch+1.0f)>89.0f){
        return;
    }
    _pitch += 1.0f;
    updateVectors();
}

void Camera::yawLeft(){
    _yaw -= 1.0f;
    if ( _yaw <= -360.0f) {
        _yaw += 360.0f;
    }
    updateVectors();
}

void Camera::yawRight() {

    _yaw += 1.0f;
    if ( _yaw >= 360.0f) {
        _yaw -= 360.0f;
    }
    updateVectors();

}



void Camera::updateVectors(){

    const float fx = cosf(FloatUtils::radians(_pitch)) * cosf(FloatUtils::radians(_yaw));
    const float fy = sinf(FloatUtils::radians(_pitch));
    const float fz = cosf(FloatUtils::radians(_pitch)) * sinf(FloatUtils::radians(_yaw));

    _front = Vector(fx,fy,fz).normalize();
    // Also re-calculate the Right and Up vector
    Vector Right = Vector::cross(_front, s_up).normalize();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _up  = Vector::cross(Right, _front).normalize();
}

void Camera::buildLookAtMatrix(Matrix& M)const{

    Vector vecLookAt = Vector::add(_pos,_front);
    MVPTransform::buildLookAtMatrix(
            _pos.x(),    _pos.y(),    _pos.z(),
            vecLookAt.x(), vecLookAt.y(), vecLookAt.z(),
            _up,
            M
    );
}