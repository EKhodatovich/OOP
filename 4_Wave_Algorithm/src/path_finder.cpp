#include "path_finder.hpp"
#include <deque>

using namespace std;

bool PathFinder::start_and_finish_are_valid(const Maze& maze, const CellPosition& start_position, const CellPosition& finish_position)
{
	return	maze.cell_in_maze(start_position) && maze.cell_in_maze(finish_position) &&
			maze.get_cell_type_by_coordinates(start_position) != CellType::wall && 
			maze.get_cell_type_by_coordinates(finish_position) != CellType::wall &&
			start_position != finish_position;
}

Path PathFinder::find_the_way(const Maze& maze,const CellPosition& start_position, const CellPosition& finish_position)
{

	if (maze.get_width() < 2 || maze.get_height() < 2 || !start_and_finish_are_valid(maze, start_position, finish_position))
	{
		return Path{};
	}
	if (unordered_map<CellPosition,int> map_of_possible_ways; wave_propagation(maze, map_of_possible_ways, start_position, finish_position))
	{
		return Path{ path_recovery(maze, map_of_possible_ways, start_position, finish_position) };
	}
	return Path{};
}

bool PathFinder::wave_propagation(const Maze& maze,unordered_map<CellPosition, int>& map_of_possible_ways, const CellPosition& start_position, const CellPosition& finish_position)
{
	deque < pair < CellPosition, int >> cell_deque;
	cell_deque.emplace_back(start_position, 0);

	while (cell_deque.begin() != cell_deque.end() && cell_deque.front().first != finish_position)
	{
		const auto& [position, value] = cell_deque.front();
		for (auto const near_element : maze.get_near_elements( position))
		{
			if (maze.get_cell_type_by_coordinates(near_element) == CellType::empty_space && !map_of_possible_ways.contains(near_element) && near_element!= start_position)
			{
				map_of_possible_ways.insert({ near_element, value+1 });
				cell_deque.emplace_back(near_element, value+1);
			}
		}
		cell_deque.pop_front();
	}

	return !cell_deque.empty() && finish_position == cell_deque.front().first;
}





bool PathFinder::is_elements_near(const Maze& maze, const CellPosition& current_element, const CellPosition& other_element)
{
	auto near_elements = maze.get_near_elements(current_element);
	return (std::find(near_elements.begin(), near_elements.end(), other_element) != near_elements.end());
}


vector <CellPosition> PathFinder::path_recovery(const Maze& maze, const std::unordered_map<CellPosition, int>& map_of_possible_ways, const CellPosition& start_position, const CellPosition& finish_position)
{
	vector <CellPosition> result;
	
	deque <CellPosition> cell_deque;
	cell_deque.push_back(finish_position);
	


	while (!is_elements_near(maze, cell_deque.front(), start_position))
	{
		auto& current_element = cell_deque.front();
		const int current_element_value = map_of_possible_ways.find(current_element)->second;
		for (auto near_element : maze.get_near_elements(current_element))
		{
			if (map_of_possible_ways.contains(near_element) && current_element_value - map_of_possible_ways.find(near_element)->second == 1)
			{
				cell_deque.push_back(near_element);
				result.push_back({ near_element });
				break;
			}
		}
		cell_deque.pop_front();
	}
	return result;
}




