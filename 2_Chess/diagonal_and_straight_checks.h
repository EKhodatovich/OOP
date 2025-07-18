#pragma once

#include "figure.h"

#include <stdbool.h>
bool straight_check(const struct Figure* _self, const struct Figure* _victim, const Figures_List* _other_figures);
bool diagonal_check(const struct Figure* _self, const struct Figure* _victim, const struct Figures_List* _other_figures);
