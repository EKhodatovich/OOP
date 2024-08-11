#include <stdarg.h> // va_arg
#include "figure.h"
#include "new.h"
static struct Figure* figure_ctor(struct Figure* _self, va_list* app)
{
    _self->x = va_arg(*app, int);
    _self->y = va_arg(*app, int);
	return _self;
}

void draw(const struct Figure* _self)
{
	const void* self_ = _self;
	struct Figure_Info* const* self = self_;
	if (_self!= NULL && *self != NULL && (*self)->draw != NULL)
	{
		(*self)->draw(_self);
	}
}

struct Figures_List* eat_check(const struct Figure* _self, const struct Figures_List *_other_figures)
{
	const void* self_ = _self;
	struct Figure_Info* const* self = self_;
    if (_self != NULL && *self != NULL && (*self)->eat_check!=NULL && _other_figures!=NULL &&  _other_figures->list != NULL)
	{
		return (*self)->eat_check(_self, _other_figures);
	}
	return NULL;
}

static const struct Class _Figure = {
	sizeof(struct Figure),
	figure_ctor,
	NULL,
};

const void* Figure = &_Figure;
