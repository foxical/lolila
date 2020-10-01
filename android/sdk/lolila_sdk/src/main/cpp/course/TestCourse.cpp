//
// Created by tam on 2020/9/28.
//

#include "TestCourse.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
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
}

void TestCourse::onDrawStep(DrawingContext& dc){

    Matrix translateMat(4,4);

    Translate::buildTranslateMatrix(Vector(0,0,-5),translateMat);
    dc.setModelMatrix(translateMat);
    //_line1.draw();
    //_plane.draw();
    ht.draw();

    /*
    Translate::buildTranslateMatrix(Vector(0.0,1.0,-5.0),translateMat);
    dc.setModelMatrix(translateMat);
    _line2.draw();
     */

}