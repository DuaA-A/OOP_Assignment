#include "BigNumber.h"

// regex function that checks the validation of the input.
bool BigDecimalInt :: checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void BigDecimalInt :: setNumber(string num)
{
    bool validNumber = checkValidInput(num);
    if(validNumber)
    {
        number = num;
        if(number[0] == '+')
        {
            number.erase(0,1);
            signNumber = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            signNumber = '-';
        }
        else
        {
            signNumber = '+';
        }
    }
    else
    {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

// operator < overloading function.
bool BigDecimalInt :: operator < (const BigDecimalInt& anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(signNumber == '-' && anotherDec.signNumber == '+')
    {
        return true;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '-')
    {
        return false;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '+')
    {
        return comp1 < comp2;
    }
    else
    {
        return comp1 > comp2;
    }
}

// operator > overloading function.
bool BigDecimalInt :: operator > (const BigDecimalInt &anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(signNumber == '-' && anotherDec.signNumber == '+')
    {
        return false;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '-')
    {
        return true;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '+')
    {
        return comp1 > comp2;
    }
    else
    {
        return comp1 < comp2;
    }
}

// operator == overloading function.
bool BigDecimalInt :: operator == (const BigDecimalInt anotherDec)
{
    if (signNumber == anotherDec.signNumber && number == anotherDec.number)
    {
        return true;

    }
    else
    {
        return false;
    }
}

// operator = overloading function.
BigDecimalInt& BigDecimalInt :: operator = (BigDecimalInt anotherDec)
{
    signNumber = anotherDec.signNumber;
    number = anotherDec.number;
    return *this;
}

//addition implementation.
string addition(string num1,string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    int carry = 0;
    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry)
    {
        res = char((carry) + '0') + res;
    }
    return res;
}

//subtraction implementation
string subtraction(string num1,string num2){
    deque<long long>d;
    string res;

    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if (num1[i] < num2[i])
        {
            num1[i] = char (((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char (((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
        else
        {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i : d)
    {
        res += to_string(i);
    }
    return res;
}

// // operator + overloading function.
BigDecimalInt BigDecimalInt :: operator + (BigDecimalInt number2)
{
    BigDecimalInt result;
    char signNumber1 = signNumber, signNumber2 = number2.signNumber;
    string num1 = number, num2 = number2.number;
    BigDecimalInt number1 = *this;

    while (num1.length() < num2.length()){
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()){
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2){
        result.signNumber = signNumber1;
        result.number = addition(num1,num2);

    }else{

        if(number1.signNumber == '-')
        {
            number1.signNumber = '+';
            result = (number2 - number1);
        }
        else{
            number2.signNumber = '+';
            result = (number1 - number2);
        }
    }
    return result;
}

// operator - overloading function.
BigDecimalInt BigDecimalInt :: operator - (BigDecimalInt anotherDec)
{
    BigDecimalInt obj;
    deque<long long> d;
    string strmin = "", res = "";
    string num1 = number, num2 = anotherDec.number;
    char sign1 = signNumber, sign2 = anotherDec.signNumber;

    if (number.length() > anotherDec.number.length())
    {
        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++)
        {
            strmin += '0';
        }
        strmin += anotherDec.number;
        num2 = strmin;
    }
    else if (number.length() < anotherDec.number.length())
    {
        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++)
        {
            strmin += '0';
        }
        strmin += number;
        num1 = strmin;
    }

    bool neg = false, is_determined = false;
    if (num1 < num2)
    {
        swap(num1, num2);
        swap(sign1, sign2);
        neg = true;
    }

    if (sign1 == sign2 )
    {
        res = subtraction(num1,num2);

        if(sign1=='-')neg = !neg;
    }
    else
    {
        res = addition(num1,num2);
        if(signNumber == '-')
        {
            obj.signNumber = '-';
            is_determined = true;
        }
        else
        {
            obj.signNumber = '+';
            is_determined = true;
        }

    }

    bool right = false;
    for (long long i = 0; i < res.length(); i++)
    {
        if (res[i] != '-' && res[i] != '0')
        {
            right = true;
        }
        if (!right && res[i] == '0')
        {
            res.erase(i, 1);
            i--;
        }
    }

    if(res.empty()) res = "0";
    if (!is_determined && (neg))
    {
        obj.signNumber = '-';
    }
    else if(!is_determined)
    {
        obj.signNumber = '+';
    }

    obj.number = res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt :: size()
{
    return number.size();
}

// function returns the sign.
int BigDecimalInt :: sign()
{
    if (signNumber == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// operator << overloading function.
ostream &operator << (ostream &out, BigDecimalInt num)
{
    if(num.signNumber == '+')
    {
        out << num.number ;
    }
    else
    {
        if(num.number == "0")
        {
            out << num.number ;
        }
        else
        {
            out << num.signNumber << num.number ;
        }
    }
    return out;
}

BigReal::BigReal(string BR )
{
    Total = new string{BR};

    if(!isValidReal())
    {
        cout << "this is invalid Real number"<<endl;
    }
    else
    {

        if(BR[0] == '-')
        {
            R_sign = new int {-1};
        }
        else R_sign = new int {1};


        string intprt,frcprt;
        int i = 0;
        while(BR[i] != '.' && i != BR.size())
        {
            intprt += BR[i];
            i++;
        }
        i++;
        for (int j = i; j < BR.size(); ++j) {
            frcprt += BR[j];
        }
        fractional_part = new string{frcprt};

        integer_part = new string{intprt};


    }

}

BigReal::BigReal(double BR)
{
    string tmp = to_string(BR);
    Total = new string (tmp);
    if(tmp[0] == '-')
    {
        R_sign = new int {-1};
    }
    else R_sign = new int {1};

    string intprt,frcprt;
    int i = 0;
    while(tmp[i] != '.')
    {
        intprt += tmp[i];
        i++;
    }
    i++;
    for (int j = i; j < tmp.size(); ++j) {
        frcprt += tmp[j];
    }
    fractional_part = new string{frcprt};
    integer_part = new string{intprt};

}

bool BigReal::isValidReal()
{
    regex CH("[-+]?[0-9]+[.]?[0-9]+");
    return regex_match(*Total,CH);
}

BigReal::BigReal (BigDecimalInt& bigInteger)
{

    R_sign = new int {bigInteger.sign()};
    integer_part = new string (bigInteger.getNumber());
    fractional_part = new string("0");
    Total = new string (bigInteger.getNumber() + '.' + *fractional_part);

};
BigReal::~BigReal()
{
    delete R_sign;
    delete fractional_part;
    delete integer_part;
    delete Total;
}
BigReal::BigReal(const BigReal &other)
{
    R_sign = new int {*other.R_sign};
    integer_part = new string(*other.integer_part);
    fractional_part = new string (*other.fractional_part);
    Total = new string (*other.Total);

}

BigReal::BigReal(BigReal&& other)
{
    integer_part = other.integer_part;
    fractional_part = other.fractional_part;
    Total = other.Total;
    R_sign = other.R_sign;

    other.Total = nullptr;
    other.fractional_part = nullptr;
    other.integer_part = nullptr;
    other.R_sign = nullptr;

};

BigReal& BigReal::operator=(BigReal &other)
{
    integer_part = new string(*other.integer_part);
    fractional_part = new string (*other.fractional_part);
    Total = new string (*other.Total);
    R_sign = new int (*other.R_sign);
    return *this;


}

BigReal &BigReal::operator=(BigReal &&other)
{


    integer_part = other.integer_part;
    fractional_part = other.fractional_part;
    Total = other.Total;
    R_sign = other.R_sign;

    other.Total = nullptr;
    other.fractional_part = nullptr;
    other.integer_part = nullptr;
    other.R_sign = nullptr;
    return *this;
    cout<<"move assignment"<<endl;
}

bool BigReal::operator < (BigReal& anotherReal)
{

    BigDecimalInt F1(*integer_part);
    BigDecimalInt F2(*anotherReal.integer_part);
    if(F1 == F2)
    {

        int sign1 = sign() ;
        int sign2 = anotherReal.sign() ;

        deque<int> bdi1;
        deque<int> bdi2;

        for(char& ch : *fractional_part){
            if ( ch == '-' || ch == '+') continue;
            bdi1.push_back(ch - 48);
        }

        for(char& ch : *anotherReal.fractional_part){
            if ( ch == '-' || ch == '+') continue;
            bdi2.push_back(ch - 48);
        }

        int maxLen = max(bdi1.size(), bdi2.size());
        int minLen = min(bdi1.size(), bdi2.size()) ;

        for (int i = minLen; i < maxLen; ++i) {
            (bdi1.size() > bdi2.size() ? bdi2 : bdi1).push_back(0);
        }

        for (int i = 0; i < maxLen; ++i) {
            if ( bdi1[i] * sign1  < bdi2[i] * sign2) return true;
            else if ( bdi1[i] * sign1 > bdi2[i] * sign2) return false;

        }
        return false;
    }

    else if(F1 < F2){return true;}
    else{return false;}
}

bool BigReal::operator > (BigReal& anotherReal)
{

    BigDecimalInt F1(*integer_part);
    BigDecimalInt F2(*anotherReal.integer_part);
    if(F1 == F2)
    {

        int sign1 = sign() ;
        int sign2 = anotherReal.sign() ;


        deque<int> bdi1;
        deque<int> bdi2;

        for(char& ch : *fractional_part){
            if ( ch == '-' || ch == '+') continue;
            bdi1.push_back(ch - 48);
        }

        for(char& ch : *anotherReal.fractional_part){
            if ( ch == '-' || ch == '+') continue;
            bdi2.push_back(ch - 48);
        }

        int maxLen = max(bdi1.size(), bdi2.size());
        int minLen = min(bdi1.size(), bdi2.size()) ;

        for (int i = minLen; i < maxLen; ++i) {
            (bdi1.size() > bdi2.size() ? bdi2 : bdi1).push_back(0);
        }

        for (int i = 0; i < maxLen; ++i) {
            if ( bdi1[i] * sign1  > bdi2[i] * sign2) return true;
            else if ( bdi1[i] * sign1 < bdi2[i] * sign2) return false;

        }
        return false;
    }

    else if(F1 > F2){return true;}
    else{return false;}
}

bool BigReal::operator==(BigReal anotherReal)
{
    BigDecimalInt F1(*integer_part);
    BigDecimalInt F2(*anotherReal.integer_part);
    if(!(F1 == F2))
    {
        return false;
    }
    else
    {

        int sign1 = sign() ;
        int sign2 = anotherReal.sign() ;

        deque<int> bdi1;
        deque<int> bdi2;

        for(char& ch : *fractional_part){
            if ( ch == '-' || ch == '+') continue;
            bdi1.push_back(ch - 48);
        }

        for(char& ch : *anotherReal.fractional_part){
            if ( ch == '-' || ch == '+') continue;
            bdi2.push_back(ch - 48);
        }

        int maxLen = max(bdi1.size(), bdi2.size());
        int minLen = min(bdi1.size(), bdi2.size()) ;

        for (int i = minLen; i < maxLen; ++i) {
            (bdi1.size() > bdi2.size() ? bdi2 : bdi1).push_back(0);
        }

        for (int i = 0; i < maxLen; ++i) {
            if ( bdi1[i] * sign1  != bdi2[i] * sign2) return false;


        }
        return true;
    }
}

BigReal BigReal::operator-(BigReal &other)
{

    BigReal Final;
    BigDecimalInt A(*this->integer_part) , B(*other.integer_part);
    string frc1 , frc2;
    frc1 = *this->fractional_part;
    frc2 = *other.fractional_part;
    delete Final.integer_part ;
    delete Final.fractional_part ;
    delete Final.Total;
    delete Final.R_sign;
    Final = subtraction(*this,other);
    if(*this > other && this->sign() == -1)
    {
        delete  Final.R_sign;
        Final.R_sign = new int {1};
    }
    else if(*this > other && this->sign() == 1)
    {
        delete  Final.R_sign;
        Final.R_sign = new int {1};
    }
    else
    {
        delete  Final.R_sign;
        Final.R_sign = new int {-1};
    }
    return Final;

}

BigReal BigReal::operator+(BigReal &other)
{
    //
    BigReal Final;
    BigDecimalInt A(*this->integer_part) , B(*other.integer_part);
    string frc1 , frc2;
    frc1 = *this->fractional_part;
    frc2 = *other.fractional_part;
    delete Final.integer_part ;
    delete Final.fractional_part ;
    delete Final.Total;
    delete Final.R_sign;
    Final = addition(*this,other);
    if(*this > other && this->sign() == -1)
    {
        delete  Final.R_sign;
        Final.R_sign = new int {-1};
    }
    else if(*this < other && other.sign() == -1)
    {
        delete  Final.R_sign;
        Final.R_sign = new int {-1};
    }
    else
    {
        delete  Final.R_sign;
        Final.R_sign = new int {1};
    }
    return Final;
}

int BigReal::sign()
{
    return *R_sign;
}

int BigReal::size()
{
    return Total->size()-1;
}

ostream& operator << (ostream& out, BigReal& b){
    if(b.sign() == -1){out <<'-'<<*b.Total;}
    else out <<*b.Total;
    return out ;
}

istream& operator >> (istream& out, BigReal& b){
    string tmp_str;
    out >> tmp_str;
    BigReal tmp_br(tmp_str);
    b = tmp_br;
    return out;
}
// Helper function for addition.
BigReal BigReal::addition(BigReal& first, BigReal& seccond)
{

    BigReal total;
    string temp = "";

    delete total.integer_part ;
    delete total.fractional_part ;
    delete total.Total;
    delete total.R_sign;
    int frc_max_len = max(first.fractional_part->size() , seccond.fractional_part->size() );
    int frc_min_len = min(first.fractional_part->size() , seccond.fractional_part->size() );
    for (int i = frc_min_len; i < frc_max_len; ++i) {
        (first.fractional_part->size() > seccond.fractional_part->size() ? *seccond.fractional_part : *first.fractional_part) +='0';
    }

    BigDecimalInt A( *first.integer_part + *first.fractional_part);
    BigDecimalInt B(*seccond.integer_part + *seccond.fractional_part);

    BigDecimalInt tmp((A+B).getNumber());
    for (int i = tmp.getNumber().size() - frc_max_len; i <= tmp.getNumber().size(); ++i) {
        temp += tmp.getNumber()[i];
    }
    total.fractional_part = new string{temp};
    temp = "";

    for (int i = 0 ; i < tmp.getNumber().size() - frc_max_len; ++i) {
        temp += tmp.getNumber()[i];
    }
    total.integer_part = new string {temp};
    total.Total = new string {*total.integer_part + '.'+*total.fractional_part};
    total.R_sign = new int{tmp.sign()};
    return total;
}


// Helper function for subtraction.
BigReal BigReal::subtraction(BigReal &first, BigReal& seccond)
{

    BigReal total;
    string temp = "";

    delete total.integer_part ;
    delete total.fractional_part ;
    delete total.Total;
    delete total.R_sign;
    int frc_max_len = max(first.fractional_part->size() , seccond.fractional_part->size() );
    int frc_min_len = min(first.fractional_part->size() , seccond.fractional_part->size() );
    for (int i = frc_min_len; i < frc_max_len; ++i) {
        (first.fractional_part->size() > seccond.fractional_part->size() ? *seccond.fractional_part : *first.fractional_part) +='0';
    }

    BigDecimalInt A( *first.integer_part + *first.fractional_part);
    BigDecimalInt B(*seccond.integer_part + *seccond.fractional_part);

    if ( A == B){
        total.fractional_part = new string{"0"};
        total.integer_part = new string{"0"};
        total.Total = new string{"0.0"};
        total.R_sign = new int{0};
    }
    else {
        BigDecimalInt tmp((A-B).getNumber());
        for (int i = tmp.getNumber().size() - frc_max_len; i <= tmp.getNumber().size(); ++i) {
            temp += tmp.getNumber()[i];
        }

        total.fractional_part = new string{temp};
        temp = "";

        for (int i = 0 ; i < tmp.getNumber().size() - frc_max_len; ++i) {
            temp += tmp.getNumber()[i];
        }
        total.integer_part = new string {temp};
        total.Total = new string {*total.integer_part + '.'+*total.fractional_part};
        total.R_sign = new int{tmp.sign()};
    }
    return total;

}
