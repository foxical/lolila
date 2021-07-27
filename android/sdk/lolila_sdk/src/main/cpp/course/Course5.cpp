//
// Created by tam on 2020/11/6.
//

#include <glm/glm.hpp>
#include "Course5.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/transforms/Rotation.h"
#include "../base/geometry/Vector.h"
#include "../base/geometry/Ray.h"
#include "../base/geometry/Triangle.h"
#include "../base/geometry/Box.h"
#include "../base/utils/AndroidLog.h"
#include "../base/transforms/MultiTransform.h"

static const Vector gt(-5,-3,-10);  // global translate
static const Vector box_lt(3,4,-3); // box local translate

static const glm::vec3 vec3_gt(-5,-3,-6);  // global translate

const float box_w=2;
const float box_h=2;
const float box_d=2;

static const int cycle = 2;
static int c_count=0;
static float ray_rotate_angle=0.0f;
const Vector initRayV(1,1,0);
const Vector initRayS(0,0,0);
static Matrix boxMat(4,4);
static bool allowDrawCute=false;

void Course5::load(){
    _coordinate.load(0,0,0,1);
    _cube.load(1,0,0,1);
    _tri1.load(
            0,0,0,
            1,0,0,
            1,1,0,
            0,1,0,1);
    _tri2.load(
            0,0,0,
            1,1,0,
            0,1,0,
            0,0,1,1);

    ray_rotate_angle=0.0f;
}









#if 0
static bool drawRay(DrawingContext& dc){
    c_count++;
    if(c_count<cycle){
        return false;
    }
    c_count=0;

    const Vector rayVR = Rotation::doTransform(Vector(0,1,0),ray_rotate_angle,initRayV);
    const Ray ray(initRayS,rayVR);


    Box calcBox(box_w,box_h,box_d);
    calcBox.translate(Vector(0,-(box_h)/2,box_d/2));
    calcBox.rotate(Vector(1,0,0),ray_rotate_angle);
    calcBox.translate(Vector(0,box_h/2,-(box_d)/2));
    calcBox.translate(box_lt);
    boxMat.set(calcBox.geCurTransformMat());
    allowDrawCute=true;

    Vector crossPoint(0,0,0);
    Vector weight(0,0,0);
    if( calcBox.surfaceIntersectionCheck(ray,crossPoint,weight)){

    }else{
        crossPoint = ray.pointAt(6);
    }


    /*
    SimpleLine line;
    line.load(0,0,0,crossPoint.x(),crossPoint.y(),crossPoint.z(),0,1,0,1);
    Matrix t(4, 4);
    Translate::buildTranslateMatrix(gt, t);
    dc.setModelMatrix(t);
    line.draw();
    */

    ray_rotate_angle -= -1.0f;

    /* 不要这样直接比较大小，会出古怪问题
    if( ray_rotate_angle<=-360.0f ){
        ray_rotate_angle=0.0f;
    }
    */



    return true;
}
#endif

void Course5::onDrawStep(DrawingContext& dc){


    MultiTransform cordTransform;
    cordTransform.translate(vec3_gt);
    cordTransform.scale(glm::vec3(6,6,6));
    dc.setModelMatrix(cordTransform.getMat());
    _coordinate.draw();

    MultiTransform boxTransform;
    boxTransform.translate(vec3_gt);
    boxTransform.translate(glm::vec3(1,4,-3));
    boxTransform.rotate(ray_rotate_angle,glm::vec3(1,0,0));
    boxTransform.translate(glm::vec3(1,-(box_h/2),box_d/2));
    boxTransform.scale(glm::vec3(box_w,box_h,box_d));

    dc.setModelMatrix(boxTransform.getMat());
    _cube.draw();
    _tri1.draw();
    _tri2.draw();

    MultiTransform vTransform;
    vTransform.rotate(ray_rotate_angle,glm::vec3(0,1,0));
    const Vector rayV = MultiTransform::doTransform(vTransform.getMat(),initRayV);

    MultiTransform sTransform;
    sTransform.translate(vec3_gt);
    const Vector rayS = MultiTransform::doTransform(sTransform.getMat(),initRayS);

    const Ray ray(rayS,rayV);

    Box calcBox(boxTransform.getMat());
    Vector crossPoint(0,0,0);
    Vector weight(0,0,0);
    bool bingo=false;
    if( calcBox.surfaceIntersectionCheck(ray,crossPoint,weight)){
        bingo=true;
    }else{
        crossPoint = ray.pointAt(6);
    }

    SimpleLine line;
    if( bingo) {
        line.load(rayS.x(), rayS.y(), rayS.z(), crossPoint.x(), crossPoint.y(), crossPoint.z(), 1, 0, 1, 1);
    }else{
        line.load(rayS.x(), rayS.y(), rayS.z(), crossPoint.x(), crossPoint.y(), crossPoint.z(), 0, 0, 0, 1);
    }
    dc.setModelMatrix(glm::mat4(1));
    line.draw();



    ray_rotate_angle -= -1.0f;

}

static const Vector cv(-5,0,-10);
const Vector* Course5::getSceneCenterV()const{
    return &cv;
}