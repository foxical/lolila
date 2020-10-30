//
// Created by Administrator on 2017/11/6.
//

#include "Camera.h"
#include "MVPTransform.h"
#include "Rotation.h"
#include "../math/Matrix.h"
#include "../utils/FloatUtils.h"
#include "../utils/AndroidLog.h"
#include "Translate.h"
#include <math.h>
#include <stdexcept>

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

Camera::Camera():_pos(s_def_pos_x,s_def_pos_y,s_def_pos_z),
                 _front(s_def_front_x,s_def_front_y,s_def_front_z),
                 _up(s_up),
                 _right(s_right),
                 _direct(s_direct),
                 _speed(s_def_speed),
                 _sceneCenterPos(0,0,0){

}

Camera::~Camera(){

}



void Camera::resetPos(){
    _pos = s_def_pos;
    _front=Vector(s_def_front_x,s_def_front_y,s_def_front_z);
    _up=s_up;
    _right=s_right;
    _direct=s_direct;
    _speed=s_def_speed;

}

void Camera::moveUp() {
    _pos = Vector::add(_pos,Vector::scalarMultiply(s_up.normalize(),_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera::moveDown() {
    _pos = Vector::minus(_pos,Vector::scalarMultiply(s_up.normalize(),_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera::moveLeft(){
    Vector temp = Vector::cross(_front,s_up).normalize();
    _pos = Vector::minus(_pos,Vector::scalarMultiply(temp,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera::moveRight(){
    Vector temp = Vector::cross(_front,s_up).normalize();
    _pos = Vector::add(_pos,Vector::scalarMultiply(temp,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera::moveForward(){
    _pos = Vector::add(_pos,Vector::scalarMultiply(_front,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}

void Camera::moveBack(){
    _pos = Vector::minus(_pos,Vector::scalarMultiply(_front,_speed));
    LOGD("  vPos:%s",_pos.c_str());
}


void Camera::pitchDown(){
    rotateFront(-s_def_ra_step,true,false,false);
}

void Camera::pitchUp(){
    rotateFront(s_def_ra_step,true,false,false);
}

void Camera::yawLeft(){
    rotateFront(s_def_ra_step,false,false,true);
}

void Camera::yawRight() {
    rotateFront(-s_def_ra_step,false,false,true);
}

void Camera::setSceneCenterPos(const Vector* cv){
    if(cv!=NULL){
        _sceneCenterPos = *cv;
    }
}

void Camera::lookAtSceneCenter(){
    if( _pos.isEqual(_sceneCenterPos)){
        return;
    }

    _front = Vector(
            _sceneCenterPos.x()-_pos.x(),
            _sceneCenterPos.y()-_pos.y(),
            _sceneCenterPos.z()-_pos.z()
    ).normalize();
    // Also re-calculate the Right and Up vector
    _right = Vector::cross(_front,s_up).normalize();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _up = Vector::cross(_right, _front).normalize();
    Vector vDTemp = Vector::add(_pos,_front);
    _direct = Vector::minus(_pos,vDTemp).normalize();
}

float Camera::getYaw(const Vector& scv)const{

    if(_pos.isEqual(scv)){
        return 0.0f;
    }

    float yaw=0.0f;

    // 四种特殊情况
    if( FloatUtils::isEqual(_pos.x(),scv.x()) ){
        if( _pos.z()>scv.z()){
            yaw = -90.0f;
        }else if( _pos.z()<scv.z()){
            yaw = -270.0f;
        }else{
            throw runtime_error(" lookAtSceneCenterYaw isEqual(_pos.z(),scv.z()) ");
        }

    }else if( FloatUtils::isEqual(_pos.z(),scv.z()) ){
        if( _pos.x()>scv.x()){
            yaw = -180.0f;
        }else if( _pos.x()<scv.x()){
            yaw = 0.0f;
        }else{
            throw runtime_error(" lookAtSceneCenterYaw isEqual(_pos.x(),scv.x())");
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

float Camera::getPitch(const Vector& scv)const{


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

void Camera::rotateAroundSceneCenterLockY(float angle){
    if(FloatUtils::isEqual(angle,0.0f)){
        return;
    }
    if( _pos.isEqual(_sceneCenterPos)){
        return;
    }

    const Vector axis(0,1,0);

    const float ax = _sceneCenterPos.x();
    const float ay = _sceneCenterPos.y();
    const float az = _sceneCenterPos.z();
    //LOGD("before rotate,px:%f,py:%f,pz:%f",_pos.x(),_pos.y(),_pos.z());
    Vector before( _pos.x()-ax,_pos.y()-ay,_pos.z()-az);
    Vector after = Rotation::doTransform(axis,angle,before);
    _pos = Vector(after.x()+ax,after.y()+ay,after.z()+az);

    _front = Rotation::doTransform(axis,angle,_front);
    // Also re-calculate the Right and Up vector
    _right = Vector::cross(_front,s_up).normalize();  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _up = Vector::cross(_right, _front).normalize();
    Vector vDTemp = Vector::add(_pos,_front);
    _direct = Vector::minus(_pos,vDTemp).normalize();
}

void Camera::rotateAroundSceneCenter(float angle,
                                     bool lockCameraR,
                                     bool lockCameraD,
                                     bool lockCameraU ){

    if(FloatUtils::isEqual(angle,0.0f)){
        return;
    }
    if( _pos.isEqual(_sceneCenterPos)){
        return;
    }

    const Vector* axis=NULL;
    if( lockCameraR){
        axis = &_right;
    }else if(lockCameraU){
        axis = &_up;
    }else if(lockCameraD){
        axis = &_direct;
    }


    const float ax = _sceneCenterPos.x();
    const float ay = _sceneCenterPos.y();
    const float az = _sceneCenterPos.z();
    //LOGD("before rotate,px:%f,py:%f,pz:%f",_pos.x(),_pos.y(),_pos.z());
    Vector before( _pos.x()-ax,_pos.y()-ay,_pos.z()-az);
    Vector after = Rotation::doTransform(*axis,angle,before);
    _pos = Vector(after.x()+ax,after.y()+ay,after.z()+az);
    //LOGD("  vPos:%s",_pos.c_str());


    rotateFront(angle,lockCameraR,lockCameraD,lockCameraU);

}

void Camera::rotateFront( float angle,
                          bool lockCameraR,
                          bool lockCameraD,
                          bool lockCameraU){
    if(lockCameraR){

        _front = Rotation::doTransform(_right,angle,_front);
        _up = Vector::cross(_right,_front);
        Vector vDTemp = Vector::add(_pos,_front);
        _direct = Vector::minus(_pos,vDTemp).normalize();

    }else if(lockCameraU){

        _front = Rotation::doTransform(_up,angle,_front);
        _right = Vector::cross(_front,_up).normalize();
        Vector vDTemp = Vector::add(_pos,_front);
        _direct = Vector::minus(_pos,vDTemp).normalize();

    }else if( lockCameraD){
        return; // not support yet!!
    }
}



void Camera::buildLookAtMatrix(Matrix& M)const{

    LOGD("---------------------------------------------------------------------");
    //LOGD("yaw:%f, pitch:%f", _yaw,_pitch);
    LOGD("  vPos:%s",_pos.c_str());
    LOGD("vFront:%s",_front.c_str());
    LOGD("    vD:%s",_direct.c_str());
    LOGD("    vR:%s",_right.c_str());
    LOGD("    vU:%s",_up.c_str());

#if 0

    Vector vecLookAt = Vector::add(_pos,_front);
    MVPTransform::buildLookAtMatrix(
            _pos.x(),    _pos.y(),    _pos.z(),
            vecLookAt.x(), vecLookAt.y(), vecLookAt.z(),
            _up,
            M
    );

#endif

#if 1

    // 上向量必须与方向向量垂直
    if( !FloatUtils::isEqual(Vector::dot(_direct,_up),0.0f) ){
        throw runtime_error("vector UP must vDirect");
    }
    if( !FloatUtils::isEqual(Vector::dot(_direct,_right),0.0f) ){
        throw runtime_error("vector D must R");
    }
    if( !FloatUtils::isEqual(Vector::dot(_up,_right),0.0f) ){
        throw runtime_error("vector UP must R");
    }

    // 以上叉乘注意顺序不要搞错，遵守右手法则，三个新轴的方向和OPENGL世界坐标系的方向完全相同
    // 三个新轴向量都必须是单位向量，即三个新轴是规范正交基
    /// 因为轴的长度是1，因此旋转矩阵可以简化为以下形式，消去了角度的因素，即和旋转角度无关
    const Vector& vRight=_right;
    const Vector& vDirect=_direct;
    const Vector& vU=_up;
    const float& posX=_pos.x();
    const float& posY=_pos.y();
    const float& posZ=_pos.z();

    Matrix M0(4,4);
    M0.set(0,0, vRight.x());   M0.set(0,1, vRight.y());   M0.set(0,2, vRight.z());   //M0.set(0,3, 0.0f);
    M0.set(1,0, vU.x());       M0.set(1,1, vU.y());       M0.set(1,2, vU.z());       //M0.set(1,3, 0.0f);
    M0.set(2,0, vDirect.x());  M0.set(2,1, vDirect.y());  M0.set(2,2, vDirect.z());  //M0.set(2,3, 0.0f);
    /*M0.set(3,0, 0.0f);         M0.set(3,1,0.0f)         M0.set(3,2, 0.0f);*/         M0.set(3,3, 1.0f);
    //LOGD("MO:%s",M0.c_str());


    Matrix M1(4,4);
    Translate::buildTranslateMatrix(Vector(-posX,-posY,-posZ),M1);

    //!!! 这里先平移，即先把坐标原点重合，再做变换
    M.set(Matrix::multiply(M0,M1));

#endif

}