//
// Created by Administrator on 2017/11/6.
//

#include "Camera.h"

static const float s_def_speed = 0.5f;

// 默认相机位置
static const float s_def_pos_x = 0.0f;
static const float s_def_pos_y = 0.0f;
static const float s_def_pos_z = 3.0f;

// 定义一个front向量，无论什么pos向量与这个相加，都保证lookAt(观察点)位于pos的前面，不会出现向后看的情形
static const float s_def_front_x=0.0f;
static const float s_def_front_y=0.0f;
static const float s_def_front_z=-1.0f;

//默认的上向量
static const Vector s_up(0.0,1.0,0.0);

Camera::Camera():_pos(s_def_front_x,s_def_front_y,s_def_front_z),
                 _front(s_def_front_x,s_def_front_y,s_def_front_z),
                 _speed(s_def_speed){

}

Camera::~Camera(){

}

void Camera::moveLeft(){

}

void Camera::moveRight(){

}

void Camera::moveForward(){

}

void Camera::moveBack(){

}
