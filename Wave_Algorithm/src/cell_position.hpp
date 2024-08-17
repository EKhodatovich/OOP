#pragma once
#include <functional>

class CellPosition final
{
	size_t x;
	size_t y;
public:
	size_t get_x() const { return x; }
	size_t get_y() const { return y; }
	CellPosition(const size_t x, const size_t y) : x(x), y(y) {}
	CellPosition() = default;
    bool operator==(const CellPosition& _other) const {return x==_other.x && y==_other.y;};
    bool operator!=(const CellPosition& _other) const {return !(*this==_other);};

};

template<>
struct std::hash<CellPosition>
{
	size_t operator()(const CellPosition& position) const noexcept
	{
		return std::hash<size_t>{}((position.get_x()<<7) + position.get_y());
	}
};
