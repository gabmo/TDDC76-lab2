#include "Monetary.h"
#include <stdexcept>
#include <cctype>
#include <sstream>

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

// Returnera strömmen som matas in så att funktionen kan returneras
// direkt i strömoperatorn för utmatning.
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

    // Modluo används för att få antalet cent efter additionen
    // och heltalsdivision används för att omvandla överflödande
    // cents till units.
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
    // Räkna upp cents med ett och utför heltalsdivision med 100
    // för att få det nya antalet units om överslag sker för cents.
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

    // Om den mest signifikanta enheten är störst blir resultatet alltid negativt
    // och ett fel skall slängas.
    if (curr_units < second_term.curr_units)
        throw monetary_exception(SIGN_ERR);

    // Är antalet cents större än antalet som skall dras bort sker inget överslag
    // och cents och units kan behandlas direkt.
    if (curr_cents >= second_term.curr_cents)
    {
        tmp.curr_cents = curr_cents - second_term.curr_cents;
        tmp.curr_units = curr_units - second_term.curr_units;
    }
    else
    {
        // Skulle nuvarande units vara like med det andra objektets units eller noll
        // kommer slutresultatet att bli negativt om ett överslag av cents sker.
        if (curr_units == second_term.curr_units || curr_units == 0)
            throw monetary_exception(SIGN_ERR);

        // Låna 100 cents från units och utför subtraktionen, ty överslag har skett.
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

    if (token.length() > 0)
    {
        // Avgör om den inlästa strängen är ett numeriskt värde eller
        // en textsträng som representerar en valuta.
        if (!isdigit(token.at(0)))
        {
            currency = token;

            is >> token;
        }

        std::stringstream ss(token);

        std::string buffer;

        // Här vet vi att vi skall ha ett numeriskt värde så dela strängen
        // på decimaltecknet för att få decimaler och heltal separat.
        std::getline(ss, buffer, '.');
        std::stringstream(buffer) >> units;

        // Om vi inte har nått slutet av strömmen har vi decimaler också och i
        // sådana fall läser vi in dem.
        if (!ss.eof())
        {
            ss >> cents;
        }
        else
            cents = 0;
    }

    rhs = Money(currency, units, cents);

    return is;

}
