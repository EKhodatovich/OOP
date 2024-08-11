#include <stdlib.h> // free, calloc
#include "new.h"

void* new(const void* _class, ...)
{
	const struct Class* class = _class;
	void* pointer = calloc(1, class->size);
	if (pointer==NULL)
	{
		return NULL;
	}
	*(const struct Class**)pointer = class;
	if (class->ctor)
	{
		va_list ap;
		va_start(ap, _class);
		pointer = class->ctor(pointer, &ap);
		va_end(ap);
	}
	return pointer;
}

void delete(void* _self)
{
	const struct Class** self = _self;
	if (_self && *self && (*self)->dtor)
	{
		_self = (*self)->dtor(_self);
	}
	free(_self);
}


