#include <gtest/gtest.h>
#include "hot_key.hpp"
#include "exceptions.hpp"
using namespace std; 


TEST(HotKeyTests, EmptyHotKeyNum1)
{
	const unordered_set<string> combination_set;
	EXPECT_THROW(hot_key{ combination_set }, empty_string);
}

TEST(HotKeyTests, EmptyHotKeyNum2)
{
	const unordered_set<string> combination_set = { "" };
	EXPECT_THROW(hot_key{ combination_set }, empty_string);
}

TEST(HotKeyTests, EmptyHotKeyNum3)
{
	const unordered_set<string> combination_set = { "   " };
	EXPECT_THROW(hot_key{ combination_set }, string_with_spaces);
}
TEST(HotKeyTests, EmptyHotKeyNum4)
{
	const unordered_set<string> combination_set = { " ", "  " };
	EXPECT_THROW(hot_key{ combination_set }, string_with_spaces);
}
TEST(HotKeyTests, EmptyHotKeyNum5)
{
	const unordered_set<string> combination_set = { "Ctrl", "  "};
	EXPECT_THROW(hot_key{ combination_set }, string_with_spaces);
}

TEST(HotKeyTests, OKHotKeyNum1)
{
	const unordered_set<string> combination_set = { "Ctrl" };
	const hot_key result{ combination_set };
	EXPECT_EQ(*result.begin(), "ctrl");
}

TEST(HotKeyTests, OKHotKeyNum2)
{
	const unordered_set<string> combination_set = { "Ctrl", "F1"};
	const hot_key result{ combination_set };
	const unordered_set<string> normal_combination_set= { "ctrl", "f1" };
	EXPECT_EQ(*result.begin(), "ctrl");
	EXPECT_EQ(*(++result.begin()), "f1");
}
TEST(HotKeyTests, BadHotKeyNum1)
{
	const unordered_set<string> combination_set = { "Ctrl ", "F 1" };
	EXPECT_THROW(hot_key{ combination_set }, string_with_spaces);
}

TEST(HotKeyTests, BadHotKeyNum2)
{
	const unordered_set<string> combination_set = { "  Ctrl ", "F1" };
	EXPECT_THROW(hot_key{ combination_set }, string_with_spaces);
}
TEST(HotKeyTests, BadHotKeyNum3)
{
	const unordered_set<string> combination_set = { "Ct rl", "F1" };
	EXPECT_THROW(hot_key{ combination_set }, string_with_spaces);
}