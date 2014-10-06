#include "Monetary.h"
#include <stdexcept>
#include <cctype>
#include <sstream>
#include <cstdlib>

using namespace Monetary;

Money::Money(const std::string& currency_name, const Amount& curr_units, const CentAmount& curr_cents) :
currency_name(currency_name), curr_units(curr_units), curr_cents(curr_cents)
{
	VerifyMemberValues();
}

Money::Money(const Amount& curr_units, const CentAmount& curr_cents) :
curr_units(curr_units), curr_cents(curr_cents)
{
	currency_name = "";

	VerifyMemberValues();
}

std::string Money::currency() const
{
	return currency_name;
}

Amount Money::GetUnits() const
{
	return curr_units;
}

CentAmount Money::GetCents() const
{
	return curr_cents;
}

std::ostream& Money::print(std::ostream& output) const
{
	output << (currency_name.length() > 0 ? currency_name + ": " : "")
		   << curr_units << "." << curr_cents;

	return output;
}

Money& Money::operator=(const Money& rhs)
{
	if (rhs.currency_name.length() > 0)
	{
		if (currency_name.length() > 0 && currency_name.compare(rhs.currency_name) != 0)
			throw monetary_exception(CURR_ASS_ERR);
		
		if (currency_name.length() == 0)
			currency_name = rhs.currency_name;
	}

	curr_units = rhs.curr_units;
	curr_cents = rhs.curr_cents;

	return *this;
}

Money Money::operator+(const Money& second_term) const
{
  if (currency_name.length() != 0 && second_term.currency_name.length() != 0 &&
      currency_name.compare(second_term.currency_name) != 0)
    throw monetary_exception(CURR_ADD_ERR);

  Money tmp;

  if (currency_name.length() > 0)
    tmp.currency_name = currency_name;
  else
    tmp.currency_name = second_term.currency_name;

  tmp.curr_cents = (curr_cents + second_term.curr_cents) % 100;
  tmp.curr_units = (curr_units + second_term.curr_units) +
                   (curr_cents + second_term.curr_cents) / 100;

  return tmp;
}

bool Money::operator<(const Money& rhs) const
{
  if (currency_name.length() != 0 && rhs.currency_name.length() != 0 &&
      currency_name.compare(rhs.currency_name) != 0)
    throw monetary_exception(CURR_CMP_ERR);

  if (curr_units == rhs.curr_units)
    return curr_cents < rhs.curr_cents;
  else
    return curr_units < rhs.curr_units;
}

bool Money::operator==(const Money& rhs) const
{
   if (currency_name.length() != 0 && rhs.currency_name.length() != 0 &&
      currency_name.compare(rhs.currency_name) != 0)
     throw monetary_exception(CURR_CMP_ERR);

   return curr_cents == rhs.curr_cents && curr_units == rhs.curr_units;
}

bool Money::operator>(const Money& rhs) const
{
  return rhs < *this;
}

bool Money::operator<=(const Money& rhs) const
{
  return *this < rhs || *this == rhs;
}

bool Money::operator>=(const Money& rhs) const
{
  return rhs < *this || *this == rhs;
}

bool Money::operator!=(const Money& rhs) const
{
  return !(*this == rhs);
}

Money& Money::operator++()
{
  curr_units = curr_units + (++curr_cents / 100);
  curr_cents = curr_cents % 100;

  return *this;
}

Money Money::operator++(int)
{
  Money tmp(*this);
  
  operator++();

  return tmp;
}

Money& Money::operator+=(const Money& rhs)
{
	*this = *this + rhs;
	return *this;
}

Money& Money::operator--()
{
	if (curr_cents > 0)
	{
		curr_cents -= 1;
		return *this;
	}
	else if (curr_units == 0)
		throw monetary_exception(SIGN_ERR);

	curr_units -= 1;
	curr_cents = 99;

	return *this;
}

Money Money::operator--(int)
{
	Money tmp(*this);

	operator--();

	return tmp;
}

Money Money::operator-(const Money& second_term) const
{
	if (currency_name.length() != 0 && second_term.currency_name.length() != 0 &&
		currency_name.compare(second_term.currency_name) != 0)
		throw monetary_exception(CURR_ADD_ERR);

	Money tmp;

	if (currency_name.length() > 0)
		tmp.currency_name = currency_name;
	else
		tmp.currency_name = second_term.currency_name;
	
	if (curr_units < second_term.curr_units)
		throw monetary_exception(SIGN_ERR);

	if (curr_cents >= second_term.curr_cents)
	{
		tmp.curr_cents = curr_cents - second_term.curr_cents;
		tmp.curr_units = curr_units - second_term.curr_units;
	}
	else
	{
		if (curr_units == second_term.curr_units || curr_units == 0)
			throw monetary_exception(SIGN_ERR);

		tmp.curr_cents = 100 + curr_cents - second_term.curr_cents;
		tmp.curr_units = curr_units - second_term.curr_units - 1;
	}

	return tmp;
}

Money& Money::operator-=(const Money& rhs)
{
	*this = *this - rhs;
	return *this;
}

void Money::VerifyMemberValues() const
{
	// Valutan skall bestå av tre tecken eller inget tecken.
	if (currency_name.length() != 3 && currency_name.length() != 0)
		throw monetary_exception(CURR_ERR);	
	
	// Hundradelarna måste ligga mellan noll och 99.
	if (curr_cents > 99)
		throw monetary_exception(CENT_ERR);
}

std::ostream& Monetary::operator<<(std::ostream& os, const Money& rhs)
{
	return rhs.print(os);	
}

std::istream& Monetary::operator>>(std::istream& is, Money& rhs)
{ 
	std::string token;
	Amount units = 0;
	CentAmount cents = 0;

	std::string currency = "";

	is >> token;

	if (token.length() > 0 && !isdigit(token.at(0)))
	{
		currency = token;

		is >> token;
	}

	if (token.length() > 0)
	{
		std::stringstream ss(token);
	
		char* buffer = new char[token.length()];

		ss.getline(buffer, token.length(), '.');
		units = atoll(buffer);

		if (!ss.eof())
		{
			ss.getline(buffer, token.length());
			cents = atoll(buffer);
		}
		else
			cents = 0;
		
		delete buffer;
	}

	rhs = Money(currency, units, cents);

	return is;
		
}
