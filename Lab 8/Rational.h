#ifndef RATIONAL_H
#define RATIONAL_H

namespace CS2124{
  // operator+(int a, int b){}
  class Rational{
  public:
    Rational(int numerator = 0, int denominator = 1);
    Rational& operator+=(const Rational& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
    friend std::istream& operator>>(std::istream& is, Rational& rhs);
    friend bool operator== ( Rational a,  Rational b);  
    explicit operator bool() const;
    Rational& operator++();
    Rational operator++(int _);
  private:
    void normalize();
    int numerator;
    int denominator;
  };
}
#endif