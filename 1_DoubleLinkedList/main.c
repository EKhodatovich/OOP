#include "dlist.h"
#include <crtdbg.h>
#include <math.h>
#include <stdio.h>

#include <assert.h> // assert

static int tests(void);


typedef struct {
    int array[8];
    float d_variable;
} Value;

static void value_print(void* value)
{
    if (value == NULL)
    {
        printf("There are no values");
    }
    else
    {
        printf("Values are: ");
        for (int i = 0; i < 8; i++)
        {
            Value* value_ = value;
            printf("%d,", value_->array[i]);
        }
        printf("\n");
    }
}



int main(void)
{
    printf("Just tests\n");
    void* dlist = dlist_create(sizeof(Value));

    //
    assert(0 == dlist_count(dlist));
    assert(dlist_stop(dlist) == dlist_first(dlist));

    //
    Value value = { {1, 2, 3, 4, 5, 6, 7, 8}, 0.f };
    Value value2 = { {8, 7, 6, 5, 4, 3, 2, 1}, 1.f };
    //
    Value* insertedValue = (Value*)dlist_prepend(dlist);

    //
    *insertedValue = value;


    Value* item = dlist_item(dlist, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value.array[i]);
    }

    assert(fabsf(item->d_variable - value.d_variable) < 1e-10f);
    assert(NULL == dlist_item(dlist, 1));

    assert(dlist_next(dlist, dlist_first(dlist)) == dlist_stop(dlist));

    //
    dlist_append(dlist);
    dlist_prepend(dlist);
    insertedValue = (Value*)dlist_append(dlist);
    *insertedValue = value2;

    //
    assert(4 == dlist_count(dlist));

    item = (Value*)dlist_item(dlist, 1);
    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value.array[i]);
    }

    //
    dlist_removeFirst(dlist, NULL);
    dlist_removeLast(dlist, value_print);
    dlist_removeFirst(dlist, value_print);
    assert(dlist_next(dlist, dlist_first(dlist)) == dlist_stop(dlist));

    //
    dlist_removeLast(dlist, NULL);

    assert(0 == dlist_count(dlist));

    //   3
    dlist_insertAfter(dlist, 0);
    dlist_insertAfter(dlist, dlist_first(dlist));
    insertedValue = (Value*)dlist_insertBefore(dlist, dlist_first(dlist));
    dlist_insertBefore(dlist, dlist_last(dlist));

    //
    assert(4 == dlist_count(dlist));
    assert(dlist_next(dlist, dlist_last(dlist)) == dlist_stop(dlist));

    *insertedValue = value;
    item = (Value*)dlist_current(dlist, dlist_first(dlist));
    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value.array[i]);
    }

    //     id
    dlist_erase(dlist, dlist_first(dlist), value_print);
    dlist_erase(dlist, dlist_first(dlist), NULL);
    dlist_erase(dlist, dlist_first(dlist), NULL);
    dlist_erase(dlist, dlist_first(dlist), NULL);


    assert(0 == dlist_count(dlist));

    //   3
    dlist_insertBefore(dlist, dlist_stop(dlist));
    dlist_insertBefore(dlist, dlist_first(dlist));
    dlist_insertBefore(dlist, dlist_last(dlist));

    //
    dlist_init(dlist, sizeof(int), NULL);

    assert(0 == dlist_count(dlist));
    assert(dlist_stop(dlist) == dlist_first(dlist));


    //
    dlist_destroy(dlist, NULL);
    int a = tests();
    _CrtDumpMemoryLeaks();
    return a;
}

void* create_list_1_node(Value value)
{
    void* dlist = dlist_create(sizeof(Value));
    Value* insertedvalue = dlist_append(dlist);
    *insertedvalue = value;
    return dlist;
}

void* create_list_3_nodes(Value value1, Value value2, Value value3)
{
    void* dlist = dlist_create(sizeof(Value));
    Value* insertedvalue1 = dlist_append(dlist);
    *insertedvalue1 = value1;
    Value* insertedvalue2 = dlist_append(dlist);
    *insertedvalue2 = value2;
    Value* insertedvalue3 = dlist_append(dlist);
    *insertedvalue3 = value3;
    return dlist;
}

static int tests(void)
{
    Value value = { {1,2,3,4,5,6,7,8}, 0.f };
    Value* insertedvalue;

    /*
    -----------------------------------------------------
    NULL CONTAINER TESTS
    -----------------------------------------------------
    */
    printf("\nNull container tests\n");
    assert(dlist_create(0) == NULL);

    void* dlist = dlist_create(sizeof(Value));
    assert(dlist != NULL);
    assert(dlist_count(dlist) == 0);
    dlist_destroy(dlist, value_print);

    dlist_destroy(NULL, value_print);

    dlist_destroy(NULL, NULL);

    assert (dlist_init(NULL, 0, NULL) == NULL);

    assert (dlist_init(NULL, sizeof(Value), NULL) == NULL);

    dlist_clear(NULL, value_print);

    dlist_clear(NULL, NULL);

    assert(dlist_count(NULL) == INVALID);

    assert(dlist_item(NULL, (size_t)-1) == NULL);
    assert(dlist_item(NULL, 1) == NULL);

    assert(dlist_prepend(NULL) == NULL);
    assert(dlist_append(NULL) == NULL);

    dlist_removeFirst(NULL, value_print);
    dlist_removeLast(NULL, value_print);
    dlist_removeFirst(NULL, NULL);
    dlist_removeLast(NULL, NULL);

    dlist_stop(NULL);
    assert(dlist_first(NULL) == dlist_stop(NULL));
    assert(dlist_last(NULL) == dlist_stop(NULL));

    assert(dlist_current(NULL, dlist_stop(NULL)) == NULL);
    assert(dlist_next(NULL, dlist_stop(NULL)) == dlist_stop(NULL));
    assert(dlist_prev(NULL, dlist_stop(NULL)) == dlist_stop(NULL));
    int a = 0;

    for (size_t i = dlist_first(NULL); i != dlist_stop(NULL); i = dlist_next(NULL, i)) { a++; }
    for (size_t i = dlist_last(NULL); i != dlist_stop(NULL); i = dlist_prev(NULL, i)) { a++; }

    assert(dlist_insertAfter(NULL, dlist_stop(NULL)) == NULL);
    assert(dlist_insertBefore(NULL, dlist_stop(NULL)) == NULL);

    dlist_erase(NULL, dlist_stop(NULL), value_print);
    dlist_erase(NULL, dlist_stop(NULL), NULL);


    /*
    -----------------------------------------------------
    EMPTY CONTAINER TESTS
    -----------------------------------------------------
    */
    printf("\nEmpty container tests\n");

    dlist = dlist_create(sizeof(Value));
    dlist_destroy(dlist, value_print);

    dlist = dlist_create(sizeof(Value));
    dlist_destroy(dlist, NULL);

    dlist = dlist_create(sizeof(Value));
    assert(dlist_init(dlist, 0, NULL) == NULL);
    assert(dlist_init(dlist, -1, NULL) != NULL);
    assert(dlist_count(dlist) == 0);
    assert(dlist_init(dlist, sizeof(Value), NULL) != NULL);
    assert(dlist_count(dlist) == 0);
    assert(dlist_init(dlist, sizeof(Value), value_print) != NULL);
    assert(dlist_count(dlist) == 0);

    dlist_clear(dlist, value_print);
    assert(dlist_count(dlist) == 0);
    assert(dlist_item(dlist, 0) == NULL);
    assert(dlist_item(dlist, -1) == NULL);
    assert(dlist_item(dlist,(size_t)-1) == NULL);
    assert(dlist_item(dlist, 1) == NULL);

    dlist_clear(dlist, NULL);
    insertedvalue = dlist_prepend(dlist);
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 1);
    assert(dlist_item(dlist, 0) == insertedvalue);

    dlist_clear(dlist, NULL);
    insertedvalue = dlist_append(dlist);
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) ==1);
    assert(dlist_item(dlist, 0) == insertedvalue);

    dlist_clear(dlist, NULL);
    dlist_removeFirst(dlist, value_print);
    assert(dlist_count(dlist) == 0);
    dlist_removeFirst(dlist, NULL);
    assert(dlist_count(dlist) == 0);

    dlist_removeLast(dlist, value_print);
    assert(dlist_count(dlist) == 0);
    dlist_removeLast(dlist, NULL);
    assert(dlist_count(dlist) == 0);

    dlist_stop(dlist);
    assert(dlist_first(dlist) == dlist_stop(dlist));
    assert(dlist_last(dlist) == dlist_stop(dlist));
    assert(dlist_current(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_next(dlist, dlist_stop(dlist)) == 0);
    assert(dlist_prev(dlist, dlist_stop(dlist)) == 0);


    for (size_t i = dlist_first(dlist); i != dlist_stop(dlist); i = dlist_next(dlist, i)) { a++; }
    for (size_t i = dlist_last(dlist); i != dlist_stop(dlist); i = dlist_prev(dlist, i)) { a++; }

    insertedvalue = dlist_insertAfter(dlist, dlist_stop(dlist));
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 1);
    assert(dlist_item(dlist, 0) == insertedvalue);

    dlist_clear(dlist, NULL);
    insertedvalue = dlist_insertBefore(dlist, dlist_stop(dlist));
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 1);
    assert(dlist_item(dlist, 0) == insertedvalue);


    dlist_erase(dlist, dlist_stop(dlist), value_print);
    dlist_erase(dlist, dlist_stop(dlist), NULL);

    dlist_clear(dlist, NULL);
    dlist_erase(dlist, dlist_stop(dlist), value_print);
    dlist_erase(dlist, dlist_stop(dlist), NULL);


    dlist_destroy(dlist, NULL);

    /*
    -----------------------------------------------------
    SINGLE CONTAINER TESTS
    -----------------------------------------------------
    */
    printf("\nSingle containers tests\n");

    dlist = create_list_1_node(value);
    dlist_destroy(dlist, value_print);

    dlist = create_list_1_node(value);
    dlist_clear(dlist, value_print);
    assert(dlist_count(dlist) == 0);

    dlist_destroy(dlist, value_print);

    dlist = create_list_1_node(value);
    assert(dlist_init(dlist, 0, NULL) == NULL);
    assert(dlist_count(dlist) == 1);
    assert(dlist_init(dlist, sizeof(Value), NULL) != NULL);
    assert(dlist_count(dlist) == 0);
    dlist_destroy(dlist, NULL);
    dlist = create_list_1_node(value);
    assert(dlist_init(dlist, sizeof(Value), value_print) != NULL);
    assert(dlist_count(dlist) == 0);
    dlist_destroy(dlist, NULL);

    dlist = create_list_1_node(value);
    assert(dlist_item(dlist, 0) != NULL);
    assert(dlist_item(dlist, 1) == NULL);
    assert(dlist_item(dlist, (size_t)-1) == NULL);

    insertedvalue = dlist_prepend(dlist);
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 2);
    assert(dlist_item(dlist, 0) == insertedvalue);
    assert(dlist_item(dlist, 1) != insertedvalue);

    dlist_removeFirst(dlist, NULL);

    insertedvalue = dlist_append(dlist);
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 2);
    assert(dlist_item(dlist, 0) != insertedvalue);
    assert(dlist_item(dlist, 1) == insertedvalue);

    dlist_removeLast(dlist, NULL);

    dlist_removeFirst(dlist, value_print);
    assert(dlist_count(dlist) == 0);

    dlist_prepend(dlist);

    dlist_removeLast(dlist, value_print);
    assert(dlist_count(dlist) == 0);

    dlist_prepend(dlist);

    dlist_stop(dlist);
    assert(dlist_first(dlist) != dlist_stop(dlist));
    assert(dlist_last(dlist) != dlist_stop(dlist));
    assert(dlist_last(dlist) == dlist_last(dlist));
    assert(dlist_current(dlist, dlist_first(dlist)) != NULL);
    assert(dlist_current(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_next(dlist, dlist_first(dlist)) == dlist_stop(dlist));
    assert(dlist_next(dlist, dlist_last(dlist)) == dlist_stop(dlist));
    assert(dlist_prev(dlist, dlist_first(dlist)) == dlist_stop(dlist));
    assert(dlist_prev(dlist, dlist_last(dlist)) == dlist_stop(dlist));

    for (size_t i = dlist_first(dlist); i != dlist_stop(dlist); i = dlist_next(dlist, i)) { a++; }
    a--;
    for (size_t i = dlist_last(dlist); i != dlist_stop(dlist); i = dlist_prev(dlist, i)) { a++; }
    a--;


    insertedvalue = dlist_insertAfter(dlist, dlist_first(dlist));
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 2);
    assert(dlist_item(dlist, 0) != insertedvalue);
    assert(dlist_item(dlist, 1) == insertedvalue);

    dlist_removeLast(dlist, NULL);

    insertedvalue = dlist_insertBefore(dlist, dlist_first(dlist));
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 2);
    assert(dlist_item(dlist, 0) == insertedvalue);
    assert(dlist_item(dlist, 1) != insertedvalue);

    dlist_removeFirst(dlist, NULL);

    assert(dlist_insertAfter(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_count(dlist) == 1);

    assert(dlist_insertBefore(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_count(dlist) == 1);

    dlist_erase(dlist, dlist_first(dlist), value_print);
    assert(dlist_count(dlist) == 0);

    dlist_destroy(dlist, NULL);

    /*
    -----------------------------------------------------
    THREE CONTAINERS TESTS
    -----------------------------------------------------
    */
    printf("\nThree containers tests\n");
    Value value1 = value;
    Value value2 = {{8,7,6,5,4,3,2,1}, 1.f};
    Value value3 = {{5,5,5,5,5,5,5,5}, 2.f};

    dlist = create_list_3_nodes(value1, value2, value3);
    assert(dlist_count(dlist) == 3);
    dlist_destroy(dlist, value_print);

    dlist = create_list_3_nodes(value1, value2, value3);
    dlist_clear(dlist, value_print);
    assert(dlist_count(dlist)==0);

    dlist_destroy(dlist, NULL);

    // -----------------------------------------------------------
    printf("----------------------------------\n");
    dlist = create_list_3_nodes(value1, value2, value3);
    assert(dlist_init(dlist, 0, NULL) == NULL);
    assert(dlist_count(dlist) == 3);

    assert(dlist_init(dlist, sizeof(Value), NULL) != NULL);
    assert(dlist_count(dlist) == 0);
    assert(dlist_first(dlist) == dlist_stop(dlist));
    assert(dlist_last(dlist) == dlist_stop(dlist));

    assert(dlist_item(dlist, 0) == NULL);
    assert(dlist_item(dlist, 1) == NULL);
    Value* insertedvalue1 = (Value*)dlist_prepend(dlist);
    *insertedvalue1 = value1;
    Value* insertedvalue2 = (Value*)dlist_prepend(dlist);
    *insertedvalue2 = value2;
    Value* insertedvalue3 = (Value*)dlist_prepend(dlist);
    *insertedvalue3 = value3;
    assert(dlist_count(dlist) == 3);

    insertedvalue = dlist_item(dlist, 2);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue1->array[i] == insertedvalue->array[i]);
    }
    insertedvalue = dlist_item(dlist, 1);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue2->array[i] == insertedvalue->array[i]);
    }
    insertedvalue = dlist_item(dlist, 0);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue3->array[i] == insertedvalue->array[i]);
    }

    for (size_t j = 0; j < 10; j++)
    {
        dlist_init(dlist, sizeof(Value), NULL);
        assert(dlist_first(dlist) == dlist_stop(dlist));
        assert(dlist_last(dlist) == dlist_stop(dlist));

        assert(dlist_item(dlist, 0) == NULL);
        assert(dlist_item(dlist, 1) == NULL);

        insertedvalue1 = (Value*)dlist_insertBefore(dlist, dlist_stop(dlist));
        *insertedvalue1 = value1;
        insertedvalue2 = (Value*)dlist_insertBefore(dlist, dlist_first(dlist));
        *insertedvalue2 = value2;
        insertedvalue3 = (Value*)dlist_insertBefore(dlist, dlist_first(dlist));
        *insertedvalue3 = value3;

        insertedvalue = dlist_current(dlist, dlist_last(dlist));
        for (size_t i = 0; 8 > i; ++i)
        {
            assert(insertedvalue1->array[i] == insertedvalue->array[i]);
            assert(insertedvalue1->array[i] == value1.array[i]);
        }
        insertedvalue = dlist_item(dlist, 1);
        for (size_t i = 0; 8 > i; ++i)
        {
            assert(insertedvalue2->array[i] == insertedvalue->array[i]);
            assert(insertedvalue2->array[i] == value2.array[i]);
        }
        insertedvalue = dlist_current(dlist, dlist_first(dlist));
        for (size_t i = 0; 8 > i; ++i)
        {
            assert(insertedvalue3->array[i] == insertedvalue->array[i]);
            assert(insertedvalue3->array[i] == value3.array[i]);
        }
        assert(dlist_item(dlist, 4) == NULL);

        dlist_init(dlist, sizeof(int), value_print);
        assert(dlist_first(dlist) == dlist_stop(dlist));
        assert(dlist_last(dlist) == dlist_stop(dlist));

        assert(dlist_item(dlist, 0) == NULL);
        assert(dlist_item(dlist, 1) == NULL);

        int* inserted_int1 = (int*)dlist_insertAfter(dlist, dlist_stop(dlist));
        *inserted_int1 = 1;

        int* inserted_int = dlist_current(dlist, dlist_first(dlist));
        for (size_t i = 0; 8 > i; ++i)
        {
            assert(*inserted_int1 == *inserted_int);
            assert(*inserted_int1 == 1);
        }
        assert(dlist_item(dlist, 1) == NULL);
    }


    assert(dlist_init(dlist, sizeof(int), NULL) != NULL);
    printf("----------------------------------\n");
    assert(dlist_count(dlist) == 0);
    //------------------------------------------------------------


    dlist_destroy(dlist, NULL);
    dlist = create_list_3_nodes(value1, value2, value3);
    assert(dlist_init(dlist, sizeof(Value), value_print) != NULL);
    assert(dlist_count(dlist) == 0);
    dlist_destroy(dlist, NULL);

    dlist = create_list_3_nodes(value1, value2, value3);

    insertedvalue = dlist_item(dlist, 0);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value1.array[i]);
    }
    insertedvalue = dlist_item(dlist, 1);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value2.array[i]);
    }
    insertedvalue = dlist_item(dlist, 2);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value3.array[i]);
    }
    assert(dlist_item(dlist, 3) == NULL);
    assert(dlist_item(dlist, (size_t)-1) == NULL);

    insertedvalue = dlist_prepend(dlist);
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 4);
    assert(dlist_item(dlist, 0) == insertedvalue);
    assert(dlist_item(dlist, 1) != insertedvalue);

    dlist_removeFirst(dlist, NULL);

    insertedvalue = dlist_append(dlist);
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 4);
    assert(dlist_item(dlist, 0) != insertedvalue);
    assert(dlist_item(dlist, 3) == insertedvalue);

    dlist_removeLast(dlist, NULL);

    dlist_removeFirst(dlist, value_print);
    assert(dlist_count(dlist) == 2);

    dlist_prepend(dlist);

    dlist_removeLast(dlist, value_print);
    assert(dlist_count(dlist) == 2);

    dlist_prepend(dlist);

    dlist_stop(dlist);
    assert(dlist_first(dlist) != dlist_stop(dlist));
    assert(dlist_last(dlist) != dlist_stop(dlist));
    assert(dlist_first(dlist) != dlist_last(dlist));
    assert(dlist_current(dlist, dlist_first(dlist)) != NULL);
    assert(dlist_current(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_next(dlist, dlist_last(dlist)) == dlist_stop(dlist));
    assert(dlist_prev(dlist, dlist_first(dlist)) == dlist_stop(dlist));


    for (size_t i = dlist_first(dlist); i != dlist_stop(dlist); i = dlist_next(dlist, i)) { a++; }
    a=a-3;
    for (size_t i = dlist_last(dlist); i != dlist_stop(dlist); i = dlist_prev(dlist, i)) { a++; }
    a=a-3;


    insertedvalue = dlist_insertAfter(dlist, dlist_first(dlist));
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 4);
    assert(dlist_item(dlist, 0) != insertedvalue);
    assert(dlist_item(dlist, 1) == insertedvalue);

    dlist_erase(dlist,dlist_next(dlist, dlist_first(dlist)), NULL);

    insertedvalue = dlist_insertBefore(dlist, dlist_first(dlist));
    assert(insertedvalue != NULL);
    assert(dlist_count(dlist) == 4);
    assert(dlist_item(dlist, 0) == insertedvalue);
    assert(dlist_item(dlist, 1) != insertedvalue);

    dlist_erase(dlist, dlist_first(dlist), NULL);

    assert(dlist_insertAfter(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_count(dlist) == 3);

    assert(dlist_insertBefore(dlist, dlist_stop(dlist)) == NULL);
    assert(dlist_count(dlist) == 3);

    dlist_erase(dlist, dlist_first(dlist), value_print);
    assert(dlist_count(dlist) == 2);

    dlist_erase(dlist, dlist_last(dlist), value_print);
    assert(dlist_count(dlist) == 1);

    dlist_destroy(dlist, NULL);

    /*
    -----------------------------------------------------
    FOUR CONTAINERS TESTS
    -----------------------------------------------------
    */
    Value value4 = { {4,4,4,4,4,4,4,4}, 3.f};

    dlist = create_list_3_nodes(value1, value2, value3);
    insertedvalue = dlist_append(dlist);
    *insertedvalue = value4;
    assert(dlist_count(dlist) == 4);
    dlist_destroy(dlist, value_print);

    dlist = create_list_3_nodes(value1, value2, value3);
    insertedvalue = dlist_append(dlist);
    *insertedvalue = value4;
    dlist_clear(dlist, value_print);
    assert(dlist_count(dlist) == 0);

    dlist_destroy(dlist, NULL);

    // -----------------------------------------------------------
    printf("----------------------------------\n");
    dlist = create_list_3_nodes(value1, value2, value3);
    insertedvalue = dlist_append(dlist);
    *insertedvalue = value4;
    assert(dlist_init(dlist, 0, NULL) == NULL);
    assert(dlist_count(dlist) == 4);

    insertedvalue = dlist_item(dlist, 0);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value1.array[i]);
    }
    insertedvalue = dlist_item(dlist, 1);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value2.array[i]);
    }
    insertedvalue = dlist_item(dlist, 2);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value3.array[i]);
    }
    insertedvalue = dlist_item(dlist, 3);
    for (size_t i = 0; 8 > i; ++i)
    {
        assert(insertedvalue->array[i] == value4.array[i]);
    }
    assert(dlist_item(dlist, 4) == NULL);
    assert(dlist_item(dlist, (size_t)-1) == NULL);


    assert(dlist_init(dlist, sizeof(Value), NULL) != NULL);
    assert(dlist_count(dlist) == 0);
    assert(dlist_first(dlist) == dlist_stop(dlist));
    assert(dlist_last(dlist) == dlist_stop(dlist));

    dlist_destroy(dlist, NULL);

    return a;
}
