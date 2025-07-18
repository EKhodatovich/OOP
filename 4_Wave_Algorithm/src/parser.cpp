#include "parser.hpp"
#include "exceptions.hpp"
#include <sstream>

using namespace std;


CellsTable Parser::parse(std::istream &is, const CellTypesConvertor& ctc)
{
	vector<CellType> result = {};
	size_t result_size = 0;
	string line;
	size_t y = 0;

	CellPosition start{};
	CellPosition finish{};
	while (getline(is, line))
	{
		istringstream iss(line);
		vector<CellType> line_numbers;
		char n = 0;

		while (iss >> n)
		{
			if (n != ' ')
			{
				if (n == '2')
				{
					start = CellPosition{ line_numbers.size(), y};
				}
				else if (n == '3')
				{
					finish = CellPosition{ line_numbers.size(), y}; 
				}
				line_numbers.push_back(ctc.front_convert(n));
			}
		}
		if (y != 0 && line_numbers.size() != result_size)
		{
			throw DifferentStringSizeException();
		}
		if (!line_numbers.empty())
		{
			result_size = line_numbers.size();
			result.insert(result.begin() + line_numbers.size() * y, line_numbers.begin(), line_numbers.end());
		}
		else
		{
			throw EmptyStringException();
		}
		++y;
	}
	return CellsTable{ result, result_size, y, start, finish };
}
