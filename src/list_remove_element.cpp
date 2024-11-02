#include <stdio.h>
#include <assert.h>

#include "list_error.h"
#include "list_remove_element.h"

list_error_t list_remove (list_t* ptr_list, size_t index_remote_element)
{
	assert (ptr_list);

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