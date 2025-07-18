#include "writer.hpp"

#include <sstream>
using namespace std;

void writer::write_map(const hot_keys_map& map, std::ostream& os)
{
	auto previous_command = map.begin()->first;

	for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
	{
        const auto& [current_command, current_hot_key] = *iterator;
		if (iterator == map.begin() || current_command != previous_command)
		{
			os << '\n' << current_command.get_command_string() << '\t';
		}
		stringstream keys;
		for (auto key = current_hot_key.begin(); key!=current_hot_key.end(); ++key)
		{
			keys << *key << '+';
		}
		string hot_key(keys.str());
		hot_key.pop_back();
		os << hot_key;
		os << ", ";
		previous_command = current_command;
	}
}

void writer::write_conflicts(const conflicts& conflicts, std::ostream& os)
{
	os << "conflicts: " << conflicts.get_vector_of_conflicts().size() << '\n';
    for (const auto& conflict : conflicts.get_vector_of_conflicts())
	{
		stringstream keys;
		for (auto key = conflict.begin(); key != conflict.end(); ++key)
		{
			keys << *key << '+';
		}
		string hot_key(keys.str());
		hot_key.pop_back();
		os << hot_key;
		os << '\n';
	}
}

