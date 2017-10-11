//
// Created by Administrator on 2017/4/6.
//

#include "Plane.h"
#include "../utils/FloatUtils.h"
#include <math.h>

Plane::Plane(const Vector &N, const Vector &P):_n(N),_p(P) {
}

Plane::~Plane() {
}

bool  Plane::pointLiesInPlane(const Plane &plane, const Vector &Q){
    const Vector& N = plane._n;
    const Vector& P = plane._p;
    const Vector Q_P = Vector::minus(Q,P);
    return FloatUtils::isEqual(Vector::dot(N,Q_P),0.0f);
}

bool  Plane::pointLiesInPlane( const Vector& Q)const{
    return pointLiesInPlane(*this, Q);
}

float Plane::distanceFromOri()const{
    return fabsf(D())/N().length();
}
