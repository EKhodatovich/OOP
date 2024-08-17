#pragma once

#include "cells_table.hpp"
#include "cell_types_convertor.hpp"
#include <istream>

class Parser  final
{
public:
	Parser() = delete;
	static CellsTable parse(std::istream& is, const CellTypesConvertor& ctc);
};
