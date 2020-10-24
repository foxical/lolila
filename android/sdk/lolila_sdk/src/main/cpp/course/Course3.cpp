//
// Created by tam on 2020/10/18.
//

#include "Course3.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/transforms/Rotation.h"
#include "../base/geometry/Vector.h"
#include "../base/geometry/Ray.h"

Course3::Course3():_step(0){

}
Course3::~Course3(){

}

void Course3::load(){
    _line.load(0,0,0,1);
}

static void drawXYAxis(Matrix& M, DrawingContext& dc,const SimpleLine& _line){
    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(0,-2,-5),t);

    {
        Matrix r(4, 4);
        Rotation::buildRotationMatrix(Vector(0, 0, -1), -90, r);
        Matrix s(4, 4);
        Scaling::buildScalingMatrix(Vector(1, 3, 1), s);
        dc.setModelMatrix(Matrix::multiply(t,s,r));
        _line.draw();
    }

    {
        //Matrix r(4, 4);
        //Rotation::buildRotationMatrix(Vector(0, 0, -1), -90, r);
        Matrix s(4, 4);
        Scaling::buildScalingMatrix(Vector(3, 1, 1), s);
        dc.setModelMatrix(Matrix::multiply(t,s));
        _line.draw();
    }

}

static void drawRay(Matrix& M, DrawingContext& dc,int  _step){
    if(_step<=0){
        return;
    }

    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(0,-2,-5),t);
    dc.setModelMatrix(t);

    const Vector vs = Vector(0.5,0.5,0);

    Ray ray(vs,Vector(1,0,0));
    const Vector pt = ray.pointAt(_step*0.3f);

    SimpleLine t1;
    t1.load(0,0,0,pt.x(),pt.y(),pt.z(),1,0,0,1);
    t1.draw();

    SimpleLine t2;
    t2.load(vs.x(),vs.y(),vs.z(),pt.x(),pt.y(),pt.z(),0,0,1,1);
    t2.draw();

    SimpleLine t3;
    t3.load(0,0,0,vs.x(),vs.y(),vs.z(),0,1,0,1);
    t3.draw();
}


void Course3::onDrawStep(DrawingContext& dc){

    Matrix m(4,4);

    drawXYAxis(m,dc,_line);
    drawRay(m,dc,_step);
}

void Course3::nextStep(){
    if(_step<getTotalStepsCount()){
        ++_step;
    }
}
void Course3::prevStep(){
    if(_step>0){
        --_step;
    }
}
void Course3::reset(){
    _step=0;
}
