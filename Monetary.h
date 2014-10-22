#ifndef MONETARY_H
#define MONETARY_H

#include <iostream>
#include <string>

namespace Monetary
{

#define CENT_ERR "Hundradelarna mste ligga mellan noll och 99!"
#define CURR_ERR "Valutan skall vara ospecifierad (\"\") eller tre tecken lng!"
#define CURR_ASS_ERR "Tv objekt med olika, specificerade, valutor kan ej tilldelas varandra!"
#define CURR_ADD_ERR "Tv objekt med olika, specificerade, valutor kan ej adderas!"
#define CURR_CMP_ERR "Tv objekt med olika, specificerade, valutor kan ej jmfras!"
#define SIGN_ERR "Valutan får ej ha negativa värden!"


using Amount = unsigned long long;
using CentAmount = unsigned short;

class Money
{
public:
    Money(const std::string& currency_name = "", const Amount& curr_units = 0, const CentAmount& curr_cents = 0);
    Money(const Amount& curr_units, const CentAmount& curr_cents = 0);

    std::string currency() const;
    Amount GetUnits() const;
    CentAmount GetCents() const;

    std::ostream& print(std::ostream& output) const;

    Money& operator=(const Money& rhs);
    Money operator+(const Money& second_term) const;
    bool operator<(const Money& rhs) const;
    bool operator==(const Money& rhs) const;
    bool operator>(const Money& rhs) const;
    bool operator<=(const Money& rhs) const;
    bool operator>=(const Money& rhs) const;
    bool operator!=(const Money& rhs) const;
    Money& operator++();
    Money operator++(int);
    Money& operator+=(const Money& rhs);
    Money& operator--();
    Money operator--(int);
    Money operator-(const Money& second_term) const;
    Money& operator-=(const Money& rhs);

private:
    std::string currency_name;
    Amount curr_units;
    CentAmount curr_cents;

    // Funktionen verifierar att klassens medlemsvariabler har
    // korrekta värden och slänger fel om så ej är fallet.
    void VerifyMemberValues() const;
};

std::ostream& operator<<(std::ostream& os, const Money& rhs);
std::istream& operator>>(std::istream& is, Money& rhs);

class monetary_exception : public std::exception
{
public:
    explicit monetary_exception(const std::string& what_arg) : msg_(what_arg) {}
    explicit monetary_exception(const char* what_arg) : msg_(what_arg) {}

    const char* what() const noexcept
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};
}
#endif
