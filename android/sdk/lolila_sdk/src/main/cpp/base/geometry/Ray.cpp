//
// Created by Administrator on 2017/3/24.
//

#include <stdexcept>
#include <math.h>
#include "Ray.h"

Ray::Ray(const Vector &S, const Vector &V):_endpoint(S),_direction(V) {
    if( S.dim()!=V.dim()){
        throw  runtime_error("Dim of S not equal with V!");
    }
}

Ray::~Ray() {

}

Vector Ray::pointAt(const float &t) const {
    if( t<0.0){
        throw out_of_range(" t must >=0 ");
    }
    return Vector::add(_endpoint,Vector::scalarMultiply(_direction,t));
}

float Ray::distance(const Vector &Q) const {
    const Vector& S = _endpoint;
    const Vector& V = _direction;
    const Vector Q_S = Vector::minus(Q,S);
    const Vector proj_Q_S_V = Vector::proj(Q_S,V);
    return sqrtf( powf(Q_S.length(),2.0) - powf(proj_Q_S_V.length(),2.0) );
}
