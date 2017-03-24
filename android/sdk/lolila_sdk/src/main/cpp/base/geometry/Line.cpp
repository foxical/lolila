//
// Created by Administrator on 2017/3/24.
//


#include <stdexcept>
#include "Line.h"
#include "Ray.h"

Line::Line(const Vector &p1, const Vector &p2):_point1(p1),_point2(p2) {
    if( p1.dim()!=p2.dim()){
        throw  runtime_error("Dim P1 not equal with P2!");
    }
}

Line::~Line() {

}

Vector Line::pointAt(const float &t) const {
    if( t<0.0||t>1.0){
        throw out_of_range(" 0<t<1");
    }
    return Vector::add(Vector::multiply(_point1,1-t),Vector::multiply(_point2,t));
}

float Line::distance(const Vector& Q)const{
    const Ray innerRay(_point1,Vector::minus(_point2,_point1));
    return innerRay.distance(Q);
}