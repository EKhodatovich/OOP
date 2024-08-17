#include <cassert>
#include "parser.hpp"
#include "start_finish_to_empty_space_convertor.hpp"
#include "maze.hpp"
#include "path_finder.hpp"

#include <sstream>
using namespace std;

int main()
{
	const StartFinishToEmptySpaceConvertor convertor;
	stringstream iss;
	iss << "2 1 0 0 0\n0 1 0 1 0\n0 1 0 1 0\n0 1 0 1 0\n0 0 0 1 3 ";
	const CellsTable cells_table = Parser::parse(iss, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	
	const Path path = PathFinder::find_the_way(maze, cells_table.get_start(), cells_table.get_finish());
	assert(path.get_path().size() == 15);
	return 0;
}
