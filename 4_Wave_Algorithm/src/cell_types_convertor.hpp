#pragma once

#include <unordered_set>

#include "cell_type.hpp"


inline std::unordered_set convertible_symbols = { '0','1','2','3' };

class CellTypesConvertor
{
protected:

	CellTypesConvertor() = default;
public:
	
	CellTypesConvertor(CellTypesConvertor&) = default;
	CellTypesConvertor& operator=(const CellTypesConvertor&) = default;
	virtual ~CellTypesConvertor() = default;

	virtual CellType front_convert(const char symbol) const = 0;
};

