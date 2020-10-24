//
// Created by tam on 2020/9/28.
//

#include "TestCourse.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/geometry/Vector.h"

TestCourse::TestCourse(){

}

TestCourse::~TestCourse(){

}

void TestCourse::load(){
    _line1.load(1,0,0,1);
    _line2.load(0,1,0,1);
    _plane.load(0,0,1,1);
    ht.load(1,0,0,1);
    hollowCube.load(1,0,0,1);
    _axis.load(3,1,0,0,1);
    _m.load(1,0,0,1);
    _n.load(1,0,0,1);
    _o.load(1,0,0,1);
    _sc.load(1.0f,1.0f,1,0,0,1);
}

void TestCourse::onDrawStep(DrawingContext& dc){

    Matrix translateMat(4,4);

    Translate::buildTranslateMatrix(Vector(-0.5,-0.5,-5),translateMat);
    dc.setModelMatrix(translateMat);
    //_line1.draw();
    //_plane.draw();
    //ht.draw();
    hollowCube.draw();
    //_axis.draw();
    //_m.draw();
    //_sc.draw();
    //_o.draw();

    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(0.5,0.5,1),s);
    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(0,0,-6.2),t);
    dc.setModelMatrix(Matrix::multiply(t,s));
    _n.draw();

    /*
    Translate::buildTranslateMatrix(Vector(0.0,1.0,-5.0),translateMat);
    dc.setModelMatrix(translateMat);
    _line2.draw();
     */

}

static const Vector cv(0,0,-5.5);

const Vector* TestCourse::getSceneCenterV()const{
    return &cv;
}