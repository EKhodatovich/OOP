#pragma once

#include "cell_position.hpp"
#include "cell_type.hpp"


class Maze final
{
public:
	Maze() = delete;
	Maze(const std::vector<CellType>& vector_from_rows,const size_t rows_width,const size_t rows_height );

	size_t get_width() const { return maze_width; }
	size_t get_height() const { return maze_height; }

	CellType get_cell_type_by_coordinates(CellPosition coordinates) const;
	std::vector<CellPosition> get_near_elements(CellPosition id) const;

	bool cell_in_maze(const CellPosition& coordinates) const;
private:
	size_t cell_id_by_coordinates(const CellPosition coordinates) const { return coordinates.get_x() + coordinates.get_y() * maze_width; }
	std::vector<CellType> maze_vector;

	size_t maze_width = 0;
	size_t maze_height = 0;
};
