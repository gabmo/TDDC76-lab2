/*
 * FILNAMN:       lab2.cc
 * LABORATION:    2
 * PROGRAMMERARE: Andreas Kempe 920607-1210 yi3
 *                Karl Larsson 891114-1938 yi3
 * DATUM:         2014-10-22
 *
 * BESKRIVNING 
 * 
 * Testprogram f�r klassen Monetary.
 */


#include <iostream>
#include <sstream>
#include "Monetary.h"

using namespace std;
using namespace Monetary;

int main()
{
  
	Money m1;
	Money m2{"OST", 100, 11};
	Money m3{"OST", 101, 10};
	Money m4;
	Money m5; //	Svenska kronor: 10 kronor, 0 öre
	Money m6{"FFR", 100, 50};// Franska franc: 100 franc, 50 centimer
	Money m7{m6}; // Franska franc: 100 franc, 50 centimer
	Money m8{m1};
	Money m9{"SEK", 1000, 80};
	
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
	
	//cout << m1.currency() << endl;
    
    Money in1, in2;
	std::stringstream ss("10.10ostar20.00"); 
	cin >> in1;

    if (ss.fail())
        cout << "in1 fail!" << endl;

	cin >> in2;

    if (ss.fail())
        cout << "in2 fail!" << endl;

	cout << "in1: " << in1 << endl << "in2: " << in2 << endl;
    
    string buffer = "";
    buffer += cin.peek();

    cout << buffer << endl;
	
	/*cout << (m2 + m3) << endl;
	cout  << m2 << " " << --m2 << endl;
	cout << m2 << " " << m2-- << " " << m2 << endl;
	cout << (m3 - m2) << endl;
	m3 -= m2;
	cout << m3 << endl;
	std::stringstream("") >> m3;
	cout << m3 << endl;*/
} 


