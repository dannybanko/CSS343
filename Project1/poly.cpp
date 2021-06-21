// file poly.cpp
// Poly class implementations of member functions

// Danny Banko, CSS 343
// date created: 08/06/2020
// date last modified: 08/11/2020
#include "poly.hpp"

//---------------------------------------------------------------------------
// constructor
// uses default values to allow the use on one single constructor
// default value is 0
Poly::Poly(int coefficient, int exponent) {
    // check to make sure that the exponent is >= 0 (valid exponent)
    if (exponent >= 0) {
        highestExp = exponent;
    } else {  // when parameter exponent is < 0
        highestExp = 0;
    }
    
    coeffArray = new int[highestExp + 1];    // sizes the array
    coeffArray[highestExp] = coefficient;    // sets the coefficient
    
    // sets the remaining exponent values to coefficient value 0
    for (int i = 0; i < highestExp; i++) {
        coeffArray[i] = 0;
    }
}

//---------------------------------------------------------------------------
// destructor
// deletes the array pointer and destructs Poly object
Poly::~Poly() {
    delete [] coeffArray;
    coeffArray = nullptr;
}

//---------------------------------------------------------------------------
// copy constructor
// Copies Poly objects using private funtion copy
Poly::Poly(const Poly &other) {
    copy(other);     // uses private funtion copy below
}

//---------------------------------------------------------------------------
// copy
// called in the copy constructor and operator= which does the actual
// copying of the int array in the Poly object, allocates memory and and
// copys contents of parameter Poly object
void Poly::copy(const Poly &toCopy) {
    
    highestExp = toCopy.highestExp;
    coeffArray = new int[highestExp + 1];
    
    // copies contents from parameter Poly object
    for (int i = 0; i <= highestExp; i++) {
        coeffArray[i] = toCopy.coeffArray[i];
    }
}

//---------------------------------------------------------------------------
// operator=
// assignment operator for Poly object, calls copy to make a deep copy of
// parameter object
Poly& Poly::operator=(const Poly& copyFrom) {
    
    // checks to see if they are the same object
    if (&copyFrom != this) {
        delete [] coeffArray;
        copy(copyFrom);
    }
    return *this;
}

//---------------------------------------------------------------------------
// operator+
// addition operator for two Poly objects, adds contents of each array in
// relation to their exponent value
Poly Poly::operator+(const Poly &add) const {

    // finds the correct size for new array.
    int size;
    if (this->highestExp > add.highestExp) {
        size = this->highestExp;
    } else {
        size = add.highestExp;
    }
    
    // creates new poly to desired size, all coeffs are 0 to start
    Poly addition(0, size);
    
    // loops through new sized array
    for (int i = 0; i <= size; i++) {
        if (i <= this->highestExp) {  // adds current objects contents
            addition.coeffArray[i] = this->coeffArray[i];
        }
        if (i <= add.highestExp) {    // adds param objects contents
            addition.coeffArray[i] += add.coeffArray[i];
        }
    }
    return addition;
}

//---------------------------------------------------------------------------
// operator-
// subtraction  operator for two Poly objects, subtracts contents of each
// array in relation to their exponent value
Poly Poly::operator-(const Poly &sub) const {
    
    // finds the correct size for new array.
    int size;
    if (this->highestExp > sub.highestExp) {
        size = this->highestExp;
    } else {
        size = sub.highestExp;
    }
    
    // creates new poly to desired size, all coeffs are 0 to start
    Poly subtraction(0, size);
    
    // walks through new sized array
    for (int i = 0; i <= size; i++) {
        if (i <= this->highestExp) {  // subtracrs current objects contents
            subtraction.coeffArray[i] = this->coeffArray[i];
        }
        if (i <= sub.highestExp) {    // subtracts param objects contents
            subtraction.coeffArray[i] -= sub.coeffArray[i];
        }
    }
    return subtraction;
}

//---------------------------------------------------------------------------
// operator*
// multiplication operator for two Poly objects, multiplies contents of each
// array in relation to their exponent value
Poly Poly::operator*(const Poly & mult) const {
    
    // find the highest index (exponent) by taking the largest expont value
    // from both poly objects and adding them together
    int productSize = this->highestExp + mult.highestExp;
    
    // new Poly object with correct size, all coeffs are set to 0
    Poly multiply(0, productSize);
    
    // loops through all coeffs of current object
    for (int i = this->highestExp; i >= 0; i--) {
        // loops through all coeffs of parameter object
        for (int j = mult.highestExp; j >= 0; j--) {
            multiply.coeffArray[i + j] += this->coeffArray[i] * mult.coeffArray[j];
        }
    }
    return multiply;
}

//---------------------------------------------------------------------------
// operator+=
// adds and assigns param Poly object to current Poly
Poly Poly::operator+=(const Poly &other) {
    return *this = *this + other;
}

//---------------------------------------------------------------------------
// operator-=
// subtracts and assigns param Poly to current Poly
Poly Poly::operator-=(const Poly &other) {
    return *this = *this - other;
}

//---------------------------------------------------------------------------
// operator*=
// multiplies and assigns param Poly to current Poly
Poly Poly::operator*=(const Poly &other) {
    return *this = *this * other;
}

//---------------------------------------------------------------------------
// operator==
// equivelant operator, checks to see if the contents of two Poly objects
// are the same
bool Poly::operator==(const Poly &other) const {

    // polys can still be == if the sizes are different (data with 0 coeffs)
    // find the smallest size, to check those values first
    if (this->highestExp < other.highestExp) {
        for (int i = 0; i <= this->highestExp; i++) {
            if (this->coeffArray[i] != other.coeffArray[i]) {
                return false;
            }
        }
    } else { // covers if the sizes of arrays are == as well as other<this
        for (int i = 0; i <= other.highestExp; i++) {
            if (this->coeffArray[i] != other.coeffArray[i]) {
                return false;
            }
        }
    }
    
    // if shared exponent indecies are ==, check the larger array
    // for coefficients greater/less than 0, if one exists, polys are not ==
    if (this->highestExp > other.highestExp) {        // current > param
        for (int i = other.highestExp; i <= this->highestExp; i++) {
            if (this->coeffArray[i] > 0 || this->coeffArray[i] < 0) {
                return false;
            }
        }
    } else if (other.highestExp > this->highestExp) { // param > current
        for (int i = this->highestExp; i <= other.highestExp; i++) {
            if (other.coeffArray[i] > 0 || other.coeffArray[i] < 0) {
                return false;
            }
         }
    }
    return true;
}

//---------------------------------------------------------------------------
// operator!=
// non-equivelant operator, checks to see if current Poly and param Poly are
// not equivelant
bool Poly::operator!=(const Poly &other) const {
    return !(*this == other);
}

//---------------------------------------------------------------------------
// setCoeff
// sets coeffcient value given and exponent value. If exponent it > current
// size, the array will be resized
void Poly::setCoeff(int coefficient, int exponent) {
    
    if (exponent < 0) {  // invalid exponent (don't do anthing)
        return;
    } else if (exponent <= this->highestExp) {  // exponent is <= highestExp
        this->coeffArray[exponent] = coefficient;
    } else {             // exponent is > highestExp
        // create temp array to new size
        int * tempArray;
        tempArray = new int[exponent + 1];
        tempArray[exponent] = coefficient;
        
        // copies current Poly contents to tempArray
        for (int i = 0; i <= this->highestExp; i++) {
            tempArray[i] = this->coeffArray[i];
        }
        // sets remaining coeff values to 0 (exponents > current size)
        for (int i = this->highestExp + 1; i < exponent; i++) {
            tempArray[i] = 0;
        }
        
        // sets highest exponent to the new exponent value
        this->highestExp = exponent;

        // clean up
        delete [] this->coeffArray;
        this->coeffArray = tempArray;
        tempArray = nullptr;
    }
}

//---------------------------------------------------------------------------
// getCoeff
// resturns the coefficient value of a given exponent, if exponent doesn't
// exist, getCoeff will return 0
int Poly::getCoeff(int index) const {
    // checks to make sure exponent exists in current Poly object
    if (this->highestExp >= index && index >= 0) {
        return this->coeffArray[index];
    } else {
        return 0;
    }
}

//---------------------------------------------------------------------------
// operator<<
// outpur operator, displays the Poly object
ostream& operator<<(ostream &output, const Poly &a) {
    
    // keeps track if any coeff is 0
    bool allZeros = true;
    // walks from highsest expoent to 0 exponent
    for (int i = a.highestExp; i >= 0; i--) {
        if (i == 0) { // dont print x or exponent
            if(a.coeffArray[i] > 0) {
                allZeros = false;
                output << " +" << a.coeffArray[i];
            } else if (a.coeffArray[i] < 0) {
                allZeros = false;
                output << " " << a.coeffArray[i];
            }
        } else if (i == 1) { // dont print exponent
            if(a.coeffArray[i] > 0) {
                allZeros = false;
                output << " +" << a.coeffArray[i] << "x";
            } else if (a.coeffArray[i] < 0) {
                allZeros = false;
                output << " " << a.coeffArray[i] << "x";
            }
        } else { // print x and exponent
            if(a.coeffArray[i] > 0) {
                allZeros = false;
                output << " +" << a.coeffArray[i] << "x^" << i;
            } else if (a.coeffArray[i] < 0) {
                allZeros = false;
                output << " " << a.coeffArray[i] << "x^" << i;
            }
        }
    }
    if (allZeros) {
        output << "0";
    }
    return output;
}

//---------------------------------------------------------------------------
// operator>>
// input operator, allows user to type in exponent and coeff values
// terminates on -1 -1
istream& operator>>(istream &input, Poly &b) {
    int temp, temp2;
    // infinite loop until -1 -1 is entered 
    while(true) {
        input >> temp;
        input >> temp2;
        if(temp == -1 && temp2 == -1) {
            break;
        }
        b.setCoeff(temp, temp2);
    }
    return input;
}
