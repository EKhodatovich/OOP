#include "start_finish_to_wall_convertor.hpp"
#include "exceptions.hpp"
CellType StartFinishToWallConvertor::front_convert(const char symbol) const
{
	if (!convertible_symbols.contains(symbol))
	{
		throw WrongCellTypeException();
	}
	if (symbol != '0')
	{
		return CellType::wall;
	}
	return CellType::empty_space;
}
