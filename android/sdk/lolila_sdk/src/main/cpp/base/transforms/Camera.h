//
// Created by Administrator on 2017/11/6.
//

#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifndef __VECTOR_H__
#include "../geometry/Vector.h"
#endif

class Matrix;

class Camera {
public:
    Camera();
    ~Camera();
public:


    void moveUp();

    void moveDown();

    /**
     * 向左平移
     */
    void moveLeft();

    /**
     * 向右平移
     */
    void moveRight();

    /**
     * 向前进，摄像机靠近物体，向Z轴反向移动
     */
    void moveForward();




    /**
     * 向后退，摄像机远离物体，向Z轴正向移动
     */
    void moveBack();

    void pitchDown();
    void pitchUp();

    void yawLeft();
    void yawRight();

    void resetPos();

    void setSceneCenterPos(const Vector* cv);
    void lookAtSceneCenter();
    void rotateAroundSceneCenter(
            const Vector& axis,
            float angle,
            bool lockCameraR= false,
            bool lockCameraD=false,
            bool lockCameraU= false
    );


public:

    void buildLookAtMatrix(Matrix& M)const;

    const Vector& getCameraPos()const{
        return _pos;
    }
    const Vector& getCameraAxisR()const{
        return _right;
    }
    const Vector& getCameraAxisU()const{
        return _up;
    }
    const Vector& getCameraAxisD()const{
        return _direct;
    }
    const Vector& getSceneCenterPos()const{
        return _sceneCenterPos;
    }

    float getYaw(const Vector& pos)const;
    float getPitch(const Vector& pos)const;

private:

    void rotateFront( float angle,
                      bool lockCameraR,
                      bool lockCameraD,
                      bool lockCameraU);

private:
    Vector _pos; // 摄像机位置
    Vector _front;
    Vector _up;
    Vector _right;
    Vector _direct;
    float _speed;//移动速度

    Vector _sceneCenterPos;

};


#endif //__CAMERA_H__
