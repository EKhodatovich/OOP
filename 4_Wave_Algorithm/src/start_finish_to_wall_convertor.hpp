#pragma once

#include "cell_types_convertor.hpp"

class StartFinishToWallConvertor final : public CellTypesConvertor
{
public:
	CellType front_convert(const char symbol) const override;
};