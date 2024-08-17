#include "gtest/gtest.h"
#include "maze.hpp"
#include "path_finder.hpp"
#include "parser.hpp"
#include "start_finish_to_empty_space_convertor.hpp"

namespace
{
	const StartFinishToEmptySpaceConvertor convertor;
}
using namespace std;
class PathFinderTests : public ::testing::Test
{
	virtual void SetUp() {

	}
	virtual void TearDown() {

	}
public:
	stringstream line;
	Path result;
};


TEST_F(PathFinderTests, OnlyWallsMaze)
{
	line << "1 1 1\n1 1 1\n1 1 1";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height() );

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(3, 3)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(2, 2)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(0, 0)).get_path().empty());
}
TEST_F(PathFinderTests, OneEmptySpaceMaze)
{
	line << "1 1 1\n1 0 1\n1 1 1";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(3, 3)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(2, 2)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 1)).get_path().empty());
}


TEST_F(PathFinderTests, Maze3_3Num1)
{
	line << "0 0 0\n0 0 0\n0 0 0";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height() );

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 1)).get_path().empty());

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 0)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(0, 1)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 2)).get_path().empty());
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(2, 1)).get_path().empty());

	EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(0, 0)).get_path().size(), 1);
	EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(2, 0)).get_path().size(), 1);
	EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(0, 2)).get_path().size(), 1);
	EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(2, 2)).get_path().size(), 1);

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(3, 3)).get_path().empty());
}

TEST_F(PathFinderTests, Maze3_3Num2)
{
	line << "2 0 0\n0 1 0\n0 3 0";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 1)).get_path().empty());
	for (size_t i =0; i<9; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(i/3, i%3)).get_path().empty());
	}
	for (size_t i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(i / 3, i % 3), CellPosition(1, 1)).get_path().empty());
	}
	for (size_t i = 0; i < 9; ++i)
	{
		if (i !=4 && i!=0)
		{
			EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(i / 3, i % 3)).get_path().size(), i/3+i%3-1);
		}
	}
	const vector result = { CellPosition(0,2), CellPosition(0,1) };
	EXPECT_EQ(PathFinder::find_the_way(maze, cells_table.get_start(), cells_table.get_finish()).get_path(), result);
	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(3, 3)).get_path().empty());
}

TEST_F(PathFinderTests, Maze3_3Num3)
{
	line << "2 1 0\n0 1 0\n3 1 0";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 1)).get_path().empty());
	for (size_t i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, i/3), CellPosition(i / 3, i % 3)).get_path().empty());
	}
	for (size_t i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(i / 3, i % 3), CellPosition(1, i/3)).get_path().empty());
	}

	for (size_t x =0; x<3; ++x)
	{
		for (size_t y = 0; y<3; ++y)
		{
            if (x>0 || (x == 0 && y<2))
			{
				EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(x, y)).get_path().empty());
			}
			else
			{
				EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(x, y)).get_path().size(), 1);
				EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(x, y)).get_path().front(), CellPosition(0, 1));
			}

            if (x < 2 || (x == 2 && y > 0))
			{
				EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(2, 2), CellPosition(x, y)).get_path().empty());
			}
			else
			{
				EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(2, 2), CellPosition(x, y)).get_path().size(), 1);
				EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(2, 2), CellPosition(x, y)).get_path().front(), CellPosition(2, 1));
			}
		}
	}
	EXPECT_EQ(PathFinder::find_the_way(maze, cells_table.get_start(), cells_table.get_finish()).get_path().front(), CellPosition(0,1));
}

TEST_F(PathFinderTests, Maze3_3Num4)
{
	line << "2 1 0\n1 0 0\n0 1 3";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());

	for (size_t i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, cells_table.get_start(), CellPosition(i / 3, i % 3)).get_path().empty());
	}
}

TEST_F(PathFinderTests, Maze3_3Num5)
{
	line << "2 0 0\n0 0 1\n0 1 3";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height());

	for (size_t i = 0; i < 9; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(i/3, i%3), cells_table.get_finish()).get_path().empty());
	}
}

TEST_F(PathFinderTests, Maze4_4_Num1)
{
	line << "2 0 1 3\n0 1 0 0\n0 1 0 1\n0 0 0 0";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height() );

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(1, 1)).get_path().empty());
	for (size_t i = 0; i < 16; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 1), CellPosition(i / 4, i % 4)).get_path().empty());
	}
	for (size_t i = 0; i < 16; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(i / 3, i % 3), CellPosition(3, 2)).get_path().empty());
	}

	for (size_t i = 0; i < 16; ++i)
	{
		if (maze.get_cell_type_by_coordinates(CellPosition(i % 4, i / 4)) == CellType::empty_space && i>1)
		{
			EXPECT_FALSE(PathFinder::find_the_way(maze, CellPosition(1, 0), CellPosition(i % 4, i / 4)).get_path().empty());
			EXPECT_FALSE(PathFinder::find_the_way(maze, CellPosition(i % 4, i / 4), CellPosition(1, 0)).get_path().empty());
		}
		else
		{
			EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 0), CellPosition(i % 4, i / 4)).get_path().empty());
			EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(i % 4, i / 4), CellPosition(1, 0)).get_path().empty());
		}
	}

	result = PathFinder::find_the_way(maze, cells_table.get_finish(), cells_table.get_start());
	EXPECT_EQ(result.get_path().size(), 8);
	vector check_result = {CellPosition(0,1), CellPosition(0,2), CellPosition(0,3), CellPosition(1,3), CellPosition(2,3), CellPosition(2,2), CellPosition(2,1), CellPosition(3,1) };
	EXPECT_EQ(result.get_path(), check_result);

	result = PathFinder::find_the_way(maze, cells_table.get_start(), cells_table.get_finish());
	EXPECT_EQ(result.get_path().size(), 8);
    reverse(check_result.begin(), check_result.end());
	EXPECT_EQ(result.get_path(), check_result);
}

TEST_F(PathFinderTests, Maze4_4_Num2)
{
	line << "3 1 1 1\n1 0 0 1\n1 0 0 1\n1 1 1 2";

	const CellsTable cells_table = Parser::parse(line, convertor);
	const Maze maze(cells_table.get_rows(), cells_table.get_width(), cells_table.get_height() );

	EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(0, 0), CellPosition(0, 0)).get_path().empty());
	for (size_t i = 0; i < 16; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(1, 0), CellPosition(i / 4, i % 4)).get_path().empty());
	}
	for (size_t i = 0; i < 16; ++i)
	{
		EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(i / 3, i % 3), CellPosition(3, 1)).get_path().empty());
	}

	for (size_t y = 0; y<4; y++ )
	{
		for (size_t x = 0; x < 4; x++)
		{
			EXPECT_TRUE(PathFinder::find_the_way(maze, cells_table.get_start(), CellPosition(x,y)).get_path().empty());
			EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(x, y), cells_table.get_finish()).get_path().empty());
			if (x==2 && y ==2 )
			{
				EXPECT_EQ(PathFinder::find_the_way(maze, CellPosition(x, y), CellPosition(1, 1)).get_path().size(), 1);
			}
			else
			{
				EXPECT_TRUE(PathFinder::find_the_way(maze, CellPosition(x, y), CellPosition(1, 1)).get_path().empty());
			}

		}
	}

}




