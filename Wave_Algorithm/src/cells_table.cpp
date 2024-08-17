#include "cells_table.hpp"
#include "exceptions.hpp"
CellsTable::CellsTable(const std::vector<CellType>& rows, const size_t width, const size_t height, const CellPosition start_position, const CellPosition finish_position)
{
	if (rows.size() != width*height)
	{
		throw DifferentSizesException();
	}
	if (width == 0 || height == 0)
	{
		*this = CellsTable{};
		return;
	}
	if (start_position.get_x() >= width || start_position.get_y() >= height)
	{
		throw WrongStartPosition();
	}
	if (finish_position.get_x() >= width || finish_position.get_y() >= height)
	{
		throw WrongFinishPosition();
	}
	this->rows = rows;
	rows_width = width;
	rows_height = height;
	this->start_id = start_position;
	this->finish_id = finish_position;
}