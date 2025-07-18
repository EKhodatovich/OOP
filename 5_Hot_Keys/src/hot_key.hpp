#pragma once
#include <unordered_set>
#include <string>

struct hot_key final
{
private:
	std::unordered_set<std::string> combination_;
public:
	explicit hot_key(const std::unordered_set<std::string>& combination);
	[[nodiscard]] auto begin() const noexcept { return combination_.begin(); }
	[[nodiscard]] auto end() const noexcept { return combination_.end(); }

	bool operator==(const hot_key&) const = default;
};


