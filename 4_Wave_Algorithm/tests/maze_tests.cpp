#include "gtest/gtest.h"

#include "parser.hpp"
#include "exceptions.hpp"
#include "start_finish_to_empty_space_convertor.hpp"

#include "maze.hpp"


using namespace std;

namespace
{
	const StartFinishToEmptySpaceConvertor convertor;
}

class MazeTests : public ::testing::Test {
	virtual void SetUp() {
		
	}
	virtual void TearDown() {
	}
public:
	stringstream line;
};

vector <char> row_from_line(const string& line)
{
	vector<char> line_numbers;
	for (auto it : line)
	{
		line_numbers.push_back(it);
	}
	return line_numbers;
}


TEST_F(MazeTests, EmptyRows)
{
	const CellsTable cells_table{};
	EXPECT_THROW(const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height()), EmptyMazeException);
}

TEST_F(MazeTests, Row)
{
	line << "1111";
	const CellsTable cells_table = Parser::parse(line, convertor);

	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	EXPECT_EQ(maze.get_width(), 4);
	EXPECT_EQ(maze.get_height(), 1);
	for (size_t i = 0; i < 4; i++)
	{
		EXPECT_EQ(maze.get_cell_type_by_coordinates(CellPosition{ i,0}), CellType::wall);
	}
	vector result = { CellPosition{0,0}, CellPosition{2,0} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(1, 0)), result);
	result = { CellPosition{1,0}};
	EXPECT_EQ(maze.get_near_elements(CellPosition(0,0)), result);
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(1, 0)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(1, 1)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(4, 0)));
}
TEST_F(MazeTests, Column)
{
	line << "1\n1\n1\n1";
	const CellsTable cells_table = Parser::parse(line, convertor);

	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	EXPECT_EQ(maze.get_width(), 1);
	EXPECT_EQ(maze.get_height(), 4);
	for (size_t i = 0; i < 4; i++)
	{
		EXPECT_EQ(maze.get_cell_type_by_coordinates(CellPosition{ 0,i }), CellType::wall);
	}
	vector result = { CellPosition{0,0}, CellPosition{0,2} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(0, 1)), result);
	result = { CellPosition{0,1} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(0, 0)), result);
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(0, 3)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(1, 1)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(0, 4)));
}
TEST_F(MazeTests, Table2_2)
{
	line << "11\n11";
	const CellsTable cells_table = Parser::parse(line, convertor);

	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	EXPECT_EQ(maze.get_width(), 2);
	EXPECT_EQ(maze.get_height(), 2);
	for (size_t i = 0; i < 4; i++)
	{
		EXPECT_EQ(maze.get_cell_type_by_coordinates(CellPosition{ i % 2,i / 2 }), CellType::wall);
	}
	vector result = { CellPosition{0,1}, CellPosition{1,0} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(0, 0)), result);
	result = { CellPosition{1,0}, CellPosition{0,1} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(1, 1)), result);
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(1, 1)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(3, 3)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(1, 3)));
}

TEST_F(MazeTests, WallsTable)
{
	line << "111\n111\n111";
	const CellsTable cells_table =Parser::parse(line, convertor );

	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	EXPECT_EQ(maze.get_width(), 3);
	EXPECT_EQ(maze.get_height(), 3);
	for (size_t i = 0; i<9; i++)
	{
		EXPECT_EQ(maze.get_cell_type_by_coordinates(CellPosition{ i%3,i/3 }), CellType::wall);
	}
	vector result = { CellPosition{0,1}, CellPosition{1,0} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(0, 0)), result);
	result = { CellPosition{1,0}, CellPosition{0,1}, CellPosition{1,2}, CellPosition{2,1} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(1, 1)), result);
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(1, 1)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(3, 3)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(1, 3)));
}

TEST_F(MazeTests, EmptySpaceTable)
{
	line << "000\n000\n000";
	const CellsTable cells_table = Parser::parse(line, convertor);

	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	EXPECT_EQ(maze.get_width(), 3);
	EXPECT_EQ(maze.get_height(), 3);
	for (size_t i = 0; i < 9; i++)
	{
		EXPECT_EQ(maze.get_cell_type_by_coordinates(CellPosition{ i % 3,i / 3 }), CellType::empty_space);
	}
	vector result = { CellPosition{0,1}, CellPosition{1,0} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(0, 0)), result);
	result = { CellPosition{1,0}, CellPosition{0,1}, CellPosition{1,2}, CellPosition{2,1} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(1, 1)), result);
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(1, 1)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(3, 3)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(1, 3)));
}

TEST_F(MazeTests, 10_10_Table)
{
	for (size_t i = 0; i<10; ++i)
	{
		line << (i%2 ==0 ? "1010101010\n" : "0101010101\n");
	}
	const CellsTable cells_table = Parser::parse(line, convertor);

	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());
	EXPECT_EQ(maze.get_width(), 10);
	EXPECT_EQ(maze.get_height(), 10);
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			EXPECT_EQ(maze.get_cell_type_by_coordinates(CellPosition{ x, y}), (y%2 == 0 && x%2==0) || (y % 2 != 0 && x % 2 != 0) ? CellType::wall : CellType::empty_space);
		}
	}
	vector result = { CellPosition{0,1}, CellPosition{1,0} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(0, 0)), result);
	result = { CellPosition{1,0}, CellPosition{0,1}, CellPosition{1,2}, CellPosition{2,1} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(1, 1)), result);
	result = { CellPosition{6,5}, CellPosition{5,6}, CellPosition{6,7}, CellPosition{7,6} };
	EXPECT_EQ(maze.get_near_elements(CellPosition(6, 6)), result);
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(1, 1)));
	EXPECT_TRUE(maze.cell_in_maze(CellPosition(3, 3)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(11, 3)));
	EXPECT_FALSE(maze.cell_in_maze(CellPosition(10, 10)));
}