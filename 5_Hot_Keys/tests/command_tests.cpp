#include <gtest/gtest.h>
#include "command.hpp"
#include "exceptions.hpp"
using namespace std;


TEST(CommandTests, EmptyCommandNum1)
{
	const string combination_set ;
	EXPECT_THROW(command{ combination_set }, empty_string);
}

TEST(CommandTests, EmptyCommandNum2)
{
    const string combination_set ;
	EXPECT_THROW(command{ combination_set }, empty_string);
}

TEST(CommandTests, EmptyCommandNum3)
{
	const string combination_set  =  "   ";
	EXPECT_THROW(command{ combination_set }, string_with_spaces);
}

TEST(CommandTests, OKCommandNum1)
{
	const string combination_set  = "ctrl";
	const command result{ combination_set };
	EXPECT_EQ(result.get_command_string(), combination_set);
}
TEST(CommandTests, OKCommandNum2)
{
	const string combination_set = "Ctrl";
	const string real_combination_set = "ctrl";
	const command result{ combination_set };
	EXPECT_EQ(result.get_command_string(), real_combination_set);
}

TEST(CommandTests, BadCommandNum1)
{
	const string combination_set  = "  Ctrl  ";
	EXPECT_THROW(command { combination_set }, string_with_spaces);
}
TEST(CommandTests, BadCommandNum2)
{
	const string combination_set = "Ct  rl";
	EXPECT_THROW(command{ combination_set }, string_with_spaces);
}
