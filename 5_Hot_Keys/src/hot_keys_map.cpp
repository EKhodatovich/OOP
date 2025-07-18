#include "hot_keys_map.hpp"

#include <algorithm>
#include <stdexcept>


using namespace std;

hot_keys_map::hot_keys_map(const std::vector<key_command_combination>& combinations) 
{
	for (const auto& combination : combinations )
	{
		auto [_, key_not_in_map_already] = hot_key_to_command_.insert({ combination.get_hot_key(), combination.get_command() });
		if (key_not_in_map_already)
		{
			command_to_hot_key_.insert({ combination.get_command(), combination.get_hot_key() });
		}
	}
}

void hot_keys_map::add_key_command_combination(const hot_key& key, const command& command)
{
	auto [_, key_not_in_map_already] = hot_key_to_command_.insert({ key,command });
	if (key_not_in_map_already)
	{
		command_to_hot_key_.insert({ command, key });
	}
}

void hot_keys_map::remove_command(const command& command)
{
	auto [first_key_with_equal_command, last_key_with_equal_command] = command_to_hot_key_.equal_range(command);

	if (first_key_with_equal_command == command_to_hot_key_.end())
	{
		throw out_of_range("Command is not in the map");
	}
	auto current = first_key_with_equal_command;

	while (current != last_key_with_equal_command)
	{
		auto [current_key, current_command] = *current;
		hot_key_to_command_.erase(current_command);
		++current;
	}
	command_to_hot_key_.erase(first_key_with_equal_command, last_key_with_equal_command);
}


void hot_keys_map::remove_hot_key(const hot_key& key)
{
	const auto key_to_command_it = hot_key_to_command_.find(key);
	if (key_to_command_it == hot_key_to_command_.end())
	{
		throw out_of_range("Key is not in the map");
	}

	const auto [_, desired_command] = *key_to_command_it;
	const auto [first_key_with_desired_command, last_key_with_desired_command] = command_to_hot_key_.equal_range(desired_command);


	const auto current = std::find_if(first_key_with_desired_command, last_key_with_desired_command, 
			[key] (const pair<command,hot_key>& current_) {return current_.second == key; });
	

	command_to_hot_key_.erase(current);
	hot_key_to_command_.erase(key_to_command_it);
}

vector<hot_key> hot_keys_map::find_hot_keys_by_command(const command& command_) const
{
	const auto& [first_key_with_equal_command, last_key_with_equal_command] = command_to_hot_key_.equal_range(command_);
	if (first_key_with_equal_command == command_to_hot_key_.end())
	{
		throw out_of_range("Command is not in the map");
	}
	vector<hot_key> result;

	transform(first_key_with_equal_command, last_key_with_equal_command, std::back_inserter(result), 
		[result](const pair<const command, hot_key>& current) ->const hot_key&
		{
			return current.second;
		});

	return result;
}

const command& hot_keys_map::find_command_by_hot_key(const hot_key& hot_key) const
{
	if (const auto result = hot_key_to_command_.find(hot_key); result != hot_key_to_command_.end())
	{
        const auto& [result_key, result_command] = *result;
		return result_command;
	}
	throw out_of_range("Key is not in the map");
}

void hot_keys_map::clear() noexcept
{
	command_to_hot_key_.clear();
	hot_key_to_command_.clear();
}

conflicts hot_keys_map::merge(const hot_keys_map& second_map)
{
	vector <hot_key> result;
	for (const auto& [additional_key, additional_command] : second_map.hot_key_to_command_)
	{
        auto [possible_conflict, no_conflict] = hot_key_to_command_.try_emplace( additional_key, additional_command);
        if (!no_conflict && possible_conflict->second != additional_command)
		{
			result.push_back(additional_key);
		}
        else if (no_conflict)
        {
            command_to_hot_key_.insert(make_pair(additional_command, additional_key));
        }
	}
	return conflicts{ std::move(result) };
}
