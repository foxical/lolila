//
// Created by tam on 2020/7/16.
//

#ifndef __FLOATOUTPUTADAPTER_HPP__
#define __FLOATOUTPUTADAPTER_HPP__

#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

#ifndef __FLOATUTILS_H__
#include "../utils/FloatUtils.h"
#endif

struct FloatOutputAdapter{

    static string toString(const float & f ){
        std::stringstream output;
        output<<f;
        return output.str();
    }

    static bool isZero(const float& f){
        return FloatUtils::isEqual(f,0.0f);
    }

    static float reciprocal(const float& f){
        if( isZero(f)){
            throw logic_error("can not reciprocal with a zero");
        }
        return 1.0/f;
    }

    static float reciprocal_N(const float& f){
        if( isZero(f)){
            throw logic_error("can not reciprocal with a zero");
        }
        float r = 1.0/f;
        if( f<0.0f){
            r*= -1.0f;
        }
        return r;
    }

    static bool isEqualD(const float & f,const double& d ){
        return FloatUtils::isEqualD(f,d);
    }

    static bool isEqualOne(const float & f ){
        return FloatUtils::isEqual(f,1.0f);
    }

    static float abs(const float & f){
        return fabs(f);
    }
};


#endif //__FLOATOUTPUTADAPTER_HPP__
