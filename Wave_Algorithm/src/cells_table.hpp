#pragma once

#include <vector>

#include "cell_type.hpp"
#include "cell_position.hpp"

class CellsTable final
{
	std::vector<CellType> rows;
	size_t rows_width = 0;
	size_t rows_height = 0;
	CellPosition start_id{};
	CellPosition finish_id{};
public:
	CellsTable() = default;
	CellsTable(const std::vector<CellType>& rows, const size_t width, const size_t height, const CellPosition start_position, const CellPosition finish_position);
	const std::vector<CellType>& get_rows() const { return rows; }
	size_t get_width() const { return rows_width; }
	size_t get_height() const { return rows_height; }

	CellPosition get_start() const { return start_id; }
	CellPosition get_finish() const { return finish_id; }
};
