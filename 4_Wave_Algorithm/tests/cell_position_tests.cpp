#include "gtest/gtest.h"
#include "cell_position.hpp"
#include "gtest/gtest.h"
namespace
{
	constexpr CellPosition empty_position{};
}
TEST(CellPositionTest, DefaultPosition)
{
	EXPECT_EQ(empty_position.get_x(), 0);
	EXPECT_EQ(empty_position.get_y(), 0);
}

TEST(CellPositionTest, Zero_Zero_Position)
{
	const CellPosition position{ 0,0 };
	EXPECT_EQ(position.get_x(), 0);
	EXPECT_EQ(position.get_y(), 0);
	EXPECT_EQ(position, empty_position);
}

TEST(CellPositionTest, One_One_Position)
{
	const CellPosition position{ 1,1 };
	EXPECT_EQ(position.get_x(), 1);
	EXPECT_EQ(position.get_y(), 1);
	EXPECT_NE(position, empty_position);
}
TEST(CellPositionTest, One_Zero_Position)
{
	const CellPosition position{ 1,0 };
	EXPECT_EQ(position.get_x(), 1);
	EXPECT_EQ(position.get_y(), 0);
	EXPECT_NE(position, empty_position);
	EXPECT_NE(position, CellPosition(0, 128));
}
TEST(CellPositionTest, Ten_Ten_Position)
{
	const CellPosition position{ 10,10 };
	EXPECT_EQ(position.get_x(), 10);
	EXPECT_EQ(position.get_y(), 10);
	EXPECT_NE(position, empty_position);
}
TEST(CellPositionTest, 1_1K_Position)
{
	const CellPosition position{ 1,1000 };
	EXPECT_EQ(position.get_x(), 1);
	EXPECT_EQ(position.get_y(), 1000);
	EXPECT_NE(position, empty_position);
	EXPECT_NE(position, CellPosition( 2,872 ));
}
