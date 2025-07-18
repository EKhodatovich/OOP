#pragma once
#include <algorithm>
#include <string>

#include "exceptions.hpp"


static void check_and_lower_symbol(char& symbol)
{
	if (symbol == ' ' || symbol== '\n' || symbol=='\t')
	{
		throw string_with_spaces();
	}
	symbol = static_cast<char>(tolower(symbol));
}

inline void check_string_for_spaces_and_lower_symbols(std::string& str)
{
	if (str.empty())
	{
		throw empty_string();
	}
	std::ranges::for_each(str, check_and_lower_symbol);
	
}
