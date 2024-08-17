#include "gtest/gtest.h"
#include "start_finish_to_empty_space_convertor.hpp"
#include "start_finish_to_wall_convertor.hpp"
#include "exceptions.hpp"

TEST(CellTypeConvertorTests, ToEmptySpace)
{
	const StartFinishToEmptySpaceConvertor convertor{};
	const std::vector vector = { '1', '2', '3','0' };
	std::vector<CellType> result;
	for (const auto it: vector)
	{
		result.push_back(convertor.front_convert(it));
	}
	const std::vector resulted = { CellType::wall, CellType::empty_space, CellType::empty_space, CellType::empty_space };
	EXPECT_EQ(result, resulted);
	EXPECT_THROW(convertor.front_convert({ '4' }), WrongCellTypeException);
}

TEST(CellTypeConvertorTests, ToWall)
{
	const StartFinishToWallConvertor convertor{};
	const std::vector vector = { '1', '2', '3','0' };
	std::vector<CellType> result;
	for (const auto it : vector)
	{
		result.push_back(convertor.front_convert(it));
	}
	const std::vector resulted = { CellType::wall, CellType::wall, CellType::wall, CellType::empty_space };
	EXPECT_EQ(result, resulted);
	EXPECT_THROW(convertor.front_convert({ '4' }), WrongCellTypeException);
}


