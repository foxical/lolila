//
// Created by Administrator on 2017/11/6.
//

#ifndef __CAMERA_H__
#define __CAMERA_H__

#ifndef __VECTOR_H__
#include "../geometry/Vector.h"
#endif

class Camera {
public:
    Camera();
    ~Camera();
public:

    void moveLeft();
    void moveRight();
    void moveForward();
    void moveBack();

private:
    Vector _pos; // 摄像机位置
    Vector _front;
    float _speed;//移动速度
};


#endif //__CAMERA_H__
