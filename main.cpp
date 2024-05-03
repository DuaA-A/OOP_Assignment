#include <iostream>
#include "BigNumber.h"

using namespace std;

int main() {
    BigReal n1("12345678901234567890.12345678901234567890");
    BigReal n2("-12345678901234567890.12345678901234567890");
    BigReal n3("2.00000000000000000000000001");
    BigReal n4("4563173412.1234671412413");
    BigReal n7("11111111111111.1111111111");
    BigReal n8("-11111111111111.1111111111");
    BigReal n9("11111111111111.1111111111");
    BigReal n5 = n1+n2;
    BigReal n6 =n3-n4;
    cout<<n5<<endl;
    cout<<n6<<endl;
    if (n1>n2)
        cout<<"N1 is bigger than N2. "<<endl;
    else
        cout<<"N1 is less than or equal to N2. "<<endl;

    if (n2<n4)
        cout<<"N2 is less than N4. "<<endl;
    else
        cout<<"N4 is bigger than or equal to N2. "<<endl;

    if (n7==n8)
        cout<<"N7 is equal to N8. "<<endl;
    else
        cout<<"N7 is not equal to N8. "<<endl;

    if (n7==n9)
        cout<<"N7 is equal to N9. "<<endl;
    else
        cout<<"N7 is not equal to N9. "<<endl;

    return 0;
}
