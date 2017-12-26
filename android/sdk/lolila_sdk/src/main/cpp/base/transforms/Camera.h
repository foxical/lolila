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

    void resetPos();

public:

    void buildLookAtMatrix(Matrix& M)const;

private:

    void updateVectors();

private:
    Vector _pos; // 摄像机位置
    Vector _front;
    Vector _up;
    float _speed;//移动速度
    float _pitch;// 俯仰角
};


#endif //__CAMERA_H__
