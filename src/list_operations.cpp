#include <stdio.h>
#include <assert.h>

#include "list_error.h"
#include "list_operations.h"

list_error_t list_add (list_t* ptr_list, data_t element, size_t index_prev_element)
{
	assert (ptr_list);

	if (index_prev_element > (ptr_list -> count))
	{
		ptr_list -> list_error |= PREV_MORE_COUNT;
		list_error (ptr_list, __FILE__, __LINE__);
		return ptr_list -> list_error;
	}

	if (ptr_list -> free == 0)
	{
		ptr_list -> list_error |= LIST_FULL;
		list_error (ptr_list, __FILE__, __LINE__);
		return ptr_list -> list_error;
	}

	free_t next_free = (ptr_list -> next)[ptr_list -> free];
	
	size_t old_next                        = (ptr_list -> next)[index_prev_element];  
	(ptr_list -> prev)[old_next]           = ptr_list -> free;
	(ptr_list -> next)[index_prev_element] = ptr_list -> free; 

	(ptr_list -> data)[ptr_list -> free] = element;
	(ptr_list -> next)[ptr_list -> free] = old_next;
	(ptr_list -> prev)[ptr_list -> free] = index_prev_element;

	ptr_list -> free   = next_free;
	ptr_list -> count += 1;

	list_error (ptr_list, __FILE__, __LINE__);
	return ptr_list -> list_error;
}

list_error_t list_remove (list_t* ptr_list, size_t index_remote_element)
{
	assert (ptr_list);

	if ((ptr_list -> next)[0] == 0)
	{
		ptr_list -> list_error |= NOT_ELEMENTS_IN_LIST;
		list_error (ptr_list, __FILE__, __LINE__);
		return ptr_list -> list_error;
	}

	if (index_remote_element == 0)
	{
		ptr_list -> list_error |= REMOVE_NULL;
		list_error (ptr_list, __FILE__, __LINE__);
		return ptr_list -> list_error;
	}

	size_t old_next                          = (ptr_list -> next)[index_remote_element];  
	size_t old_prev                          = (ptr_list -> prev)[index_remote_element]; 

	(ptr_list -> next)[old_prev]             = old_next;
	(ptr_list -> prev)[old_next]             = old_prev;

	(ptr_list -> data)[index_remote_element] = FREE_VALUE;
	(ptr_list -> next)[index_remote_element] = ptr_list -> free;
	(ptr_list -> prev)[index_remote_element] = FREE_VALUE;

	ptr_list -> free = index_remote_element;

	list_error (ptr_list, __FILE__, __LINE__);
	return ptr_list -> list_error;
}