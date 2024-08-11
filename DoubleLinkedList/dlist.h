#pragma once
#include <stdbool.h> // bool
#include <stddef.h>  // size_t


static const size_t INVALID = ~((size_t)0);

// annotation
void* dlist_create(const size_t itemSize);
void dlist_destroy(void* dlist, void(*destroy)(void*));
void* dlist_init(
    void* dlist,
    const size_t itemSize,
    void(*destroy)(void*));
void dlist_clear(void* dlist, void(*destroy)(void*));
size_t dlist_count(const void* dlist);
void* dlist_item(const void* dlist, const size_t i);
void* dlist_append(void* dlist);
void* dlist_prepend(void* dlist);
void dlist_removeFirst(void* dlist, void(*destroy)(void*));
void dlist_removeLast(void* dlist, void(*destroy)(void*));

size_t dlist_first(const void* dlist);
size_t dlist_last(const void* dlist);
size_t dlist_next(const void* dlist, const size_t item_id);
size_t dlist_prev(const void* dlist, const size_t item_id);
size_t dlist_stop(const void* dlist);
void* dlist_current(const void* dlist, const size_t item_id);


void* dlist_insertAfter(void* dlist, const size_t item_id);
void* dlist_insertBefore(void* dlist, const size_t item_id);
void dlist_erase(void* dlist, const size_t item_id, void(*destroy)(void*));
