#include "parser.hpp"
#include "hot_keys_map.hpp"
#include "writer.hpp"
#include <fstream>

using namespace std;

class wrong_file_name : public exception
{
    [[nodiscard]] char const* what() const noexcept override { return "Cannot open file"; }
};

int main(int argc, char** argv)
{
	ifstream ifs;
	ofstream ofs;
	if (argc == 2)
	{
		ifs.open(argv[0], ifstream::in);
		ofs.open(argv[1], ofstream::out);
	}
	else
	{
		ifs.open("first_list.txt", ifstream::in);
		ofs.open("second_list.txt", ofstream::out);
	}

	if (!ifs.is_open() || !ofs.is_open())
	{
		throw wrong_file_name();
	}
	const vector<key_command_combination> vector_of_key_command_strings = parser::parse(ifs);
	hot_keys_map map(vector_of_key_command_strings);

	ofs << "first map\n";
	writer::write_map(map, ofs);

	string tmp = map.find_command_by_hot_key(vector_of_key_command_strings[2].get_hot_key()).get_command_string();


	map.add_key_command_combination(hot_key{ {"Ctrl", "F"} }, command{ "find" });
	map.add_key_command_combination(hot_key{ {"Ctrl", "F"} }, command{ "replace" });
	map.add_key_command_combination(hot_key{ {"Ctrl", "N"} }, command{ "find" });
	map.add_key_command_combination(hot_key{ {"Ctrl", "G"} }, command{ "replace" });

	map.remove_hot_key(hot_key{ {"Ctrl", "C"} });
	map.remove_hot_key(hot_key{ {"Shift", "Ins"} });
	try
	{
		map.remove_hot_key(hot_key{ {"Ctrl", "T"} });
	}
	catch (out_of_range&) {}

	auto tmp2 = map.find_hot_keys_by_command(command{ "copy" });
	tmp2 = map.find_hot_keys_by_command(command{ "cut" });
	try
	{
		tmp2 = map.find_hot_keys_by_command(command{ "delete" });
	}
	catch (out_of_range&) {}

	ofs << "\n\nafter transformations\n";
	writer::write_map(map, ofs);


	hot_keys_map map2{ vector_of_key_command_strings };
	map2.add_key_command_combination(hot_key{ {"Ctrl", "N"} }, command{ "beat" });

	ofs << "\n\nsecond map\n";
	writer::write_map(map2, ofs);


	conflicts result = map.merge(map2);

	ofs << "\n\nafter merge\n";
	writer::write_conflicts(result, ofs);
	writer::write_map(map, ofs);
	
	map.clear();
	map2.clear();


	return 0;
}
