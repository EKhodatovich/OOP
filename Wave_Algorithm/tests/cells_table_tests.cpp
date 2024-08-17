#include "gtest/gtest.h"
#include "cells_table.hpp"
#include "exceptions.hpp"

TEST(CellsTableTests, DefaultTable)
{
	const CellsTable cells_table{};
	EXPECT_EQ(cells_table.get_start().get_x(), 0);
	EXPECT_EQ(cells_table.get_start().get_y(), 0);
	EXPECT_EQ(cells_table.get_finish().get_x(), 0);
	EXPECT_EQ(cells_table.get_finish().get_y(), 0);
	EXPECT_EQ(cells_table.get_start(), cells_table.get_finish());
	EXPECT_EQ(cells_table.get_width(), 0);
	EXPECT_EQ(cells_table.get_height(), 0);
	EXPECT_EQ(cells_table.get_rows().size(), 0);
}

TEST(CellsTableTests, EmptyTable)
{
	const std::vector<CellType> vector;
	const CellsTable cells_table{ vector, 0,0, {0,0}, {0,0} };
	EXPECT_EQ(cells_table.get_start().get_x(), 0);
	EXPECT_EQ(cells_table.get_start().get_y(), 0);
	EXPECT_EQ(cells_table.get_finish().get_x(), 0);
	EXPECT_EQ(cells_table.get_finish().get_y(), 0);
	EXPECT_EQ(cells_table.get_start(), cells_table.get_finish());
	EXPECT_EQ(cells_table.get_width(), 0);
	EXPECT_EQ(cells_table.get_height(), 0);
	EXPECT_EQ(cells_table.get_rows().size(), 0);
}

TEST(CellsTableTests, WrongSizeTable1)
{
	const std::vector vector = {CellType::empty_space, CellType::empty_space, CellType::wall };
	EXPECT_THROW(const CellsTable cells_table(vector, 1, 2, { 0,0 }, { 0,0 }), DifferentSizesException);
}

TEST(CellsTableTests, WrongSizeTable2)
{
	const std::vector<CellType> vector;
	EXPECT_THROW(const CellsTable cells_table(vector, 1, 2, { 0,0 }, { 0,0 }), DifferentSizesException);
}

TEST(CellsTableTests, WrongSizeTable3)
{
	const std::vector vector = { CellType::empty_space, CellType::empty_space, CellType::wall };
	EXPECT_THROW(const CellsTable cells_table(vector, 0, 0, { 0,0 }, { 0,0 }), DifferentSizesException);
}

TEST(CellsTableTests, WrongStartPos)
{
	const std::vector vector = {CellType::empty_space};
	EXPECT_THROW(const CellsTable cells_table(vector, 1, 1, { 2,0 }, { 0,0 }), WrongStartPosition);
}
TEST(CellsTableTests, WrongFinishPos)
{
	const std::vector vector = { CellType::empty_space };
	EXPECT_THROW(const CellsTable cells_table(vector, 1, 1, { 0,0 }, { 2,0 }), WrongFinishPosition);
}

TEST(CellsTableTests, NormalTable1)
{
	const std::vector vector = { CellType::empty_space };
	const CellsTable cells_table(vector, 1, 1, { 0,0 }, { 0,0 });
	EXPECT_EQ(cells_table.get_start().get_x(), 0);
	EXPECT_EQ(cells_table.get_start().get_y(), 0);
	EXPECT_EQ(cells_table.get_finish().get_x(), 0);
	EXPECT_EQ(cells_table.get_finish().get_y(), 0);
	EXPECT_EQ(cells_table.get_start(), cells_table.get_finish());
	EXPECT_EQ(cells_table.get_width(), 1);
	EXPECT_EQ(cells_table.get_height(), 1);
	EXPECT_EQ(cells_table.get_rows().size(), 1);
}

TEST(CellsTableTests, NormalTable2)
{
	const std::vector vector = { CellType::empty_space, CellType::empty_space, CellType::wall, CellType::wall };
	CellsTable cells_table(vector, 1, 4, { 0,0 }, { 0,3 });
	EXPECT_EQ(cells_table.get_start().get_x(), 0);
	EXPECT_EQ(cells_table.get_start().get_y(), 0);
	EXPECT_EQ(cells_table.get_finish().get_x(), 0);
	EXPECT_EQ(cells_table.get_finish().get_y(), 3);
	EXPECT_NE(cells_table.get_start(), cells_table.get_finish());
	EXPECT_EQ(cells_table.get_width(), 1);
	EXPECT_EQ(cells_table.get_height(), 4);
	EXPECT_EQ(cells_table.get_rows().size(), 4);

	cells_table = CellsTable(vector, 2, 2, {0,0}, {1,1});
	EXPECT_EQ(cells_table.get_start().get_x(), 0);
	EXPECT_EQ(cells_table.get_start().get_y(), 0);
	EXPECT_EQ(cells_table.get_finish().get_x(), 1);
	EXPECT_EQ(cells_table.get_finish().get_y(), 1);
	EXPECT_NE(cells_table.get_start(), cells_table.get_finish());
	EXPECT_EQ(cells_table.get_width(), 2);
	EXPECT_EQ(cells_table.get_height(), 2);
	EXPECT_EQ(cells_table.get_rows().size(), 4);
}


