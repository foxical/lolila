//
// Created by tam on 2020/11/6.
//

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

static const Vector gt(-5,-3,-10);  // global translate
static const Vector box_lt(3,4,-3); // box local translate

const float box_w=2;
const float box_h=2;
const float box_d=2;

void Course5::load(){
    _coordinate.load(0,0,1,1);
    _cube.load(1,0,0,1);

}



static void drawCoordinate(DrawingContext& dc,Simple3DCoordinate& coordinate){

    Matrix t(4,4);
    Translate::buildTranslateMatrix(gt,t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(10,10,10),s);
    dc.setModelMatrix(Matrix::multiply(t,s));
    coordinate.draw();
}

static const int cycle = 2;
static int c_count=0;
static float ray_rotate_angle=0.0f;
const Vector initRayV(1,1,0);
const Vector initRayS(0,0,0);
static Matrix boxMat(4,4);
static bool allowDrawCute=false;

static void drawCube(DrawingContext& dc,HollowCube& cube){
    if(!allowDrawCute){
        return;
    }

    Matrix t(4,4);
    Translate::buildTranslateMatrix(gt,t);
    dc.setModelMatrix( Matrix::multiply(t,boxMat));
    cube.draw();
}




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

    SimpleLine line;
    line.load(0,0,0,crossPoint.x(),crossPoint.y(),crossPoint.z(),0,1,0,1);
    Matrix t(4, 4);
    Translate::buildTranslateMatrix(gt, t);
    dc.setModelMatrix(t);
    line.draw();

    ray_rotate_angle -= -1.0f;
    if( ray_rotate_angle<=-360.0f ){
        ray_rotate_angle=0.0f;
    }

    return true;
}

void Course5::onDrawStep(DrawingContext& dc){
    drawCoordinate(dc,_coordinate);
    drawRay(dc);
    drawCube(dc, _cube);

}

static const Vector cv(-5,0,-10);
const Vector* Course5::getSceneCenterV()const{
    return &cv;
}