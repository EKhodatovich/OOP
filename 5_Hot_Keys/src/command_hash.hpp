#pragma once
#include "command.hpp"

class command_hash final
{
public:
	size_t operator()(const command& command) const noexcept
	{
		return std::hash<std::string> {} (command.get_command_string());
	}
};