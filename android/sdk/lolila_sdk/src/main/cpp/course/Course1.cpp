//
// Created by tam on 2020/10/1.
//

#include "Course1.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/transforms/Rotation.h"
#include "../base/geometry/Vector.h"


static void makeScaleMatT(Matrix& M ){
    Vector vector(1,2,1);//scale the triangle y to 2x
    Scaling::buildScalingMatrix(vector,M);
}

static void makeLineMat(Matrix& M ){
    Matrix sm(4,4);
    Scaling::buildScalingMatrix(Vector(6,1,1),sm);//scale the line x to 6x
    Matrix tm(4,4);
    Translate::buildTranslateMatrix(Vector(-3,0,-5),tm); // move ori
    M.set(Matrix::multiply(tm,sm));
}

static void makeTriangleMat1(Matrix& M,float a ){
    Matrix sm(4,4);
    Scaling::buildScalingMatrix(Vector(1,2,1),sm);//scale the triangle y to 2x
    Matrix rm(4,4);
    Rotation::buildRotationMatrix(Vector(0,0,-1),a,rm); // rotate with z axis
    Matrix tm(4,4);
    Translate::buildTranslateMatrix(Vector(0,0,-5),tm); // move ori
    M.set(Matrix::multiply(tm,Matrix::multiply(rm,sm)));

}

static void makeTriangleMat2(Matrix& M,float a ){
    Matrix sm(4,4);
    Scaling::buildScalingMatrix(Vector(1,2,1),sm);//scale the triangle y to 2x
    Matrix rm(4,4);
    Rotation::buildRotationMatrix(Vector(0,0,-1),90,rm); // rotate with z axis
    Matrix tm(4,4);
    Translate::buildTranslateMatrix(Vector(-2,1,-5),tm); // move ori
    Matrix bm = (Matrix::multiply(tm,Matrix::multiply(rm,sm)));

    Matrix am(4,4);
    Rotation::buildRotationMatrix(Vector(0,0,-1),a,am); // rotate with z axis
    M.set(Matrix::multiply(am,bm));
}

Course1::Course1():a1(0.0f),a2(0.0f){

}
Course1::~Course1(){

}

void Course1::load(){

    _baseLine.load(0,0,0,1); // black line
    _t1.load(1,0,0,1);
    _t2.load(0,0,1,1);
}

void Course1::onDrawStep(DrawingContext& dc) {

    Matrix m(4,4);

    makeLineMat(m);
    dc.setModelMatrix(m);
    _baseLine.draw();

    makeTriangleMat1(m,a1);
    dc.setModelMatrix(m);
    _t1.draw();

    makeTriangleMat2(m,a2);
    dc.setModelMatrix(m);
    _t2.draw();
}

void Course1::nextStep(){

    a1 += (-2.0f);
    a2 += (-3.0f);

}
void Course1::prevStep(){
    a1 += (2.0f);
    a2 += (3.0f);
}
void Course1::reset(){
    a1=0.0f;
    a2=0.0f;
}