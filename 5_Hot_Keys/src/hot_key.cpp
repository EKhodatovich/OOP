#include "hot_key.hpp"
#include "exceptions.hpp"
#include "string_to_lowercase.hpp"
using namespace std;

hot_key::hot_key(const unordered_set<string>& combination)
{
	if (combination.empty())
	{
		throw empty_string();
	}
	for (auto key: combination)
	{
		check_string_for_spaces_and_lower_symbols(key);
		combination_.insert(key);
	}
}

