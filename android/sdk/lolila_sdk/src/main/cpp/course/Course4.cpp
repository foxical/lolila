//
// Created by tam on 2020/11/5.
//

#include "Course4.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/transforms/Rotation.h"
#include "../base/geometry/Vector.h"
#include "../base/geometry/Ray.h"
#include "../base/geometry/Triangle.h"
#include "../base/utils/AndroidLog.h"

static const Vector gt(-5,-3,-10);

const float tx0=5,ty0=0,tz0=0,tx1=0,ty1=0,tz1=-5,tx2=0,ty2=5,tz2=0;

void Course4::load(){
    _coordinate.load(0,0,1,1);
    _triangle.load(tx0,ty0,tz0,tx1,ty1,tz1,tx2,ty2,tz2,1,0,0,1);

}



static void drawCoordinate(DrawingContext& dc,Simple3DCoordinate& coordinate){

    Matrix t(4,4);
    Translate::buildTranslateMatrix(gt,t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(10,10,10),s);

    dc.setModelMatrix(Matrix::multiply(t,s));

    coordinate.draw();
}

static void drawTriangle(DrawingContext& dc,SimpleTriangle& triangle){

    Matrix t(4,4);
    Translate::buildTranslateMatrix(gt,t);

    dc.setModelMatrix(t);

    triangle.draw();
}


static const int cycle = 2;
static int c_count=0;
static float ray_rotate_angle=0.0f;
const Triangle calcT(tx0,ty0,tz0,tx1,ty1,tz1,tx2,ty2,tz2);
const Vector initRayV(1,1,0);
const Vector initRayS(0,0,0);

static void drawRay(DrawingContext& dc){
    c_count++;
    if(c_count<cycle){
        return;
    }
    c_count=0;

    const Vector rayVR = Rotation::doTransform(Vector(0,1,0),ray_rotate_angle,initRayV);
    const Ray ray(initRayS,rayVR);

    Vector crossPoint(0,0,0);
    Vector weight(0,0,0);
    if( calcT.surfaceIntersectionCheck(ray,crossPoint,weight)){

    }else{
        crossPoint = ray.pointAt(6);
    }

    SimpleLine line;
    line.load(0,0,0,crossPoint.x(),crossPoint.y(),crossPoint.z(),0,1,0,1);

    Matrix t(4,4);
    Translate::buildTranslateMatrix(gt,t);
    dc.setModelMatrix(t);
    line.draw();

    ray_rotate_angle -= -1.0f;
    if( ray_rotate_angle<=-360.0f ){
        ray_rotate_angle=0.0f;
    }
}

void Course4::onDrawStep(DrawingContext& dc){

    drawCoordinate(dc,_coordinate);
    drawTriangle(dc,_triangle);
    drawRay(dc);
}


static const Vector cv(-5,0,-10);

const Vector* Course4::getSceneCenterV()const{
    return &cv;
}