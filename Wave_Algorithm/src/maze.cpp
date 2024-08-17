#include "maze.hpp"
#include "exceptions.hpp"
#include <stdexcept>
using namespace std;


Maze::Maze(const std::vector<CellType>& vector_from_rows,const size_t rows_width,const size_t rows_height)
{
	if (vector_from_rows.size() != rows_width*rows_height)
	{
		throw DifferentSizesException();
	}
	if (rows_width == 0 || rows_height == 0)
	{
		throw EmptyMazeException();
	}
	maze_width = rows_width;
	maze_height = rows_height;
	maze_vector = vector(vector_from_rows);
}

CellType Maze::get_cell_type_by_coordinates(const CellPosition coordinates) const
{
	if (coordinates.get_x() >= maze_width || coordinates.get_y() >= maze_height)
	{
		throw std::out_of_range("Wrong cell coordinates");
	}
	return maze_vector[cell_id_by_coordinates(coordinates)];
}

vector<CellPosition> Maze::get_near_elements(const CellPosition id) const
{
	vector<CellPosition> result;
	const size_t x = id.get_x();
	const size_t y = id.get_y();
	if (y>=maze_height || x>= maze_width)
	{
		throw std::out_of_range("ID is out of maze range");
	}
	if (y!=0)
	{
		result.emplace_back( x, y - 1 );
	}
	if (x != 0)
	{
		result.emplace_back( x-1, y);
	}
	if (y!= maze_height-1)
	{
		result.emplace_back( x, y+1 );
	}
	if (x != maze_width- 1)
	{
		result.emplace_back( x+1, y );
	}
	return result;
}


bool Maze::cell_in_maze(const CellPosition& coordinates) const
{
	return (coordinates.get_x() < maze_width && coordinates.get_y() < maze_height);
}
