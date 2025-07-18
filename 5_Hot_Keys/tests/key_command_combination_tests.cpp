#include "gtest/gtest.h"
#include "key_command_combination.hpp"

TEST(KeyCommandTests, Num1)
{
	const hot_key key{ {"Ctrl"} };
	const hot_key low_key{ {"ctrl"} };
	const command com{ "copy" };
	const key_command_combination result{ key, com};
	EXPECT_EQ(result.get_hot_key(), key);
	EXPECT_EQ(result.get_command(), com);
}

TEST(KeyCommandTests, Num2)
{
	const hot_key key{ {"Ctrl", "C"} };
	const hot_key low_key{ {"ctrl", "c"}};
	const command com{ "copy" };
	const key_command_combination result{ key, com };
	EXPECT_EQ(result.get_hot_key(), key);
	EXPECT_EQ(result.get_command(), com);
}