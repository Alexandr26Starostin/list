#ifndef LIST_PRINT_H
#define LIST_PRINT_H

#include "const_in_list.h"

#ifdef PRINT_LIST
	list_error_t print_list (list_t* ptr_list);
	list_error_t list_dump  (list_t* ptr_list, FILE* dump_file);
#endif

#endif