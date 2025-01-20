#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BTC
{
    private:
        std::map<std::string, float> exchangeRates;
        std::string firstDate;

        bool isDateValid(const std::string& date) const;
        void processLine(const std::string& line);
        float getExchangeRate(const std::string& date) const;

    public:
        BTC();
        BTC(const BTC& other);
        ~BTC();
        BTC& operator=(const BTC& other);

        bool parser(const std::string& filename);
        bool parser2(const std::string& filename);
};

#endif
