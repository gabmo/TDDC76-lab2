/*
 * FILNAMN:       lab2.cc
 * LABORATION:    2
 * PROGRAMMERARE: Andreas Kempe 920607-1210 yi3
 *                Karl Larsson 891114-1938 yi3
 * DATUM:         2014-10-22
 *
 * BESKRIVNING 
 * 
 * Testprogram för klassen Monetary.
 */


#include <iostream>
#include <sstream>
#include "Monetary.h"

using namespace std;
using namespace Monetary;

int main()
{
  try //Detta har vi tänkt ska lyckas
    {
        // Initiering
        cout << "Initiering" << endl;

	Money m1;
	Money m2{"OST", 100, 11};
	Money m3{"OST", 101, 10};
	Money m4;
	Money m5{"SEK", 10};; //	Svenska kronor: 10 kronor, 0 Ã¶re
	Money m6{"FFR", 100, 50};// Franska franc: 100 franc, 50 centimer
	Money m7{m6}; // Franska franc: 100 franc, 50 centimer
	Money m8{m1};
	Money m9{"SEK", 1000, 80};

	try
	  { Money m10{"USD", 10, 100}; } // För mycket cents
	catch (const monetary_exception& e)
	  { cout << "Undantag fangat: " << e.what() << endl; }

	try 
	  { Money m11{"USDOLLAR", 10, 50}; } // För långt namn
	catch (const monetary_exception& e)
	  { cout << "Undantag fangat: " << e.what() << endl; }

	try 
	  { Money m12{"USD", -10, 50}; } // Minus på kontot
	catch (const monetary_exception& e)
	  { cout << "Undantag fangat: " << e.what() << endl; }
       
	try 
	  { Money m13{"USD", 10, -50}; } // Negativa cent
	catch (const monetary_exception& e)
	  { cout << "Undantag fangat: " << e.what() << endl; }
 
	// Utskrift
	cout << endl << "Utskrift" << endl;

	// 2 objekt med .print syntax.
	m1.print(cout);
	cout << endl;
	m2.print(cout);
	cout << endl;
	
	// Samma objekt med << operator.
	cout << endl <<  m1 << endl << m2 << endl;

	// Det andra objekt har initierats med det första.
	cout << endl;
	m1.print(cout);
	cout << endl;
	m8.print(cout);
	cout << endl;

	// Tilldelning
	cout << endl << "Tilldelning" << endl;
	cout << "FÃ¶re tilldelning:" << endl;
	cout << m5 << endl << m4 << endl;

	m5 = m4;

	cout << "Efter tilldelning:" << endl;
	cout << m5 << endl << m4 << endl << endl;

	try
	  { m2 = m5; } // Olika valutor
	catch (const monetary_exception e)
	  { cout << "Undantag fangat: " << e.what() << endl; }

	// Addition
	cout << endl << "Addition" << endl;
	cout << m1 + m2 << endl;
	cout << m1 + m3 << endl;
	cout << m2 + m3 << endl;
	
	cout << endl << m1 + m6 << endl;
	cout << m6 + m6 << endl;

	try
	  { cout << (m2 + m5); } // Olika valutor
	catch (const monetary_exception e)
	  { cout << "Undantag fangat: " << e.what() << endl; }

	// Jämförelse
	cout << endl << "Jamforelse" << endl;
	cout << (m2 < m3) << endl; // true
	cout << (m4 != m3) << endl; // true
	cout << (m1 >= m4) << endl; // true
	cout << endl;
	cout << (m5 > m9) << endl; // false
	cout << (m2 == m3) << endl; // false
	cout << (m7 <= m1) << endl; // false
	cout << endl;

	try
	  { cout << (m2 == m5); } // Olika valutor
	catch (const monetary_exception e)
	  { cout << "Undantag fangat: " << e.what() << endl; }


	// Stegning

       
	
	
    }
  catch (monetary_exception e)
    { cout << "Se over testfilen, detta undantag var inte planerat, fangade: " << e.what() << endl; }
	
	
	
	/*
	std::stringstream ss("SEK 10.50 OST 5999999999999.99"); 
	ss >> m1;
	ss >> m2;
	cout << m1 << endl << m2 << endl;
	*/
	/*cout << (m2 + m3) << endl;
	cout  << m2 << " " << --m2 << endl;
	cout << m2 << " " << m2-- << " " << m2 << endl;*/
  /*
	cout << (m3 - m2) << endl;
	m3 -= m2;
	cout << m3 << endl;
	std::stringstream("") >> m3;
	cout << m3 << endl;
  */
} 


