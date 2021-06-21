//  file poly.h
//  Class Poly, member funtion definitions

// Danny Banko, CSS 343
// date created: 08/06/2020
// date last modified: 08/11/2020
#ifndef poly_hpp
#define poly_hpp

#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Poly class:
//  -- Poly Class is a class used to internally represent polynomials as an
//     array. The array elements consist of coefficients for the coresponding
//     subscript which represents the exponent power. Memory is dynamically
//     allocated for the initial size of the Poly object. The Poly class
//     consists of arithmetic operators +, -, *, and their correspoonding
//     assignment operators (+=, -=, *=) to solve arithmetic between multiple
//     Poly objects. Poly class can set coefficients and exponents using
//     setCoeff, or it can accept user input.
//  Implementation and assumptions:
//  -- One array stores one polynomial
//  -- There can be at most 2 values (int coeff, int exponent) when
//     creating Poly object
//  -- If Poly is created with negative exponent, exponent will be changed
//     to 0
//  -- Coefficients can be changed using a setter function
//  -- Exponent values have to be >= 0
//  -- Assume correct data (ints)
//  -- Array will resize if larger exponents are introcuded to a polynomial
//  -- Array size will only get larger if needed, not smaller
//---------------------------------------------------------------------------

class Poly {
    friend ostream& operator<<(ostream &, const Poly &);     //output
    friend istream& operator>>(istream &, Poly &);           //input
    
public:
    Poly(int = 0, int = 0);     // constructor (uses default values)
    ~Poly();                    // destructor
    Poly(const Poly &);         // copy constructor
    
    Poly& operator=(const Poly &);       // assignment operator
    
    Poly operator+(const Poly &) const;  // addition of 2 polynomials
    Poly operator-(const Poly &) const;  // subtraction of 2 polynomials
    Poly operator*(const Poly &) const;  // multiplication of 2 polynomials

    Poly operator+=(const Poly &);       // addition assignment
    Poly operator-=(const Poly &);       // subtraction assignment
    Poly operator*=(const Poly &);       // multiplication assignment
    
    bool operator==(const Poly &) const; // polynomial == comparison
    bool operator!=(const Poly &) const; // polynomial != comparison
    
    int getCoeff(int) const;    // setter
    void setCoeff(int, int);    // getter
    
private:
    // data
    int highestExp;             // sizes the array
    int* coeffArray;            // array of coefficients
    // functions
    void copy(const Poly &);    // copy used in copy const/operator =
};

#endif
