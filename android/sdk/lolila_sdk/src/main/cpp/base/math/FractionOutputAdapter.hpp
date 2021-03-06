//
// Created by tam on 2020/7/16.
//

#ifndef __FRACTIONOUTPUTADAPTER_HPP__
#define __FRACTIONOUTPUTADAPTER_HPP__

#ifndef __FRACTION_H__
#include "Fraction.h"
#endif

#ifndef __FLOATUTILS_H__
#include "../utils/FloatUtils.h"
#endif

#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct FractionOutputAdapter{

    static string toString(const Fraction& f ){
        if(f.isZero()){
            return string("0");
        }else if( f.getNumerator()==f.getDenominator()){
            return string("1");
        }else{
            Fraction clone(f);
            clone.reduce();
            clone.symbolSimplification();
            if(clone.getDenominator()==1L){
                char buf[128];
                sprintf(buf,"%d",clone.getNumerator());
                return string(buf);
            }
            return (string)clone;
        }
    }

    static bool isZero(const Fraction& f){
        return f.isZero();
    }

    static Fraction reciprocal(const Fraction& f){
        return f.reciprocal();
    }

    static Fraction reciprocal_N(const Fraction& f){
        return f.reciprocal_N();
    }

    static bool isEqualD(const Fraction& f,const double& d){
        return FloatUtils::isEqualD(f,d);
    }

    static bool isEqualOne(const Fraction& f){
        if(isZero(f)){
            return false;
        }
        return (f.getNumerator()==f.getDenominator());
    }

    static Fraction abs(const Fraction& f){
        Fraction r;
        r.setNumerator(labs(f.getNumerator()));
        r.setDenominator(labs(f.getDenominator()));
        return r;
    }
};

#endif //_FRACTIONOUTPUTADAPTER_HPP
