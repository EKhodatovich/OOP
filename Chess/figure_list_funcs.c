#include "new.h"

#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "figure_list_funcs.h"

#include <stdio.h> // printf, sscanf_s
#include <stdlib.h> // NULL, calloc
#include <string.h> // strtok_s
#include <stdbool.h> // bool


const char* figures_names[5] = { "king", "queen","rook","bishop","knight" };

Figures_List* create_list_of_figures(char* char_figure_list)
{
    const int standart_figure_name_size = 7;
	//char figure_name[standart_figure_name_size];	


    char figure_name[standart_figure_name_size];
    figure_name[standart_figure_name_size-1] = '\0';
    //figure_name[6] = '\0';
	int x = 0, y = 0;

	Figures_List* figure_list = calloc(1, sizeof(Figures_List));
	if (!figure_list)
	{
		return NULL;
	}
	struct Figure* p = NULL;
	struct Figure** tmp = NULL;
	size_t lines_count = 0;
	int figures_count = 0;
    bool figure_created = true;

	char* token = NULL;
	char* next_token = NULL;

	token = strtok_s(char_figure_list, "\n", &next_token);

    for ( ; token !=NULL ; figures_count++)
	{
		if (!sscanf_s(token, "%s %d %d\n", figure_name, (unsigned int)sizeof(figure_name), &x, &y))
		{
			break;
		}
		
		if (!strcmp(figure_name, figures_names[0]))
		{
			p = new(King, x, y);
		}
		else if (!strcmp(figure_name, figures_names[1]))
		{
			p = new(Queen, x, y);
		}
		else if (!strcmp(figure_name, figures_names[2]))
		{
			p = new(Rook, x, y);
		}
		else if (!strcmp(figure_name, figures_names[3]))
		{
			p = new(Bishop, x, y);
		}
		else if (!strcmp(figure_name, figures_names[4]))
		{
			p = new(Knight, x, y);
		}
		else
		{
			printf("Wrong input in line %zd\n", lines_count + 1);
            figure_created = false;
		}
        if (figure_created)
		{
			tmp = realloc(figure_list->list, (figures_count + 1) * sizeof(struct Figure*));
			if (!tmp)
			{
                free(figure_list);
				return NULL;
			}
			figure_list->list = tmp;
			*(figure_list->list + figures_count) = p;
		}
		else
		{
			figures_count--;
		}
		token = strtok_s(NULL, "\n", &next_token);
		lines_count++;
        figure_created = true;
	}
	figure_list->list_size = figures_count;
	free(char_figure_list);
	return figure_list;
}



void draw_all_figures(const Figures_List* const figures_list)
{
	if (figures_list == NULL)
	{
		return;
	}
	for (size_t i = 0; i< figures_list->list_size;i++)
	{
		draw(figures_list->list[i]);
	}
	printf("======================================================================\n");
}

void print_attacks_of_all_figures(const Figures_List* figures_list)
{
	if (figures_list == NULL)
	{
		return;
	}
	for (size_t figure_index = 0; figure_index<figures_list->list_size;figure_index++)
	{
		Figures_List* eaten_figures = eat_check(*(figures_list->list + figure_index), figures_list);
		draw(figures_list->list[figure_index]);
		printf("Eats\n------------------------------------------------------\n");
		if (eaten_figures == NULL)
		{
			printf("Some error occured");
			return;
		}
		for (size_t eaten_figures_index = 0; eaten_figures_index< eaten_figures->list_size; eaten_figures_index ++)
		{
			draw(eaten_figures->list[eaten_figures_index]);
		}
		free(eaten_figures->list);
		free(eaten_figures);
		printf("------------------------------------------------------------\n\n");
	};
	printf("======================================================================\n");
}

void delete_all_figures(Figures_List* figure_list)
{
	if (figure_list == NULL)
	{
		return;
	}
	for (size_t i = 0; i<figure_list->list_size;i++)
	{
		delete(*(figure_list->list + i));
	};
	free(figure_list->list);
	free(figure_list);
}
