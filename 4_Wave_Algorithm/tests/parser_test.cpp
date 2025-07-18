#include "gtest/gtest.h"
#include "parser.hpp"

#include "start_finish_to_empty_space_convertor.hpp"
#include "start_finish_to_wall_convertor.hpp"
#include "exceptions.hpp"

#include <vector>

namespace
{
	StartFinishToEmptySpaceConvertor convertor;
	StartFinishToWallConvertor other_convertor;
}

class ParserTests : public ::testing::Test {
	virtual void SetUp(){
	}
	virtual void TearDown() {
	}
public:
	std::stringstream is;
};


TEST_F(ParserTests, EmptyStream)
{
	const CellsTable result = Parser::parse(is, convertor);
	EXPECT_EQ(result.get_rows().begin(), result.get_rows().end());
	EXPECT_EQ(result.get_width(), 0);
	EXPECT_EQ(result.get_height(), 0);

}
TEST_F(ParserTests, EmptyString)
{
	is << "";
	const CellsTable result = Parser::parse(is, convertor);
	EXPECT_EQ(result.get_rows().begin(), result.get_rows().end());
	EXPECT_EQ(result.get_width(), 0);
	EXPECT_EQ(result.get_height(), 0);
}
TEST_F(ParserTests, WhiteSpaceString)
{
	is << "     ";
	EXPECT_THROW(Parser::parse(is, convertor), EmptyStringException);

}
TEST_F(ParserTests, SomeWhiteSpaceStrings)
{
	is << "     \n       \n        ";
	EXPECT_THROW(Parser::parse(is, convertor), EmptyStringException);
}
TEST_F(ParserTests, OneLetterStrings)
{
	is << "1\n1\n1";
	const CellsTable result = Parser::parse(is, convertor);
	EXPECT_EQ(result.get_width(), 1);
	EXPECT_EQ(result.get_height(), 3);
	for (auto& it : result.get_rows())
	{
		EXPECT_EQ(it, CellType::wall);
	}
}
TEST_F(ParserTests, SomeLettersStrings)
{
	is << "011\n101\n110";
	const CellsTable result = Parser::parse(is, convertor);
	EXPECT_EQ(result.get_width(), 3);
	EXPECT_EQ(result.get_height(), 3);
	const std::vector check_result = { CellType::empty_space, CellType::wall,CellType::wall, CellType::wall, CellType::empty_space, CellType::wall, CellType::wall, CellType::wall, CellType::empty_space };
	EXPECT_EQ(result.get_rows(), check_result);
}
TEST_F(ParserTests, SomeLettersAndWhiteSpaceStrings)
{
	is << "0  1  1\n1 0 1\n   11  0";
	const CellsTable result = Parser::parse(is, convertor);
	EXPECT_EQ(result.get_width(), 3);
	EXPECT_EQ(result.get_height(), 3);
	const std::vector check_result = { CellType::empty_space, CellType::wall,CellType::wall, CellType::wall, CellType::empty_space, CellType::wall, CellType::wall, CellType::wall, CellType::empty_space };
	EXPECT_EQ(result.get_rows(), check_result);
}

TEST_F(ParserTests, FullStrings)
{
	is << "1111\n1201\n1031\n1111";
	const CellsTable result = Parser::parse(is, convertor);
	EXPECT_EQ(result.get_width(), 4);
	EXPECT_EQ(result.get_height(), 4);
	EXPECT_EQ(result.get_rows()[5], CellType::empty_space);
	EXPECT_EQ(result.get_rows()[2], CellType::wall);
	EXPECT_EQ(result.get_rows()[9], CellType::empty_space);
	EXPECT_EQ(result.get_rows()[10], CellType::empty_space);
}

TEST_F(ParserTests, WrongTypesStrings)
{
	is << "1111\n1201\n1031\n1411";
	EXPECT_THROW(const CellsTable result = Parser::parse(is, convertor), WrongCellTypeException);
}


TEST_F(ParserTests, FullStringsToWall)
{
	is << "1111\n1201\n1031\n1111";
	const CellsTable result = Parser::parse(is, other_convertor);
	EXPECT_EQ(result.get_width(), 4);
	EXPECT_EQ(result.get_height(), 4);
	EXPECT_EQ(result.get_rows()[5], CellType::wall);
	EXPECT_EQ(result.get_rows()[2], CellType::wall);
	EXPECT_EQ(result.get_rows()[9], CellType::empty_space);
	EXPECT_EQ(result.get_rows()[10], CellType::wall);
}

TEST_F(ParserTests, WrongTypesStringsToWall)
{
	is << "1111\n1201\n1031\n1411";
	EXPECT_THROW(const CellsTable result = Parser::parse(is, other_convertor), WrongCellTypeException);
}

