//
// Created by TanLinghui on 2017/6/5.
//

#include "Projections.h"
#include <stdexcept>
#include "Vector.h"
#include "../math/Matrix.h"
#include "../utils/LogQueue.h"

Vector Projections::perspectiveProjection(
        const double& l,const double& t,const double& r,const double& b,
        const double& n,const double& f,
        const Vector& p){

    Matrix M(4,4);
    M.set(0,0,2.0*n/(r-l)); M.set(0,1,0);         M.set(0,2,(r+l)/(r-l));      M.set(0,3,0);
    M.set(1,0,0);         M.set(1,1,2.0*n/(t-b)); M.set(1,2,(t+b)/(t-b));      M.set(1,3,0);
    M.set(2,0,0);         M.set(2,1,0);         M.set(2,2,-1.0*(f+n)/(f-n));   M.set(2,3,-2.0*n*f/(f-n));
    M.set(3,0,0);         M.set(3,1,0);         M.set(3,2,-1);               M.set(3,3,0);

    //LogQueue::push("M is %s",M.c_str());

    Matrix P(4,1);
    P.set(0,0,p.x());P.set(1,0,p.y());P.set(2,0,p.z());P.set(3,0,1);

    const Matrix PZ = Matrix::multiply(M,P);
    const double wc = PZ.get(3,0);
    //LogQueue::push("pz' is %g,wc is %g\n",PZ.get(2,0),wc);
    return Vector(PZ.get(0,0)/wc,PZ.get(1,0)/wc,PZ.get(2,0)/wc);
}

Vector Projections::perspectiveProjection_v2(
        const double& l,const double& t,const double& r,const double& b,
        const double& n,const double& f,
        const Vector& P){

    const double px = P.x();
    const double py = P.y();
    const double pz = P.z();

    const double x = ((2*n)/(r-l))*(-1*px/pz)-((r+l)/(r-l));
    const double y = ((2*n)/(t-b))*(-1*py/pz)-((t+b)/(t-b));
    const double z = (-2*pz-2*f)/(f-n) +1;
    return Vector(x,y,z);
}

