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

#ifndef __FRACTION_H__
#define __FRACTION_H__

using namespace std;

/**
 * Fraction class
 */
class Fraction {
private:
    // Fraction parts
    long numerator, denominator;
    // Euclidean algorithm for greatest common divisor
    long euclidean(long a, long b);
public:
    // Constructors
    Fraction(void);
    Fraction(long);
    Fraction(double Number);
    Fraction(const std::string& FractionString);
    Fraction(const Fraction&);
    // Destructur
    ~Fraction(void);

    // Getter and Setter
    long getNumerator(void)const;
    long getDenominator(void)const;
    void setNumerator(long Numerator);
    void setDenominator(long Denominator);

    // Fraction functions
    bool reduce(void);
    void convertDoubleToFraction(double Number);
    const double convertFractionToDouble(void)const;
    bool convertStringToFraction(const std::string& FractionString);

    // Operator overloading functions

    // tested
    bool operator<(const Fraction& fraction)const;
    // tested
    bool operator<=(const Fraction& fraction)const;

    bool operator>(const Fraction& fraction)const;

    bool operator>=(const Fraction& fraction)const;

    bool operator==(const Fraction& fraction)const;

    bool operator!=(const Fraction& fraction)const;

    long operator%(Fraction fraction);

    operator double()const;
    operator float()const;
    operator long()const;


    operator std::string()const;


    Fraction operator+(Fraction fraction);
    Fraction operator+=(Fraction fraction);
    Fraction operator-=(Fraction fraction);
    Fraction operator-(Fraction fraction);
    Fraction operator*(Fraction fraction);
    Fraction operator*=(Fraction fraction);
    Fraction operator/(Fraction fraction);
    Fraction operator/=(Fraction fraction);
    Fraction operator~(void);
    Fraction operator++(void);
    Fraction operator--(void);

public:
    Fraction& operator=(const Fraction&);
    Fraction& operator=(long);
    Fraction& operator=(double);
    Fraction& operator=(const string&);

public:



    inline bool  isZero()const{
        return  numerator==0L || denominator==0L;
    }

    inline bool isNegative()const{
        if(isZero()){
            return false;
        }
        return ( numerator<0L && denominator>0L ) || ( numerator >0L && denominator<0L );
    }

    inline bool isPositive()const{
        if(isZero()){
            return false;
        }
        return ( numerator>0L && denominator>0L ) || ( numerator <0L && denominator<0L );
    }

    /**
     * 求倒数
     * @return
     */
    Fraction reciprocal()const;

    /**
     * 求倒数，且符号取反
     * @return
     */
    Fraction reciprocal_N()const;

    /**
     * 化简符号
     * @return
     */
    bool symbolSimplification();
};

/**
 * FractionInputFailException class
 *
 * Exception object extending the c++ standard exceptions
 * Thrown exception can be handled like standard exceptions
*/
class FractionInputFailException: public std::exception {
public: virtual const char* what() const throw() { return "Incorrect Input"; }
};

/** Left Shift Operator overloading functions (need to be declared global) */
std::ostream& operator<<(std::ostream &out, Fraction &Fraction);
/** Right Shift Operator overloading functions (need to be declared global) */
std::istream& operator>>(std::istream &in, Fraction &Fraction);



#endif //__FRACTION_H__

