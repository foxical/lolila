//
// Created by tam on 2020/7/16.
//

#ifndef __DOUBLEOUTPUTADAPTER_HPP__
#define __DOUBLEOUTPUTADAPTER_HPP__

#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

#ifndef __FLOATUTILS_H__
#include "../utils/FloatUtils.h"
#endif

struct DoubleOutputAdapter{

    static string toString(const double& f ){
        std::stringstream output;
        output<<f;
        return output.str();
    }

    static bool isZero(const double& f){
        return FloatUtils::isEqualD(f,0.0f);
    }

    static double reciprocal(const double& f){
        if( isZero(f)){
            throw logic_error("can not reciprocal with a zero");
        }
        return 1.0/f;
    }

    static bool isEqualD(const double& f,const double& d ){
        return FloatUtils::isEqualD(f,d);
    }

    static bool isEqualOne(const double& f ){
        return FloatUtils::isEqualD(f,1.0f);
    }
};


#endif //__DOUBLEOUTPUTADAPTER_HPP__
