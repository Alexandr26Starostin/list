#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS

#include "const_in_list.h"

list_error_t list_add    (list_t* ptr_list, data_t element, size_t index_prev_element);
list_error_t list_remove (list_t* ptr_list, size_t index_prev_element);

#endif