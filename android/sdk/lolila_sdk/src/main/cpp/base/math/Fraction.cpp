/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Daniel Dorndorf <dorndorf@featdd.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include "Fraction.h"
#include "../utils/AndroidLog.h"

static void _compare(const Fraction& f1, const Fraction& f2, long& a, long& b);

/***
 * Standard constructor
*/
Fraction::Fraction(void) {
    this->numerator = 0L;
    this->denominator = 0L;
}

/**
 * Double-convert constructor
*/
Fraction::Fraction(double Number) {
    this->convertDoubleToFraction(Number);
}

/**
 * String-convert constructor
*/
Fraction::Fraction(const std::string& FractionString) {
    this->convertStringToFraction(FractionString);

}

Fraction::Fraction(const Fraction& o):numerator(o.numerator),denominator(o.denominator){

}

Fraction::Fraction(long val):numerator(val),denominator(1L){

}

Fraction& Fraction::operator=(const Fraction& other){




    if(*this!=other){
        this->numerator=other.numerator;
        this->denominator=other.denominator;
    }
    return *this;
}

Fraction& Fraction::operator=(long val){
    this->numerator=val;
    this->denominator=1L;
    return *this;
}

Fraction& Fraction::operator=(double Number){
    this->convertDoubleToFraction(Number);
    return *this;
}

Fraction& Fraction::operator=(const string& val){
    this->convertStringToFraction(val);
    return *this;
}

/**
 * Standard deconstructor
*/
Fraction::~Fraction(void) {}

/**
 * Recursive euclidean function for
 * the greatest common divisor
 */
long Fraction::euclidean(long a, long b){
    return b == 0 ? a : this->euclidean(b, a % b);
}

/**
 * Getter for the numerator
*/
long Fraction::getNumerator(void)const {
    return this->numerator;
}

/**
 * Getter for the denominator
*/
long Fraction::getDenominator(void)const {
    return this->denominator;
}

/**
 * Setter for the numerator
*/
void Fraction::setNumerator(long Numerator) {
    this->numerator = Numerator;
}

/**
 * Setter for the denominator
*/
void Fraction::setDenominator(long Denominator) {
    this->denominator = Denominator;
}

/**
 * Reduce the fraction as low as possible
*/
bool Fraction::reduce(void) {
    bool r=false;

    long gcd(this->euclidean(this->numerator, this->denominator));

    if (1 < gcd || gcd<-1 /* gcd<-1 */) {
        this->numerator /= gcd;
        this->denominator /= gcd;
        r=true;
    } else {
        //LOGD("reduce false:%i,%i",this->numerator,this->denominator);
        r=false;
    }


    return r;
}

bool Fraction::symbolSimplification(){
    if( this->numerator <0L && this->denominator<0L){
        this->numerator = labs(this->numerator);
        this->denominator = labs(this->denominator);
        return true;
    }else if( this->numerator >0L && this->denominator<0L){
        this->numerator *= -1L;
        this->denominator = labs(this->denominator);
        return true;
    }
    return false;
}

/**
 * Convert function for double to fraction
 *
 * Count pre-decimal points, multiply the
 * double number with 10 to move the floating point
 * and also the denominator
*/
void Fraction::convertDoubleToFraction(double Number) {
    this->denominator = 1;

    while(((double)(int)Number) != Number) {
        Number = Number * 10;
        this->denominator = this->denominator * 10;
    }

    this->numerator = (long)Number;

    this->reduce();
}

/**
 * Convert function for fraction to double
*/
const double Fraction::convertFractionToDouble(void) const{
    return (double)this->numerator / (double)this->denominator;
}

/**
 * Convert function for string to fraction
 *
 * cut numerator and denominator out of string
*/
bool Fraction::convertStringToFraction(const std::string& FractionString) {
    std::size_t pos = FractionString.find("/");

    if (pos != std::string::npos) {
        try {
            this->numerator = atol(FractionString.substr(0, pos).c_str());
            this->denominator = atol(FractionString.substr(pos + 1).c_str());
        } catch(...) {
            return false;
        }

        //LOGD("convertStringToFraction 1 num:%i,den:%i",this->numerator,this->denominator);

        return (this->denominator == 0) ? false : true;
    }else{
        try {
            this->numerator = atol(FractionString.c_str());
            this->denominator = 1L;
        } catch(...) {
            return false;
        }
    }

    return false;
}

/**
 * Tested!!
 * Smaller than operator overloading
*/
bool Fraction::operator<(const Fraction& f)const {
    long a,b;
    _compare(*this,f,a,b);
    return a<b;
}

/**
 * Smaller than or equal operator overloading
*/
bool Fraction::operator<=(const Fraction& f)const {
    long a,b;
    _compare(*this,f,a,b);
    return a<=b;
}

/**
 * Bigger than operator overloading
*/
bool Fraction::operator>(const Fraction& f)const {
    long a,b;
    _compare(*this,f,a,b);
    return a>b;
}

/**
 * Bigger than or equal operator overloading
*/
bool Fraction::operator>=(const Fraction& f)const {
    long a,b;
    _compare(*this,f,a,b);
    return a>=b;
}

/**
 * Equal operator overloading
*/
bool Fraction::operator==(const Fraction& f)const {
    long a,b;
    _compare(*this,f,a,b);
    return a==b;
}

/**
 * Non-Equal operator overloading
*/
bool Fraction::operator!=(const Fraction& f) const{
    long a,b;
    _compare(*this,f,a,b);
    return a!=b;
}


/**
 * Modulos operator overloading (a/b % x/y = (a*y % b*x) / (b*y))
*/
long Fraction::operator%(Fraction fraction) {
    long result;

    result = ((this->numerator * fraction.getDenominator()) % (this->denominator * fraction.getNumerator())) / (this->denominator * fraction.getDenominator());

    return result;
}

/**
 * Double typecast operator overloading
*/
Fraction::operator double() const{
    return this->convertFractionToDouble();
}

/**
 * Float typecast operator overloading
*/
Fraction::operator float() const{
    return (float)this->convertFractionToDouble();
}

/**
 * Long typecast operator overloading
*/
Fraction::operator long()const {
    return (long)this->convertFractionToDouble();
}

/**
 * Std::string typecast operator overloading
*/
Fraction::operator std::string() const{
    std::stringstream output;
    output << this->getNumerator() << "/" << this->getDenominator();
    return output.str();
}



/**
 * Addition operator overloading
*/
Fraction Fraction::operator+(Fraction fraction) {
    Fraction resultFraction;

    if( fraction.isZero()){
        resultFraction.setNumerator(this->numerator);
        resultFraction.setDenominator(this->denominator);
    }else {
        if (this->denominator == fraction.getDenominator()) {
            resultFraction.setNumerator(this->numerator + fraction.getNumerator());
            resultFraction.setDenominator(this->denominator);
        } else {
            resultFraction.setNumerator((this->numerator * fraction.getDenominator()) +
                                        (fraction.getNumerator() * this->denominator));
            resultFraction.setDenominator(this->denominator * fraction.getDenominator());
        }
    }

    return resultFraction;
}

/**
 * Assignment by Sum operator overloading
*/
Fraction Fraction::operator+=(Fraction fraction) {
    if( fraction.isZero()){
        return *this;
    }

    if( this->isZero()){
        this->numerator = fraction.getNumerator();
        this->denominator = fraction.getDenominator();
    }else {

        if (this->denominator == fraction.getDenominator()) {
            this->numerator += fraction.getNumerator();
        } else {
            this->numerator = (this->numerator * fraction.getDenominator()) +
                              (fraction.getNumerator() * this->denominator);
            this->denominator *= fraction.getDenominator();
        }
    }

    return *this;
}

/**
 * Subtraction operator overloading
*/
Fraction Fraction::operator-(Fraction fraction) {
    Fraction resultFraction;

    if (this->denominator == fraction.getDenominator()) {
        resultFraction.setNumerator(this->numerator - fraction.getNumerator());
        resultFraction.setDenominator(this->denominator);
    } else {
        resultFraction.setNumerator((this->numerator * fraction.getDenominator()) - (fraction.getNumerator() * this->denominator));
        resultFraction.setDenominator(this->denominator * fraction.getDenominator());
    }

    return resultFraction;
}

/**
 * Assignment by difference operator overloading
*/
Fraction Fraction::operator-=(Fraction fraction) {
    if (this->denominator == fraction.getDenominator()) {
        this->numerator -= fraction.getNumerator();
    } else {
        this->numerator = (this->numerator * fraction.getDenominator()) - (fraction.getNumerator() * this->denominator);
        this->denominator *= fraction.getDenominator();
    }

    return *this;
}

/**
 * Multiply operator overloading
*/
Fraction Fraction::operator*(Fraction fraction) {
    Fraction resultFraction;

    resultFraction.setNumerator(this->numerator * fraction.getNumerator());
    resultFraction.setDenominator(this->denominator * fraction.getDenominator());

    return resultFraction;
}

/**
 * Multiply Set operator overloading
*/
Fraction Fraction::operator*=(Fraction fraction) {
    this->denominator *= fraction.getDenominator();
    this->numerator *= fraction.getNumerator();

    return *this;
}

/**
 * Division operator overloading
*/
Fraction Fraction::operator/(Fraction fraction) {
    Fraction resultFraction;

    resultFraction.setDenominator(this->denominator * fraction.getNumerator());
    resultFraction.setNumerator(this->numerator * fraction.getDenominator());

    return resultFraction;
}

/**
 * Division Set operator overloading
*/
Fraction Fraction::operator/=(Fraction fraction) {
    this->denominator *= fraction.getNumerator();
    this->numerator *= fraction.getDenominator();

    return *this;
}

/**
 * Complement operator overloading
*/
Fraction Fraction::operator~(void) {
    Fraction resultFraction;

    if(this->numerator > this->denominator) {
        return *this;
    } else {
        resultFraction.setNumerator(this->denominator - this->numerator);
        resultFraction.setDenominator(this->denominator);

        return resultFraction;
    }
}

/**
 * Increment operator overloading
*/
Fraction Fraction::operator++(void) {
    this->numerator += 1;

    return *this;
}

/**
 * Decrement operator overloading
*/
Fraction Fraction::operator--(void) {
    this->numerator -= 1;

    return *this;
}

/**
 * Left shift operator overloading
*/


std::stringstream& operator<<(std::stringstream &out, Fraction &f) {
    out << f.getNumerator() << "/" << f.getDenominator();
    return out;
}




/**
 * Right shift operator overloading
 *
 * Calls convertStringToFraction function and throws an
 * FractionInputFailException object on fail.
 *
 * (catchable as a std::exception)
*/

std::istream& operator>>(std::istream &in, Fraction &Fraction) {
    std::string input;

    in >> input;

    if (false == Fraction.convertStringToFraction(input)) {
        // Throw own exception object
        throw FractionInputFailException();
    }

    return in;
}





Fraction Fraction::reciprocal()const{
    if( this->numerator==0L || this->denominator==0L ){
        throw logic_error("can not reciprocal a zero");
    }

    Fraction r;
    r.setNumerator(this->denominator);
    r.setDenominator(this->numerator);
    return r;
}

Fraction Fraction::reciprocal_N()const{
    if( this->numerator==0L || this->denominator==0L ){
        throw logic_error("can not reciprocal a zero");
    }

    long num =  this->denominator;
    long de  =  this->numerator;

    if( this->numerator<0L  ){
        de *= -1L;
    }
    if( this->denominator<0L ){
        num *= -1L;
    }
    Fraction r;
    r.setNumerator(num);
    r.setDenominator(de);
    return r;
}

static long LCM(long a , long b){
    /*排序保证a始终小于b*/
    if(a > b){
        long t = a ; a = b ; b = t ;
    }
    /*先求出最大公约数*/
    long c = a ;
    long d = b ;
    long gcd = 0 ;
    while(c%d != 0){
        //k保存余数
        long k = c%d ;
        //除数变为c
        c = d ;
        //被除数变为余数
        d = k ;
    }
    /*辗转相除结束后的c即为所求的最大公约数*/
    gcd = d ;

    /*使用公式算出最小公倍数*/
    long lcm = a*b/gcd ;

    return lcm ;
}

static void _compare(const Fraction& f1, const Fraction& f2, long& a, long& b){
    a=0L;
    b=0L;
    Fraction _f1(f1);
    Fraction _f2(f2);
    _f1.symbolSimplification();
    //_f1.reduce();
    _f2.symbolSimplification();
    //_f2.reduce();

    if( _f1.isZero() && _f2.isZero()){
        a=b=0L;
        return;
    }else if( _f1.isZero() && _f2.isPositive()){
        a=0L;
        b=1L;
        return;
    }else if( _f1.isZero() && _f2.isNegative()){
        a=0L;
        b=-1L;
        return;
    }else if( _f1.isNegative() && _f2.isZero() ){
        a=-1L;
        b=0L;
        return;
    }else if( _f1.isPositive() && _f2.isZero() ){
        a=1L;
        b=0L;
        return;
    }else if( _f1.isPositive() && _f2.isNegative() ){
        a=1L;
        b=-1L;
        return;
    }else if( _f1.isNegative() && _f2.isPositive() ){
        a=-1L;
        b=1L;
        return;
    }


    long lcm = LCM( _f1.getDenominator(),_f2.getDenominator());
    long t1 = lcm/_f1.getDenominator();
    a =  labs( _f1.getNumerator()*t1 );
    long t2 = lcm/_f2.getDenominator();
    b =  labs( _f2.getNumerator()*t2 );

}