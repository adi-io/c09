#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BTC obj;

    if (!obj.parser("data.csv"))
        return 1;
    if (!obj.parser2(argv[1]))
        return 1;

    return 0;
}
