#include <iostream>
#include <sstream>
#include "Monetary.h"

using namespace std;
using namespace Monetary;

int main()
{
    Money m1;
    Money m2 {"OST", 100, 11};
    Money m3 {"OST", 101, 10};
    Money m4;
    Money m5; //	Svenska kronor: 10 kronor, 0 öre
    Money m6 {"FFR", 100, 50}; // Franska franc: 100 franc, 50 centimer
    Money m7 {m6}; // Franska franc: 100 franc, 50 centimer
    Money m8 {m1};
    Money m9 {"SEK", 1000, 80};

    /*
    cout << "Före tilldelning:" << endl;

    cout << m5 << endl << m4 << endl;

    m5 = m4;

    cout << "Efter tilldelning:" << endl;
    cout << m5 << endl << m4 << endl;

    m7.print(cout);
    cout << endl;
    m8.print(cout);
    cout << endl;
    m3.print(cout);
    cout << endl;

    cout << m7 << endl << m8 << endl << m3 << endl;

    */
    /*
    cout << m1.currency() << endl;

    std::stringstream ss("SEK 10.50 OST 5999999999999.99");
    ss >> m1;
    ss >> m2;
    cout << m1 << endl << m2 << endl;
    */
    /*cout << (m2 + m3) << endl;
    cout  << m2 << " " << --m2 << endl;
    cout << m2 << " " << m2-- << " " << m2 << endl;*/
    cout << (m3 - m2) << endl;
    m3 -= m2;
    cout << m3 << endl;
    std::stringstream("") >> m3;
    cout << m3 << endl;
}
