#include <stdio.h>
#include <stdlib.h>
#include "diagonal_and_straight_checks.h"


/*
------------------------------------------------------------------------------
						       STRAIGHT CHECK
------------------------------------------------------------------------------
*/
static size_t x_func(const struct Figure* _figure)
{
	return _figure->x;
}
static size_t y_func(const struct Figure* _figure)
{
	return _figure->y;
}

static bool if_other_on_straight_way(size_t(*EQ_direct)(const struct Figure* _smth), size_t(*NEQ_direct)(const struct Figure* _smth), const struct Figure* _self, const struct Figure* _victim, const struct Figure* _other_figure)
{
	return
		EQ_direct(_self) == EQ_direct(_other_figure) &&
		(
			((NEQ_direct(_other_figure) < NEQ_direct(_self)) && (NEQ_direct(_other_figure) > NEQ_direct(_victim)))
			||
			((NEQ_direct(_other_figure) > NEQ_direct(_self)) && (NEQ_direct(_other_figure) < NEQ_direct(_victim)))
			);
}

bool straight_check(const struct Figure* _self, const struct Figure* _victim, const Figures_List* _other_figures)
{
	size_t(*EQ_direct)(const struct Figure* _smth) = NULL;
	size_t(*NEQ_direct)(const struct Figure* _smth) = NULL;
	if (_self->x == _victim->x)
	{
		EQ_direct = x_func;
		NEQ_direct = y_func;
	}
	else if (_self->y== _victim->y)
	{
		EQ_direct = y_func;
		NEQ_direct = x_func;
	}
	else
	{
		return false;
	}
	for (size_t i = 0; i< _other_figures->list_size; i++)
	{
		if (if_other_on_straight_way(EQ_direct, NEQ_direct, _self, _victim, _other_figures->list[i]))
		{
			return false;
		}
	}
	return true;
}
/*
------------------------------------------------------------------------------
						       DIAGONAL CHECK
------------------------------------------------------------------------------
*/

static bool x_direction(const struct Figure* _self, const struct Figure* _other)
{
	return (_self->x > _other->x);
}
static bool y_direction(const struct Figure* _self, const struct Figure* _other)
{
	return (_self->y > _other->y);
}

static bool if_other_on_diagonal_way(const struct Figure* _self, const struct Figure* _victim, const struct Figure* _other_figure)
{
	return _self != _other_figure &&
		abs(_self->x - _other_figure->x) == abs(_self->y - _other_figure->y) &&
		x_direction(_self, _victim) == x_direction(_self, _other_figure) &&
		y_direction(_self, _victim) == y_direction(_self, _other_figure) &&
		abs(_self->x - _victim->x) > abs(_self->x - _other_figure->x);
}

bool diagonal_check(const struct Figure* _self, const struct Figure* _victim, const struct Figures_List* _other_figures)
{
	if (abs(_self->x - _victim->x) != abs(_self->y - _victim->y))
	{
		return false;
	}
	for (size_t i = 0;i < _other_figures->list_size; i++)
	{
		if (if_other_on_diagonal_way(_self, _victim, _other_figures->list[i]))
		{
			return false;
		}
	}
	return true;
}
