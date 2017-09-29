//
// Created by Administrator on 2017/3/24.
//

#include <stdexcept>
#include <math.h>
#include "Ray.h"
#include "../utils/FloatUtils.h"
#include "../utils/LogQueue.h"

Ray::Ray(const Vector &S, const Vector &V):_endpoint(S),_direction(V) {
    if( S.dim()!=V.dim()){
        throw  runtime_error("Dim of S not equal with V!");
    }
}

Ray::Ray(const Ray& r):_endpoint(r._endpoint),_direction(r._direction) {

}

Ray::~Ray() {

}

Vector Ray::pointAt(const double &t) const {
    return Vector::add(_endpoint,Vector::scalarMultiply(_direction,t));
}

double Ray::distance(const Vector &Q) const {
    const Vector& S = _endpoint;
    const Vector& V = _direction;
    const Vector Q_S = Vector::minus(Q,S);
    const Vector proj_Q_S_V = Vector::proj(Q_S,V);
    // 如果f1和和f2相同的话，直接相减会出现误差，而不是0，因此需要使用工具函数
    const double f1 = pow(Q_S.length(),2.0);
    //LogQueue::push("f1:%g\n",f1);
    const double f2 = pow(proj_Q_S_V.length(),2.0);
    //LogQueue::push("f2:%g\n",f2);
    return sqrt( FloatUtils::minus(f1,f2));
}

const Vector& Ray::endPoint()const{
    return _endpoint;
}

const Vector& Ray::direction()const{
    return _direction;
}

bool Ray::pointLiesInRay(const Vector& Q)const{
    /*
    const Vector& S = _endpoint;
    const Vector& V = _direction;
    const Vector Q_S = Vector::minus(Q,S);
    const Vector proj_Q_S_V = Vector::proj(Q_S,V);
    return FloatUtils::isEqual(Q_S.length(),proj_Q_S_V.length());
     */
   return FloatUtils::isEqual(distance(Q),0.0);
}
