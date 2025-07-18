#pragma once
#include "hot_keys_map.hpp"

#include "ostream"

class writer final
{
public:
	writer() = delete;
	static void write_map(const hot_keys_map& map, std::ostream& os);
	static void write_conflicts(const conflicts& conflicts, std::ostream& os);
};