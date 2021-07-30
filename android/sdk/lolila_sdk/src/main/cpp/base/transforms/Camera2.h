//
// Created by Administrator on 2017/11/6.
//

#ifndef __CAMERA2_H__
#define __CAMERA2_H__

#ifndef __VECTOR_H__
#include "../geometry/Vector.h"
#endif

#include <glm/glm.hpp>

class Matrix;

class Camera2 {
public:
    Camera2();
    ~Camera2();
public:

    /**
     * 根据当前头顶_up方向向上移动
     */
    void moveUp();

    /**
     * 根据当前头顶_up方向的相反方向向下移动
     */
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

            float angle,
            bool lockCameraR= false,
            bool lockCameraD=false,
            bool lockCameraU= false
    );

    void rotateAroundSceneCenterLockY(float angle);

public:

    glm::mat4 buildLookAtMatrix()const;



    const Vector& getCameraPos()const{
        return _pos;
    }
    const Vector& getCameraAxisU()const{
        return _up;
    }

    const Vector& getSceneCenterPos()const{
        return _sceneCenterPos;
    }
    const Vector& getCameraFront()const{
        return _front;
    }

    /**
     * @deprecated
     * @param pos
     * @return
     */
    float getYaw(const Vector& pos)const;

    /**
     * @deprecated
     * @param pos
     * @return
     */
    float getPitch(const Vector& pos)const;

    float getFrontPitch()const;
    float getFrontYaw()const;

private:

    void rotateFront( float angle,
                      bool lockCameraR,
                      bool lockCameraD,
                      bool lockCameraU);


    void pitch(float angle);
    void yaw(float angle);

    glm::vec3 pitchAxis()const;
    glm::vec3 yawAxis()const;

private:
    Vector _pos;    // 摄像机位置
    Vector _front;  // 朝向
    Vector _up;  // 如果需要歪头，可以调整这个，否则一般不需要调整，默认(0,1,0)
    Vector _sceneCenterPos;
    float _speed;//移动速度


};


#endif //__CAMERA2_H__
