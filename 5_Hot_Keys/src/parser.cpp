#include "parser.hpp"
#include <istream>

using namespace std;
static constexpr char key_command_delimiter = '=';
static constexpr char key_delimiter = '+';

vector <key_command_combination> parser::parse(istream& is)
{
	vector <key_command_combination> result;
	string line;

	while (getline(is, line))
	{
		unordered_set<string> combination;
		const size_t delimiter_position = line.find(key_command_delimiter);

		const string hot_key_string = line.substr(0, delimiter_position);
		const string command_string = line.substr(delimiter_position+1, line.length());

		hot_key key{ make_hot_key_set(hot_key_string) };
		command command{ command_string };
		result.emplace_back(key,command);
	}
	return result;
}

unordered_set<string> parser::make_hot_key_set(const string& keys)
{
	size_t previous_delimiter_position = 0;
    size_t delimiter_position = 0;
	std::unordered_set<std::string> result;
	while ((delimiter_position = keys.find(key_delimiter, previous_delimiter_position)) != string::npos)
	{
		string combination_part = keys.substr(previous_delimiter_position, delimiter_position - previous_delimiter_position);
		result.insert(combination_part);
		previous_delimiter_position = delimiter_position + 1;
	}
	result.insert(keys.substr(previous_delimiter_position, keys.length() - previous_delimiter_position));
	return result;
}
