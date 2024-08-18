#pragma once

#include "key_command_combination.hpp"
#include "hot_key_hash.hpp"
#include "command_hash.hpp"
#include "conflicts.hpp"
#include <unordered_map>


class hot_keys_map final
{
	std::unordered_multimap<command, hot_key, command_hash> command_to_hot_key_;
	std::unordered_map<hot_key, command, hot_key_hash> hot_key_to_command_;

public:
	hot_keys_map(const std::vector<key_command_combination>&  combinations);

	void add_key_command_combination(const hot_key& key, const command& command);

	void remove_command(const command& command);
	void remove_hot_key(const hot_key& key);

	[[nodiscard]] const command& find_command_by_hot_key(const hot_key& hot_key) const;
	[[nodiscard]] std::vector<hot_key> find_hot_keys_by_command(const command& command_) const;

	void clear() noexcept;

	conflicts merge(const hot_keys_map& second_map);

	[[nodiscard]] auto begin() const { return command_to_hot_key_.begin(); }
	[[nodiscard]] auto end() const { return command_to_hot_key_.end(); }
};
