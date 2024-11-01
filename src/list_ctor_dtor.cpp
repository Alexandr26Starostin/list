#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "const_in_list.h"
#include "list_error.h"
#include "list_ctor_dtor.h"

list_error_t list_ctor (list_t* ptr_list)
{
	assert (ptr_list);

	ptr_list -> list_error = NOT_ERROR;

	ptr_list -> data = (data_t*) calloc (SIZE_DATA, sizeof (data_t));
	if (ptr_list -> data == NULL) {ptr_list -> list_error |= DATA_NULL;}

	ptr_list -> next = (next_t*) calloc (SIZE_NEXT, sizeof (next_t));
	if (ptr_list -> next == NULL) {ptr_list -> list_error |= NEXT_NULL;}

	ptr_list -> prev = (prev_t*) calloc (SIZE_PREV, sizeof (prev_t));
	if (ptr_list -> prev == NULL) {ptr_list -> list_error |= PREV_NULL;}

	ptr_list -> head  = 0;
	ptr_list -> tail  = 1;
	ptr_list -> free  = 1;
	ptr_list -> count = 0;

	if (list_error (ptr_list, __FILE__, __LINE__))
	{
		return ptr_list -> list_error;
	}

	//-------------------------------------------------------------------------------------------

	(ptr_list -> data)[0] = POISON;
	for (size_t index_data = 1; index_data < SIZE_DATA; index_data++)
	{
		(ptr_list -> data)[index_data] = FREE_VALUE;
	}

	(ptr_list -> next)[0] = 0;
	for (size_t index_next = 1; index_next < SIZE_NEXT - 1; index_next++)
	{
		(ptr_list -> next)[index_next] = index_next + 1;
	}
	(ptr_list -> next)[SIZE_NEXT - 1] = 0;

	(ptr_list -> prev)[0] = 0;
	for (size_t index_prev = 1; index_prev < SIZE_PREV; index_prev++)
	{
		(ptr_list -> prev)[index_prev] = FREE_VALUE;
	}

	return ptr_list -> list_error;
}

list_error_t list_dtor (list_t* ptr_list)
{
	assert (ptr_list);

	list_error (ptr_list, __FILE__, __LINE__);

	free (ptr_list -> data);
	free (ptr_list -> next);
	free (ptr_list -> prev);

	ptr_list -> head  = 0;
	ptr_list -> tail  = 1;
	ptr_list -> free  = 1;
	ptr_list -> count = 0;

	return ptr_list -> list_error;
}