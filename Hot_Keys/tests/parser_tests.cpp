#include "gtest/gtest.h"
#include "parser.hpp"
#include "exceptions.hpp"
using namespace std;

class ParserTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		
	}
	virtual void TearDown()
	{
		ss.clear();
		ss.sync();
		ss.ignore(((numeric_limits<streamsize>::max)()));
	}
	stringstream ss;
};

TEST_F(ParserTests, EmptyStreamNum1)
{
	EXPECT_TRUE(parser::parse(ss).empty());
}
TEST_F(ParserTests, EmptyStreamNum2)
{
	ss << "";
	EXPECT_TRUE(parser::parse(ss).empty());
}
TEST_F(ParserTests, WhiteSpaceStream)
{
	ss << "   ";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}
TEST_F(ParserTests, WhiteSpaceStreamWithKeyDelimeter)
{
	ss << "  +  ";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}
TEST_F(ParserTests, WhiteSpaceStreamWithKeyCommandDelimeter)
{
	ss << " = ";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}
TEST_F(ParserTests, WhiteKey)
{
	ss << "   = copy";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}
TEST_F(ParserTests, WhiteCommandNum1)
{
	ss << "Ctrl =  ";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}
TEST_F(ParserTests, WhiteCommandNum2)
{
	ss << "Ctrl+C =  ";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}
TEST_F(ParserTests, WhiteCommandNum3)
{
	ss << "Ctrl+C+ =  ";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}

TEST_F(ParserTests, OneSimpleCombinationNum1)
{
	ss << "Ctrl = copy";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}

TEST_F(ParserTests, OneSimpleCombinationNum2)
{
	ss << "Ctrl=copy";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(*result.front().get_hot_key().begin(), "ctrl");
	EXPECT_EQ(result.front().get_command().get_command_string(), "copy");
}
TEST_F(ParserTests, OneSimpleCombinationNum3)
{
	ss << "Ctrl   = c  opy";
	EXPECT_THROW(auto _ = parser::parse(ss), string_with_spaces);
}

TEST_F(ParserTests, OneComplexCombinationNum1)
{
	ss << "Ctrl+c=copy";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 1);

	EXPECT_EQ(*result.front().get_hot_key().begin(), "ctrl");
	EXPECT_EQ(*(++result.front().get_hot_key().begin()), "c");
	EXPECT_EQ(++++result.front().get_hot_key().begin(), result.front().get_hot_key().end());
	EXPECT_EQ(result.front().get_command().get_command_string(), "copy");
}
TEST_F(ParserTests, OneComplexCombinationNum2)
{
	ss << "Ctrl+c+inS=copy";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 1);
	const vector keys = { "ctrl", "c", "ins" };
	size_t i = 0;
	for (auto key = result.front().get_hot_key().begin(); key!= result.front().get_hot_key().end(); ++key)
	{
		EXPECT_EQ(*key, keys[i]);
		++i;
	}
	EXPECT_EQ(result.front().get_command().get_command_string(), "copy");
}
TEST_F(ParserTests, OneComplexCombinationNum3)
{
	ss << "Ctrl+c+inS=copy";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 1);

	const vector keys = { "ctrl", "c", "ins" };
	size_t i = 0;
	for (auto key = result.front().get_hot_key().begin(); key != result.front().get_hot_key().end(); ++key)
	{
		EXPECT_EQ(*key, keys[i]);
		++i;
	}
	EXPECT_EQ(result.front().get_command().get_command_string(), "copy");
}

TEST_F(ParserTests, TwoSimpleCombinations)
{
	ss << "Ctrl=copy\nShift=paste";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 2);

	const vector keys = {"ctrl", "shift"};
	const vector commands = { "copy", "paste" };
	size_t i = 0;
	for (const auto& combination : result)
	{
		EXPECT_EQ(*combination.get_hot_key().begin(), keys[i]);
		EXPECT_EQ(combination.get_command().get_command_string(), commands[i]);
		++i;
	}
}

TEST_F(ParserTests, TwoComplexCombinations)
{
	ss << "Ctrl+c=copy\nCtrl+v=paste";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 2);

	const vector<unordered_set<string>> keys = { {"ctrl", "c"}, {"ctrl", "v"}};
	const vector commands = { "copy", "paste" };
	size_t i = 0;
	for (const auto& combination : result)
	{
		EXPECT_EQ(combination.get_command().get_command_string(), commands[i]);
		++i;
	}
}

TEST_F(ParserTests, FiveComplexCombinations)
{
	ss << "Ctrl+c=copy\nCtrl+v=paste\nShift+Ins=insert\nF1=help\nCtrl+Alt+deL=Command_String";
	const auto result = parser::parse(ss);
	EXPECT_EQ(result.size(), 5);

	const vector<unordered_set<string>> keys = { {"ctrl", "c"}, {"ctrl", "v"}, {"shift", "ins"}, {"f1"}, {"ctrl", "alt", "del"}};
	const vector commands = { "copy", "paste", "insert", "help", "command_string"};
	size_t i = 0;
	for (const auto& combination : result)
	{
		EXPECT_EQ(combination.get_command().get_command_string(), commands[i]);
		++i;
	}
}
