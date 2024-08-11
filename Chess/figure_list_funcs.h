#pragma once

#include "figure.h"
Figures_List* create_list_of_figures(char* char_figure_list);
void draw_all_figures(const Figures_List* const figures_list);
void print_attacks_of_all_figures(const Figures_List* figures_list);
void delete_all_figures(Figures_List* figure_list);
