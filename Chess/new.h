#pragma once

#include <stddef.h> // size_t
#include <stdarg.h> // va_list
struct Class {
	size_t size;
	void* (*ctor)(void* self, va_list* app);
	void* (*dtor)(void* self);
};

void* new(const void* _class, ...);
void delete(void* _self);
