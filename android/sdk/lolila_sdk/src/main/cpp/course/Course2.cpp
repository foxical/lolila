//
// Created by tam on 2020/10/16.
//

#include "Course2.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/transforms/Rotation.h"
#include "../base/geometry/Vector.h"

Course2::Course2():_step(0){

}
Course2::~Course2(){

}

void Course2::load(){
    _axis.load(35,0,0,0,1);
    _o.load(0,0,0,1);
    _lineP.load(1,0,0,1);
    _lineM.load(0,1,0,1);
    _lineQ.load(0,0,1,1);
    _m.load(0,0,0,1);
    _n.load(0,0,0,1);
    _c.load(0,0,0,1);
}

const GLfloat axis_unit_x = 0.20f;
const GLfloat axis_offset_x = -17;

static void drawAxis(Matrix& M, DrawingContext& dc,const SimpleAxis& _axis){

    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(axis_offset_x,-1,-5),t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(axis_unit_x,0.5,1),s);
    M.set(Matrix::multiply(s,t));
    dc.setModelMatrix(M);
    _axis.draw();
}

static void drawO(Matrix& M, DrawingContext& dc,const SymbleO& _o){
    const GLfloat w = _o.getWidth();
    const GLfloat h = _o.getHeight();
    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(-w/2+axis_offset_x,-h-1.5,-5),t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(axis_unit_x,0.5,1),s);
    M.set(Matrix::multiply(s,t));
    dc.setModelMatrix(M);
    _o.draw();
}

static void drawC(Matrix& M, DrawingContext& dc,const SymbleC& _c){

    const GLfloat w = _c.getWidth();
    const GLfloat h = _c.getHeight();

    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(-w/2+axis_offset_x+30,-h-1.5,-5),t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(axis_unit_x,0.5,1),s);
    M.set(Matrix::multiply(s,t));
    dc.setModelMatrix(M);
    _c.draw();
}

static void drawM(Matrix& M, DrawingContext& dc,const SymbleM& _m){

    const GLfloat w = _m.getWidth();
    const GLfloat h = _m.getHeight();

    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(-w/2+axis_offset_x+4,-h-1.5,-5),t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(axis_unit_x,0.5,1),s);
    M.set(Matrix::multiply(s,t));
    dc.setModelMatrix(M);
    _m.draw();
}

static void drawN(Matrix& M, DrawingContext& dc,const SymbleN& _n){

    const GLfloat w = _n.getWidth();
    const GLfloat h = _n.getHeight();

    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(-w/2+axis_offset_x+16,-h-1.5,-5),t);
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(axis_unit_x,0.5,1),s);
    M.set(Matrix::multiply(s,t));
    dc.setModelMatrix(M);
    _n.draw();
}


static void drawLineP(Matrix& M, DrawingContext& dc,const SimpleLine& _lineP,int _step){


    Matrix r(4,4);
    Rotation::buildRotationMatrix(Vector(0,0,-1),-90,r);
    Matrix t(4,4);
    int distance = (axis_offset_x+4+3*_step);
    const int maxDistance = axis_offset_x+30;
    if(distance>maxDistance)distance=maxDistance;
    Translate::buildTranslateMatrix(Vector( distance*axis_unit_x ,0.5,-5),t);
    M.set(Matrix::multiply(t,r));
    dc.setModelMatrix(M);
    _lineP.draw();
}


static void drawLineQ(Matrix& M, DrawingContext& dc,const SimpleLine& _lineQ,int _step){


    Matrix r(4,4);
    Rotation::buildRotationMatrix(Vector(0,0,-1),-90,r);
    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector( (axis_offset_x+16+1*_step)*axis_unit_x ,0.2,-5),t);
    M.set(Matrix::multiply(t,r));
    dc.setModelMatrix(M);
    _lineQ.draw();
}

void Course2::onDrawStep(DrawingContext& dc){

    Matrix m(4,4);

    drawAxis(m,dc,_axis);
    drawO(m,dc,_o);
    drawM(m,dc,_m);
    drawN(m,dc,_n);
    drawC(m,dc,_c);
    drawLineP(m,dc,_lineP,_step);
    drawLineQ(m,dc,_lineQ,_step);
}


void Course2::nextStep(){
    if(_step<getTotalStepsCount()){
        ++_step;
    }
}
void Course2::prevStep(){
    if(_step>0){
        --_step;
    }
}
void Course2::reset(){
    _step=0;
}
