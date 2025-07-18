#include <stdio.h> // sprintf_s
#include <stdlib.h> // calloc, realloc, NULL
#include <math.h> // pow, abs
#include <stdbool.h> // bool
#include "new.h" // Class
#include "figure.h" // Figure
#include "king.h" // KIng, King_Info

const int max_king_move_dist = 4;

static void* king_ctor(void* _self, va_list* app)
{
	struct Figure* self = ((const struct Class*)Figure)->ctor(_self, app);
	return self;
}
static bool king_eats_other_figure(const struct Figure* _self, const struct Figure* _other_figure)
{
	return 	_self != _other_figure && pow(abs(_other_figure->x - _self->x), 2) + pow(abs(_other_figure->y - _self->y), 2) < max_king_move_dist;
}

static struct Figures_List* king_eat_check(const struct Figure* _self, const struct Figures_List* _other_figures)
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
		if (king_eats_other_figure(_self, other_figures[i]))
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

static void king_draw(const struct Figure* _self)
{
	printf("King on position %d, %d\n", _self->x, _self->y);
}

static const struct Figure_Info _King_Info = {
{
	sizeof(struct King),
	king_ctor,
	NULL,
},
	king_draw,
	king_eat_check
};

const void* King = &_King_Info;
