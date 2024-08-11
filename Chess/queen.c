#include <stdio.h> // sprintf_s
#include <stdlib.h> // calloc, realloc, NULL
#include "new.h" // Class
#include "figure.h" // Figure
#include "queen.h"
#include "diagonal_and_straight_checks.h"

static void* queen_ctor(void* _self, va_list* app)
{
	struct Figure* self = ((const struct Class*)Figure)->ctor(_self, app);
	return self;
}


static struct Figures_List* queen_eat_check(const struct Figure* _self, const struct Figures_List* _other_figures)
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
		if (_self != other_figures[i] && (diagonal_check(_self, other_figures[i], _other_figures) || straight_check(_self, other_figures[i], _other_figures)))
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

static void queen_draw(const struct Figure* _self)
{
	printf("Queen on position %d, %d\n", _self->x, _self->y);
}

static const struct Figure_Info _Queen_Info = {
{
	sizeof(struct Queen),
	queen_ctor,
	NULL,
},
	queen_draw,
	queen_eat_check
};

const void* Queen = &_Queen_Info;
