//
// Created by tam on 2021/7/23.
//

#include "Course6.h"
#include "DrawingContext.h"
#include "../base/math/Matrix.h"
#include "../base/geometry/Projections.h"
#include "../base/transforms/Translate.h"
#include "../base/geometry/Vector.h"

static Matrix prjMat(4,4);
static const Vector gt1(0,-3,-1.5);
static const Vector gt2(0,-3,-11.5);

Course6::Course6() {
    Projections::buildPerspectiveProjectionMatrix(-1,1,1,-1,1,10,prjMat);
}

const Matrix* Course6::getCustomProjection()const{

    //return &prjMat;
    return NULL;
}

void Course6::load(){
    _Line1.load(
       0,0,-1,
       0,0,-1.5,
       1,0,0,1
    );

    _Line2.load(
      0,0,-1.5,
      10,0,-1.5,
      0,1,0,1
    );

    _axis1.load(10,1,0,0,1);
    _axis2.load(10,0,1,0,1);
}

void Course6::onDrawStep(DrawingContext& dc){
    Matrix t(4,4);

    Translate::buildTranslateMatrix(gt1,t);
    dc.setModelMatrix(t);
    _axis1.draw();


    Translate::buildTranslateMatrix(gt2,t);
    dc.setModelMatrix(t);
    _axis2.draw();

    //_Line1.draw();
    //_Line2.draw();

}
