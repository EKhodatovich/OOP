#include "gtest/gtest.h"
#include "hot_keys_map.hpp"
#include "parser.hpp"
using namespace std;

hot_keys_map default_hot_keys_map()
{
	stringstream ss;
	ss << "Ctrl+C=copy\nCtrl+X=cut\nCtrl+Ins=insert";
	return hot_keys_map{ parser::parse(ss) };
}

namespace
{
    const hot_keys_map default_hot_key_map = default_hot_keys_map();
    const hot_key copy_keys{ {"ctrl", "c"} };
    const hot_key paste_keys{ {"ctrl", "v"} };
    const hot_key insert_keys{ {"shift", "ins"} };
}

class HotKeysMapTests : public ::testing::Test 
{
protected:
	virtual void SetUp()
	{

	}
	virtual void TearDown()
	{
		ss_.clear();
		ss_.sync();
		ss_.ignore(((numeric_limits<streamsize>::max)()));
	}
	stringstream ss_;
};

TEST_F(HotKeysMapTests, OneSimpleCombination)
{
	ss_ << "Ctrl=crouch";
	hot_keys_map result{ parser::parse(ss_) };
	const vector<hot_key> keys{hot_key{ {"ctrl"} }};
	const command commands{ "Crouch" };
	EXPECT_EQ(result.find_hot_keys_by_command(command{ "Crouch" }), keys);
	EXPECT_EQ(result.find_command_by_hot_key(hot_key{ {"ctrl"} }), commands);
	EXPECT_THROW(auto _ = result.find_hot_keys_by_command(command{ "sprint" }), out_of_range);
	EXPECT_THROW(auto _ = result.find_command_by_hot_key(hot_key{ {"shift"} }), out_of_range);

	result.add_key_command_combination(hot_key{ {"shift"} }, command{ "sprint" });

	vector<hot_key> shift = { {hot_key{ {"shift"} }} };

	EXPECT_EQ(result.find_hot_keys_by_command(command{ "sprint" }), shift);
	EXPECT_EQ(result.find_command_by_hot_key(hot_key{ {"shift"} }), command{ "sprint" });

	result.add_key_command_combination(hot_key{ {"space"} }, command{ "jump" });
	result.remove_command(command{ "jump" });
	result.remove_hot_key(hot_key{ {"shift"} });

	EXPECT_THROW(result.remove_hot_key(hot_key{ {"space"} }), out_of_range);
	EXPECT_THROW(result.remove_command(command{ "sprint"}), out_of_range);

	EXPECT_THROW(auto _ = result.find_hot_keys_by_command(command{ "sprint" }), out_of_range);
	EXPECT_THROW(auto _ = result.find_command_by_hot_key(hot_key{ {"shift"} }), out_of_range);

	conflicts conflicts = result.merge(default_hot_key_map);
	EXPECT_TRUE(conflicts.get_vector_of_conflicts().empty());

	EXPECT_EQ(result.find_hot_keys_by_command(command{ "Crouch" }), keys);
	EXPECT_EQ(result.find_command_by_hot_key(hot_key{ {"ctrl"} }), commands);

	vector<hot_key> copy_key = { copy_keys };

	EXPECT_EQ(result.find_hot_keys_by_command(command{ "copy" }), copy_key);
	EXPECT_EQ(result.find_command_by_hot_key(hot_key{ {"ctrl", "x"}}), command{"cut"});

	result.clear();
	EXPECT_THROW(result.remove_hot_key(hot_key{ {"ctrl", "c"}}), out_of_range);
	EXPECT_THROW(result.remove_command(command{ "crouch" }), out_of_range);
}

TEST_F(HotKeysMapTests, ComplexCombination)
{
	ss_ << "Ctrl+Alt+Del=reset\nCtrl+C=copy\nCtrl+Ins=copy\nCtrl+C=paste\nShift+Ins=paste\nCtrl+X=cut\nShift+Del=cut\nF1=help";
	hot_keys_map result{ parser::parse(ss_) };
	const vector<hot_key> keys{ hot_key{ {"alt", "ctrl", "del"}}, hot_key{{"ctrl", "c"}}, hot_key{{"ctrl", "ins"}} ,hot_key{{"ins", "shift"}}, hot_key{{"ctrl", "x"}},hot_key{{"del", "shift"}}, hot_key{{"f1"}} };
	const vector commands{ "reset", "copy", "copy", "paste", "cut", "cut", "help" };

	for (const auto& key : keys)
	{
		EXPECT_NO_THROW(auto _ = result.find_command_by_hot_key(key).get_command_string());
	}

	hot_key find_hot_key1{ {"Ctrl", "F"} };
	hot_key find_hot_key2{ {"Ctrl", "N"} };
    vector<hot_key> find_hot_keys = { find_hot_key2, find_hot_key1 };
	result.add_key_command_combination(find_hot_key1, command{ "find" });

    vector<hot_key> find_hot_key1_vector = { hot_key{{"Ctrl", "F"}} };
    vector<hot_key> find_hot_key2_vector = { hot_key{{"Ctrl", "N"}} };


    EXPECT_EQ(result.find_hot_keys_by_command(command{ "find" }), find_hot_key1_vector);
	EXPECT_EQ(result.find_command_by_hot_key(find_hot_key1), command{ "find" });

    result.add_key_command_combination(find_hot_key1, command{ "replace" });
    EXPECT_EQ(result.find_hot_keys_by_command(command{ "find" }), find_hot_key1_vector);
	EXPECT_EQ(result.find_command_by_hot_key(find_hot_key1), command{ "find" });

    result.add_key_command_combination(find_hot_key2, command{ "find" });
    EXPECT_EQ(result.find_hot_keys_by_command(command{ "find" }), find_hot_keys);
	EXPECT_EQ(result.find_command_by_hot_key(find_hot_key1), command{ "find" });
	EXPECT_EQ(result.find_command_by_hot_key(find_hot_key2), command{ "find" });


	result.remove_hot_key(hot_key{ {"Ctrl", "C"} });
	result.remove_hot_key(hot_key{ {"Shift", "Ins"} });


	vector<hot_key> copy = { hot_key { {"ctrl", "ins"} } };
	EXPECT_EQ(result.find_hot_keys_by_command(command{ "copy" }), copy);
	EXPECT_THROW(auto _ = result.find_command_by_hot_key(copy_keys), out_of_range);
	EXPECT_THROW(result.remove_hot_key(hot_key{ {"Ctrl", "T"} }), out_of_range);

	conflicts conflicts = result.merge(default_hot_key_map);
	EXPECT_EQ(conflicts.get_vector_of_conflicts().size(), 1);
	hot_key copy_key = hot_key{ {"ctrl", "ins"} };
	EXPECT_EQ(conflicts.get_vector_of_conflicts().front(), copy_key);
	
	result.clear();
}
