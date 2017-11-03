#include <string>
#include <iostream>
#include "gcd.cpp"
#include "Rational.h"
using namespace std;

namespace CS2124{
  ostream& operator<<(ostream& os, const Rational& rhs){
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
  }
  istream& operator>>(istream& is, Rational& rhs){
    char slash;
    is >>  rhs.numerator >> slash >> rhs.denominator;
    return is;
  }
  bool operator==( Rational a,  Rational b){
    if(a.numerator == b.numerator && a.denominator == b.denominator){
      return true;
    }
    return false;
  }

  Rational::Rational(int numerator, int denominator):numerator(numerator), denominator(denominator){ normalize();};
  Rational& Rational::operator+=(const Rational& rhs){
    numerator *= rhs.denominator;
    numerator +=  rhs.numerator * denominator;
    denominator *= rhs.denominator;
    normalize();
    return *this;
  }
  Rational& Rational::operator++(){
    numerator += denominator;
    return *this;
  };
  Rational Rational::operator++(int _){
    Rational temp(*this);
    numerator += denominator;
    return temp;
  };
  void Rational::normalize(){
    if (denominator < 0){
      numerator *= -1;
      denominator *= -1;
    }
    
    int absNum = numerator;
    if (numerator < 0){
      absNum *= -1;
    }

    int gcf = greatestCommonDivisor(absNum, denominator);
    numerator /= gcf;
    denominator /= gcf;
  }
  Rational::operator bool() const{
    return numerator;
  };
}
