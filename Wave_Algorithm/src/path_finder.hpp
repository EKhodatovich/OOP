#pragma once
#include "maze.hpp"
#include "path.hpp"

#include <unordered_map>

class PathFinder final
{
	static bool start_and_finish_are_valid(const Maze& maze, const CellPosition& start_position, const CellPosition& finish_position);
	static bool wave_propagation(const Maze& maze,std::unordered_map<CellPosition, int>& map_of_possible_ways, const CellPosition& start_position, const CellPosition& finish_position);

	static std::vector <CellPosition> path_recovery(const Maze& maze, const std::unordered_map<CellPosition, int>& map_of_possible_ways, const CellPosition& start_position, const CellPosition& finish_position);
	static bool is_elements_near(const Maze& maze, const CellPosition& current_element, const CellPosition& other_element);
public:
	PathFinder() = delete;
	static Path find_the_way(const Maze& maze, const CellPosition& start_position, const CellPosition& finish_position);
};
