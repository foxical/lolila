//
// Created by Administrator on 2017/10/20.
//

#include <stdexcept>
#include "Translate.h"
#include "../geometry/Vector.h"
#include "../math/Matrix.h"

void Translate::buildTranslateMatrix(const Vector& T, Matrix& M){

    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }

    M.zero();
    M.set(0,0,1.0f);  /*0*/               /*0*/              M.set(0,3,T.x());
    /*0*/             M.set(1,1,1.0f);    /*0*/              M.set(1,3,T.y());
    /*0*/             /*0*/               M.set(2,2,1.0f);   M.set(2,3,T.z());
    /*0*/             /*0*/               /*0*/              M.set(3,3,1.0f);

}

Vector Translate::doTransform(const Vector& T, const Vector& in){

    Matrix M(4,4);
    buildTranslateMatrix(T,M);
    Matrix P(4,1);
    P.set(0,0,in.x());P.set(1,0,in.y());P.set(2,0,in.z());P.set(3,0,1.0f);
    const Matrix PZ = Matrix::multiply(M,P);
    return Vector(PZ.get(0,0),PZ.get(1,0),PZ.get(2,0));
}