#pragma once

#include "hot_key.hpp"
#include "command.hpp"

class key_command_combination final
{
	hot_key hot_key_;
	command command_;
public:
	key_command_combination(hot_key hot_key, command command) noexcept : hot_key_{ std::move(hot_key) }, command_{ std::move(command )} {}

	[[nodiscard]] const hot_key& get_hot_key() const noexcept { return hot_key_; }
	[[nodiscard]] const command& get_command() const noexcept { return command_; }
};