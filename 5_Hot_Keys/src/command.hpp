#pragma once
#include <string>

class command final
{
	std::string command_string_;
public:
	explicit command(const std::string& command_string);
	[[nodiscard]] const std::string& get_command_string() const noexcept { return command_string_; }
	bool operator==(const command&) const = default;
};


