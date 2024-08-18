#pragma once
#include <algorithm>
#include <iterator>
#include <numeric>


#include "hot_key.hpp"

class hot_key_hash final
{
public:
	size_t operator()(const hot_key& hot_keys) const noexcept
	{
		std::vector <size_t> result;
		std::ranges::transform(hot_keys, std::back_inserter(result),
			[](const std::string& key)
			{
				return std::hash<std::string>{}(key);
			});
		return std::accumulate(result.begin(), result.end(),static_cast<size_t> (0));
	}
};