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
Fraction::Fraction(std::string FractionString) {
    this->convertStringToFraction(FractionString);
}

Fraction::Fraction(const Fraction& o):numerator(o.numerator),denominator(o.denominator){

}

Fraction::Fraction(long val):numerator(val),denominator(1){

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
    this->denominator=1;
    return *this;
}

Fraction& Fraction::operator=(double Number){
    this->convertDoubleToFraction(Number);
    return *this;
}

Fraction& Fraction::operator=(string val){
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
    long gcd(this->euclidean(this->numerator, this->denominator));

    if (1 < gcd || gcd<-1 /* */) {
        this->numerator /= gcd;
        this->denominator /= gcd;

        return true;
    } else {
        //LOGD("reduce false:%i,%i",this->numerator,this->denominator);
        return false;
    }
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
bool Fraction::convertStringToFraction(std::string FractionString) {
    std::size_t pos = FractionString.find("/");

    if (pos != std::string::npos) {
        try {
            this->numerator = atol(FractionString.substr(0, pos).c_str());
            this->denominator = atol(FractionString.substr(pos + 1).c_str());
        } catch(...) {
            return false;
        }

        return (this->denominator == 0) ? false : true;
    }

    return false;
}

/**
 * Smaller than operator overloading
*/
bool Fraction::operator<(Fraction fraction) {
    return (this->numerator * (this->denominator * fraction.getDenominator())) < (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
}

/**
 * Smaller than or equal operator overloading
*/
bool Fraction::operator<=(Fraction fraction) {
    return (this->numerator * (this->denominator * fraction.getDenominator())) <= (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
}

/**
 * Bigger than operator overloading
*/
bool Fraction::operator>(Fraction fraction) {
    return (this->numerator * (this->denominator * fraction.getDenominator())) > (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
}

/**
 * Bigger than or equal operator overloading
*/
bool Fraction::operator>=(Fraction fraction) {
    return (this->numerator * (this->denominator * fraction.getDenominator())) >= (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
}

/**
 * Equal operator overloading
*/
bool Fraction::operator==(const Fraction& fraction)const {
    return (this->numerator * (this->denominator * fraction.getDenominator())) == (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
}

/**
 * Non-Equal operator overloading
*/
/*
bool Fraction::operator!=(Fraction fraction) {
    return (this->numerator * (this->denominator * fraction.getDenominator())) != (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));
}
*/

bool Fraction::operator!=(const Fraction& fraction) const{


    if( this->isZero() && !fraction.isZero() ){
        return true;
    }
    if( !this->isZero() && fraction.isZero() ){
        return true;
    }

    // if one of them is zero , can not apply this camp way
    return  (this->numerator * (this->denominator * fraction.getDenominator())) != (fraction.getNumerator() * (this->denominator * fraction.getDenominator()));

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
Fraction::operator float() {
    return (float)this->convertFractionToDouble();
}

/**
 * Long typecast operator overloading
*/
Fraction::operator long() {
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

    if (this->denominator == fraction.getDenominator()) {
        resultFraction.setNumerator(this->numerator + fraction.getNumerator());
        resultFraction.setDenominator(this->denominator);
    } else {
        resultFraction.setNumerator((this->numerator * fraction.getDenominator()) + (fraction.getNumerator() * this->denominator));
        resultFraction.setDenominator(this->denominator * fraction.getDenominator());
    }

    return resultFraction;
}

/**
 * Assignment by Sum operator overloading
*/
Fraction Fraction::operator+=(Fraction fraction) {
    if (this->denominator == fraction.getDenominator()) {
        this->numerator += fraction.getNumerator();
    } else {
        this->numerator = (this->numerator * fraction.getDenominator()) + (fraction.getNumerator() * this->denominator);
        this->denominator *= fraction.getDenominator();
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



const char* Fraction::c_str() const{

    return ((string)*this).c_str();
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