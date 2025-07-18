#include <stdio.h> // sprintf_s
#include <stdlib.h> // calloc, realloc, NULL
#include <math.h> // pow, abs
#include <stdbool.h> // bool
#include "new.h" // Class
#include "figure.h" // Figure
#include "knight.h"

const double knight_move_dist = 5.0;
const double precision = 0.1;

static void* knight_ctor(void* _self, va_list* app)
{
	struct Figure* self = ((const struct Class*)Figure)->ctor(_self, app);
	return self;
}

static bool knight_eats_other_figure(const struct Figure* _self, const struct Figure* _other_figure)
{
	return 	fabs(	pow(abs(_self->x - _other_figure->x), 2)
					+
					pow(abs(_self->y - _other_figure->y), 2) - knight_move_dist) < precision;
}

static struct Figures_List* knight_eat_check(const struct Figure* _self, const struct Figures_List* _other_figures)
{
	Figures_List* result_list = calloc(1, sizeof(Figures_List));
	if (result_list == NULL)
	{
		return NULL;
	}
	struct Figure** result = NULL;
	struct Figure** tmp = NULL;
	struct Figure** other_figures = _other_figures->list;

	size_t number_of_eaten_figures = 0;

	for (size_t i = 0; i < _other_figures->list_size; i++)
	{
		if (knight_eats_other_figure(_self, other_figures[i]))
		{
			number_of_eaten_figures++;
			tmp = (struct Figure**)realloc(result, sizeof(struct Figure*) * (number_of_eaten_figures));
			if (tmp != NULL)
			{
				result = tmp;
			}
			else
			{
                free (result);
                free (result_list);
				return NULL;
			}
			result[number_of_eaten_figures - 1] = other_figures[i];
			result_list->list_size++;
		}
	}
	result_list->list = result;
	return result_list;
}

static void knight_draw(const struct Figure* _self)
{
	printf("Knight on position %d, %d\n", _self->x, _self->y);
}

static const struct Figure_Info _Knight_Info = {
{
	sizeof(struct Knight),
	knight_ctor,
	NULL,
},
	knight_draw,
	knight_eat_check
};
const void* Knight = &_Knight_Info;
