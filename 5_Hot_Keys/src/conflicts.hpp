#pragma once
#include "hot_key.hpp"
#include <vector>

class conflicts final
{
	std::vector<hot_key> vector_of_conflicts_;
public:
	explicit conflicts(std::vector<hot_key> conflicts) : vector_of_conflicts_(std::move(conflicts)) {}
	[[nodiscard]] const std::vector<hot_key>& get_vector_of_conflicts() const noexcept { return vector_of_conflicts_; }
};