#pragma once

#include "key_command_combination.hpp"
#include <vector>

class parser final
{
	[[nodiscard]] static std::unordered_set<std::string> make_hot_key_set(const std::string& keys);
public:
	parser() = delete;
	[[nodiscard]] static std::vector <key_command_combination> parse(std::istream& is);
};
