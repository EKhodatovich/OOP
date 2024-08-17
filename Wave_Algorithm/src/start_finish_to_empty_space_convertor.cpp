#include "start_finish_to_empty_space_convertor.hpp"
#include "exceptions.hpp"
CellType StartFinishToEmptySpaceConvertor::front_convert(const char symbol) const
{
	if (!convertible_symbols.contains(symbol))
	{
		throw WrongCellTypeException();
	}
	if (symbol != '1')
	{
		return CellType::empty_space;
	}
	return CellType::wall;
}
