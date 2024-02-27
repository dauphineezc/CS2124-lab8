// Zoe Dauphinee, rec 08, operator overloading with rational numbers

#include <iostream>
using namespace std;


class Rational {
    public:
        void normalize();
        Rational(int numerator = 0, int denominator = 1);
        Rational& operator+=(const Rational& other_num);
        Rational& operator++();
        Rational operator++(int);
        explicit operator bool();
    private:
        int numerator;
        int denominator;

    friend ostream& operator<<(ostream& os, const Rational& num);
    friend istream& operator>>(istream& is, Rational& num);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
};


Rational operator+(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& num);
Rational operator--(Rational& num, int);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
int greatestCommonDivisor(int x, int y);


int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}


/*
methods
*/
// constructor
Rational::Rational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    this->normalize();
}

// += operator
Rational& Rational::operator+=(const Rational& other_num) {
    numerator = ((numerator*other_num.denominator) + (other_num.numerator*denominator));
    denominator = (denominator*other_num.denominator);
    this->normalize();
    return *this;
}

// ++ operator (pre)
Rational& Rational::operator++() {
    *this += 1;
    return *this;
}
    
// ++ operator (post)
Rational Rational::operator++(int) {
    Rational temp(*this);
    *this += 1;
    return temp;
}

// returns false if numerator = 0, true otherwise
Rational::operator bool() {
    if (numerator == 0) {
        return false;
    }
    return true;
}


/*
friend functions
*/

// output operator
ostream& operator<<(ostream& os, const Rational& num) {
    os << num.numerator << "/" << num.denominator;
    return os;
}

// input operator
istream& operator>>(istream& is, Rational& num) {
    char slash;
    is >> num.numerator >> slash >> num.denominator;
    num.normalize();
    return is;
}

// == operator
bool operator==(const Rational& lhs, const Rational& rhs) {
    if ((lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator)) {
        return true;
    }
    return false;
}

// < operator
bool operator<(const Rational& lhs, const Rational& rhs) {
    if (lhs.denominator > 0 && rhs.denominator > 0) {
        if ((lhs.numerator * rhs.denominator) < (rhs.numerator * lhs.denominator)) {
            return true;
        }
    }
    return false;
}

// fixes negatives and simplifies rational number
void Rational::normalize() {
    int new_denom = greatestCommonDivisor(numerator, denominator);
    denominator = denominator/new_denom;
    numerator = numerator/new_denom;
    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }
}


/*
non-friend functions
*/

// + operator
Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational sum = lhs;
    sum += rhs;
    sum.normalize();
    return sum;
}

// -- operator (pre)
Rational& operator--(Rational& num) {
    num += -1;
    return num;
}

// -- operator (post)
Rational operator--(Rational& num, int) {
    Rational temp(num);
    num += -1;
    return temp;
}

// != operator
bool operator!=(const Rational& lhs, const Rational& rhs) {
    if (lhs == rhs) {
        return false;
    }
    return true;
}

// <= operator
bool operator<=(const Rational& lhs, const Rational& rhs) {
    if ((lhs < rhs) || (lhs == rhs)) {
        return true;
    }
    return false;
}

// > operator
bool operator>(const Rational& lhs, const Rational& rhs) {
    if (!(lhs <= rhs)) {
        return true;
    }
    return false;
}

// >= operator
bool operator>=(const Rational& lhs, const Rational& rhs) {
    if ((lhs > rhs) || (lhs == rhs)) {
        return true;
    }
    return false;
}

// finds greatest common divisor, used to normalize rational number
int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}