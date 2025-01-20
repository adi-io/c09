#include <iostream>
#include <fstream>
#include <sstream>
#include "BitcoinExchange.hpp"

BTC::BTC() : firstDate("") {}

BTC::BTC(const BTC& other) :
    exchangeRates(other.exchangeRates),
    firstDate(other.firstDate)
{}

BTC::~BTC() {}

BTC& BTC::operator=(const BTC& other)
{
    if (this != &other)
    {
        exchangeRates = other.exchangeRates;
        firstDate = other.firstDate;
    }
    return *this;
}

bool BTC::parser(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open database file." << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line);

    bool first = true;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        std::string exchangeRatestr;

        if (std::getline(ss, date, ',') && std::getline(ss, exchangeRatestr))
        {
            if (first)
            {
                firstDate = date;
                first = false;
            }
            try
            {
                float rate = std::stof(exchangeRatestr);
                exchangeRates[date] = rate;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: invalid rate in database for date: " << date << std::endl;
                continue;
            }
        }
    }
    file.close();
    return true;
}

bool BTC::isDateValid(const std::string& date) const
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    try
    {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        if (year < 2009 || year > 2022 ||
            month < 1 || month > 12 ||
            day < 1 || day > 31)
            return false;

        if (date < firstDate)
            return false;

    } catch (...)
    {
        return false;
    }
    return true;
}

float BTC::getExchangeRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = exchangeRates.upper_bound(date);
    if (it != exchangeRates.begin())
        --it;
    return it->second;
}

void BTC::processLine(const std::string& line)
{
    size_t delim = line.find('|');
    if (delim == std::string::npos)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }

    std::string date = line.substr(0, delim);
    std::string value = line.substr(delim + 1);

    date.erase(date.find_last_not_of(" \n\r\t")+1);
    value.erase(0, value.find_first_not_of(" \n\r\t"));

    if (!isDateValid(date))
    {
        std::cout << "Error: bad input => " << date << std::endl;
        return;
    }

    float fval;
    try
    {
        fval = std::stof(value);
        if (fval > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            return;
        }
        if (fval < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            return;
        }
    }
    catch (...)
    {
        std::cout << "Error: bad input => " << value << std::endl;
        return;
    }

    float rate = getExchangeRate(date);
    std::cout << date << " => " << fval << " = " <<
        rate * fval << std::endl;
}

bool BTC::parser2(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        processLine(line);
    }
    file.close();
    return true;
}
