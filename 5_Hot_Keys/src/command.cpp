#include "command.hpp"
#include "string_to_lowercase.hpp"
using namespace std;

command::command(const string& command_string) : command_string_(command_string)
{

	check_string_for_spaces_and_lower_symbols(command_string_);
}
