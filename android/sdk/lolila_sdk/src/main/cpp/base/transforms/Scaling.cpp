//
// Created by Administrator on 2018/2/1.
//

#include <stdexcept>
#include "Scaling.h"
#include "../geometry/Vector.h"
#include "../math/Matrix.h"

void Scaling::buildScalingMatrix(const Vector& S, Matrix& M){
    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }

    M.zero();
    M.set(0,0,S.x());  /*0*/               /*0*/             /*0*/
    /*0*/             M.set(1,1,S.y());    /*0*/             /*0*/
    /*0*/             /*0*/               M.set(2,2,S.z());  /*0*/
    /*0*/             /*0*/               /*0*/              M.set(3,3,1.0f);
}
