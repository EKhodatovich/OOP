#pragma once

#include <vector>
#include "cell_position.hpp"

class Path final
{
	std::vector<CellPosition> path;
public:
	const std::vector<CellPosition>& get_path() const { return path; }
	Path(const std::vector<CellPosition>& path) { this->path = path; }
	Path() = default;
};
