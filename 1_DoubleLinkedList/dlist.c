#include "dlist.h"
#include <stdlib.h> // free


// Структура ноды
typedef struct Node {
	void* data;
	struct Node* prev_node;
	struct Node* next_node;
} Node;

// Структура двусвязного списка
typedef struct {
	Node* head;
	Node* tail;
	size_t item_size;
	size_t list_size;
} Dlist;

static void node_destroy(Node* node, void(*destroy)(void*));
static Node* node_create(size_t list_item_size);
static void after_point_node(Node* new_node, Node* point_node, Dlist* list);
static void before_point_node(Node* new_node, Node* point_node, Dlist* list);
static void* dlist_insert(void* dlist, const size_t item_id, bool flag);
static void node_delete(Dlist* list, Node* node);

// Функция удаления ноды
static void node_destroy(Node* node, void(*destroy)(void*))
{
	if (destroy != NULL) 
	{ 
		destroy(node->data); 
	}
	free(node->data);
	free(node);
}

// Функция создания ноды
static Node* node_create(const size_t list_item_size)
{
	Node* new_node = calloc(1, sizeof(Node));
	if (new_node == NULL)
	{ 
		return NULL; 
	}
	new_node->data = calloc(1, list_item_size);
	return new_node;
}

// Функция создания списка
void* dlist_create(const size_t itemSize)
{
	if (itemSize == 0) 
	{ 
		return NULL; 
	}
	Dlist* dlist = (Dlist*)calloc(1, sizeof(Dlist));
	if (dlist == NULL) 
	{ 
		return NULL;
	}
	dlist->item_size = itemSize;
	return dlist;
}

// Функция удаления списка
void dlist_destroy(void* dlist, void(*destroy)(void*))
{
	if (dlist == NULL) 
	{ 
		return;
	}
	dlist_clear(dlist, destroy);
	free(dlist);
}

// Функция инициализация списка
void* dlist_init(void* dlist, const size_t itemSize, void(*destroy)(void*))
{
	if (dlist == NULL || itemSize==0) 
	{ 
		return NULL; 
	}
	Dlist* list = dlist;
	if (list->head != NULL)
	{
		dlist_clear(dlist, destroy);
	}
	list->item_size = itemSize;
	return dlist;
}

// Функция очистки списка
void dlist_clear(void* dlist, void(*destroy)(void*))
{
	if (dlist == NULL) 
	{ 
		return; 
	}
    size_t length = dlist_count(dlist);
	for (size_t i=0; i<length; i++)
	{
		dlist_removeFirst(dlist, destroy);
	}
}

// Функция подсчета количества элементов в списке
size_t dlist_count(const void* dlist)
{
	if (dlist == NULL) 
	{ 
		return INVALID; 
	}
	const Dlist* list = dlist;
	return list->list_size;
}


static const Node* node_prev(const Node* node)
{
	return node->prev_node;
}
static const Node* node_next(const Node* node)
{
	return node->next_node;
}


// Функция получения элемента списка по его порядковому номеру
void* dlist_item(const void* dlist, const size_t i)
{
	if (dlist == NULL) 
	{ 
		return NULL;
	}
	const Dlist* list = dlist;
	if (list->head == NULL || i>list->list_size-1) 
	{
		return NULL;
	}
	const Node* point_node = list->head;
	const Node* (*direction)(const Node* node) = node_next;
	size_t index = i;
	if (i >= list->list_size / 2)
	{
		point_node = list->tail;
		direction = node_prev;
		index = list->list_size - i-1;
	}
	for (;index > 0;index--)
	{
		point_node = direction(point_node);
	}
	return point_node->data;
}

// Функция вставки в конец списка
void* dlist_append(void* dlist)
{
	if (dlist == NULL)
	{
		return NULL;
	}
	Dlist* list = dlist;
	return dlist_insertAfter(dlist, (size_t)list->tail);
}

// Функция вставки в начало списка
void* dlist_prepend(void* dlist)
{
	if (dlist == NULL)
	{
		return NULL;
	}
	Dlist* list = dlist;
	return dlist_insertBefore(dlist, (size_t)list->head);
}

// Функция удаления головы
void dlist_removeFirst(void* dlist, void(*destroy)(void*))
{
	if (dlist == NULL)
	{
		return;
	}
	Dlist* list = dlist;
	dlist_erase(dlist, (size_t)list->head, destroy);
}

// функция удаления хвоста
void dlist_removeLast(void* dlist, void(*destroy)(void*))
{
	if (dlist == NULL)
	{
		return;
	}
	Dlist* list = dlist;
	dlist_erase(dlist, (size_t)list->tail, destroy);
}

// Функция, возвращающая идентификатор первого элемента
size_t dlist_first(const void* dlist)
{
	if (dlist == NULL)
	{
		return INVALID;
	}
	const Dlist* list = dlist;
	return (size_t)list->head;
}

// Функция, возвращающая идентификатор последнего элемента
size_t dlist_last(const void* dlist)
{
	if (dlist == NULL)
	{
		return INVALID;
	}
	const Dlist* list = dlist;
	return (size_t)list->tail;
}

// Функция, возвращающая идентификатор следующего элемента после указанного
size_t dlist_next(const void* dlist, const size_t item_id)
{
	if (dlist == NULL || item_id == INVALID)
	{
		return INVALID;
	}
	const Dlist* list = dlist;
	if (list->head == NULL) 
	{
		return 0;
	}
	const Node* point_node = (Node*)item_id;
	if (point_node)
	{
		return (size_t)point_node->next_node;
	}
	return 0;
}

// Функция, возвращающая идентификатор предыдущего элемента перед указанным
size_t dlist_prev(const void* dlist, const size_t item_id)
{
	if (dlist == NULL || item_id == INVALID)
	{ 
		return INVALID;
	}
	const Dlist* list = dlist;
	if (list->head == NULL)
	{
		return 0;
	}
	const Node* point_node = (Node*)item_id;
	if (point_node)
	{
		return (size_t)point_node->prev_node;
	}
	return 0;
}

// Функция, возвращающая идентификатор недопустимого элемента
size_t dlist_stop(const void* dlist)
{
	if (dlist == NULL) 
	{ 
		return INVALID;
	}
	return 0;
}

// Функция, возваращающая элемент по идентификатору
void* dlist_current(const void* dlist, const size_t item_id)
{
	if (dlist == NULL || item_id == INVALID)
	{ 
		return NULL;
	}
	const Node* point_node = (Node*)item_id;
	if (point_node)
	{
		return point_node->data;
	}
	return NULL;
}

// Вспомогательная функция вставки ноды после указанной  
static void after_point_node(Node* new_node, Node* point_node, Dlist* list)
{
	if (point_node->next_node == NULL)
	{
		point_node->next_node = new_node;
		new_node->prev_node = point_node;
		list->tail = new_node;
	}
	else
	{
		point_node->next_node->prev_node = new_node;
		new_node->next_node = point_node->next_node;
		new_node->prev_node = point_node;
		point_node->next_node = new_node;
	}
}

// Вспомогательная функция вставки ноды перед указанной  
static void before_point_node(Node* new_node, Node* point_node, Dlist* list)
{
	if (point_node->prev_node == NULL)
	{
		point_node->prev_node = new_node;
		new_node->next_node = point_node;
		list->head = new_node;
	}
	else
	{
		point_node->prev_node->next_node = new_node;
		new_node->prev_node = point_node->prev_node;
		new_node->next_node = point_node;
		point_node->prev_node = new_node;
	}
}

// Вспомогательная функция вставки элемента  
static void* dlist_insert(void* dlist, const size_t item_id, const bool flag)
{
	if (dlist == NULL || item_id == INVALID)
	{ 
		return NULL;
	}
	Dlist* list = dlist;
	Node* new_node = node_create(list->item_size);
	if (new_node == NULL) 
	{ 
		return NULL;
	}

	if (list->head == NULL && item_id == dlist_stop(dlist))
	{
		list->head = new_node;
		list->tail = new_node;
		list->list_size++;
		return new_node->data;
	}
	if (item_id == dlist_stop(dlist))
	{
		node_destroy(new_node, NULL);
	}
	else
	{
		Node* const point_node = (Node*)item_id;
		if (flag == false)
		{
			after_point_node(new_node, point_node, list);
		}
		else
		{
			before_point_node(new_node, point_node, list);
		}
		list->list_size++;
		return new_node->data;
	}
	return NULL;
}

// Функция вставки элемента после элемента с указанным идентификатором 
void* dlist_insertAfter(void* dlist, const size_t item_id)
{
	return dlist_insert(dlist, item_id, false);
}

// Функция вставки элемента перед элементом с указанным идентификатором 
void* dlist_insertBefore(void* dlist, const size_t item_id)
{
	return dlist_insert(dlist, item_id, true);
}

// Вспомогательная функция удаления ноды
void node_delete(Dlist* list, Node* const node)
{
	if (node->prev_node == NULL && node->next_node == NULL)
	{
		list->head = NULL;
		list->tail = NULL;
	}
	else if (node->prev_node == NULL)
	{
		list->head = node->next_node;
		node->next_node->prev_node = NULL;
	}
	else if (node->next_node == NULL)
	{
		list->tail = node->prev_node;
		node->prev_node->next_node = NULL;
	}
	else
	{
		node->prev_node->next_node = node->next_node;
		node->next_node->prev_node = node->prev_node;
	}
}

// Функция удаления элемента по идентификатору
void dlist_erase(void* dlist, const size_t item_id, void(*destroy)(void*))
{
	if (dlist == NULL || item_id == (size_t)NULL || item_id == INVALID)
	{ 
		return;
	}
	Dlist* list = dlist;
	if (list->head == NULL) 
	{ 
		return;
	}

	Node* const point_node = (Node*)item_id;
	node_delete(list, point_node);
	node_destroy(point_node, destroy);
	list->list_size--;
}
