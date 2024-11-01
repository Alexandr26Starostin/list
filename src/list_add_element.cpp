#include <stdio.h>
#include <assert.h>

#include "list_error.h"
#include "list_add_element.h"

list_error_t list_add (list_t* ptr_list, data_t element, size_t index_prev_element)
{
	assert (ptr_list);

	if (index_prev_element > (ptr_list -> count))
	{
		ptr_list -> list_error |= PREV_MORE_COUNT;
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

	if (index_prev_element == ptr_list -> tail)
	{
		ptr_list -> tail = ptr_list -> free;
	}

	if (index_prev_element == 0)
	{
		ptr_list -> head   = ptr_list -> free;
	}

	ptr_list -> free   = next_free;
	ptr_list -> count += 1;

	return ptr_list -> list_error;
}