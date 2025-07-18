#pragma once

#include "cell_types_convertor.hpp"

class StartFinishToEmptySpaceConvertor final : public CellTypesConvertor 
{
public:
	CellType front_convert(const char symbol) const override;
};