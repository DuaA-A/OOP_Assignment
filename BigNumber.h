#ifndef UNTITLED11_BIGNUMBER_H
#define UNTITLED11_BIGNUMBER_H
#include <iostream>
#include <deque>
#include <regex>

using namespace std;

class BigDecimalInt{
private:
    string number;        // The string representation of the BigDecimalInt.
    char signNumber;      // The sign of the BigDecimalInt ('+' or '-').
    bool checkValidInput(string input); // Helper function to check the validity of input.

public:
    bool operator < (const BigDecimalInt& anotherDec); // Less than operator overloading.
    bool operator > (const BigDecimalInt& anotherDec); // Greater than operator overloading.
    bool operator == (const BigDecimalInt anotherDec); // Equal to operator overloading.
    BigDecimalInt& operator = (BigDecimalInt anotherDec); // Assignment operator overloading.
    BigDecimalInt operator + (BigDecimalInt number2); // Addition operator overloading.
    BigDecimalInt operator - (BigDecimalInt anotherDec); // Subtraction operator overloading.
    friend ostream &operator << (ostream &out, BigDecimalInt num); // Output stream operator overloading.
    int size(); // Get the size (number of digits) of the BigDecimalInt.
    int sign(); // Get the sign of the BigDecimalInt.
    void setNumber(string num); // Set the value of the BigDecimalInt.
    string getNumber(){
        return number; // Get the string representation of the BigDecimalInt.
    }

    BigDecimalInt(){} // Default constructor.
    BigDecimalInt(string num)
    {
        setNumber(num); // Constructor that sets the value of the BigDecimalInt.
    }

};

class BigReal:BigDecimalInt {
private:
    string *Total; // Pointer to the total value string.
    string *fractional_part; // Pointer to the fractional part of the number.
    string *integer_part; // Pointer to the integer part of the number.
    int *R_sign; // Pointer to the sign of the BigReal number.

    bool isValidReal(); // Helper function to check the validity of the BigReal number.
    BigReal addition(BigReal& first, BigReal& second); // Helper function for addition.
    BigReal subtraction(BigReal &first, BigReal &second); // Helper function for subtraction.

public:
    BigReal (string BR = "0.0"); // Default constructor that accepts a string.
    BigReal (double BR); // Constructor that accepts a double.
    BigReal (BigDecimalInt& bigInteger); // Constructor that accepts a BigDecimalInt.
    BigReal (const BigReal& other); // Copy constructor.
    BigReal (BigReal&& other); // Move constructor.
    BigReal& operator= (BigReal& other); // Assignment operator.
    BigReal& operator= (BigReal&& other); // Move assignment.
    ~BigReal(); // Destructor.

    BigReal operator+ (BigReal& other); // Addition operator overloading.
    BigReal operator- (BigReal& other); // Subtraction operator overloading.

    bool operator< (BigReal& anotherReal); // Less than operator overloading.
    bool operator> (BigReal& anotherReal); // Greater than operator overloading.
    bool operator== (BigReal anotherReal); // Equal to operator overloading.

    int size(); // Get the size of the BigReal.
    int sign(); // Get the sign of the BigReal.

    friend ostream& operator << (ostream& out, BigReal& num); // Output stream operator overloading.
    friend istream& operator >> (istream& out, BigReal& num); // Input stream operator overloading.
};


#endif //UNTITLED11_BIGNUMBER_H
