#include <string>
#include <vector>
#include <map>

class BTC
{
	public:
		std::map<std::string, float> exchangeRates;
		std::vector<std::pair<std::string, float>> inputData;
		BTC();
		~BTC();
		void	parser();
		void	parser2();
		void	print();
};
