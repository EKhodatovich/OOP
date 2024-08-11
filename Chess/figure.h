#pragma once

#include "new.h"


struct Figure {
	const void* class;
	int x;
	int y;
};

typedef struct Figures_List {
	struct Figure** list;
	size_t list_size;
}Figures_List;

struct Figure_Info {
	const struct Class _;
	void (*draw)(const struct Figure* self);
	struct Figures_List* (*eat_check)(const struct Figure* self, const struct Figures_List* other_figures);
};

void draw(const struct Figure* _self);
struct Figures_List* eat_check(const struct Figure* _self, const struct Figures_List* _other_figures);

extern const void* Figure;
