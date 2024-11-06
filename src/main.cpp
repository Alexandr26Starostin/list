#include <stdio.h>

#include "const_in_list.h"
#include "list_ctor_dtor.h"
#include "list_print.h"
#include "list_operations.h"

#define ADD_IN_LIST_(element, position) \
	if (list_add (&list, element, position)) {return (int) list.list_error;} \
	print_list (&list);                 \
	status = list_dump (&list, dump_file); \
	if (status) {return status;}        

#define REMOVE_FROM_LIST_(position) \
	if (list_remove (&list, position)) {return (int) list.list_error;} \
	status = list_dump (&list, dump_file); \
	if (status) {return status;}     

//-------------------------------------------------------------------------------------------------     

int main () 
{
	list_t list = {};

	if (list_ctor (&list))
	{
		list_dtor (&list);
		return (int) list.list_error;
	}

	FILE* dump_file = NULL;
	error_t status = NOT_ERROR;

	print_list (&list);
	status = list_dump (&list, dump_file); 
	if (status) {return status;}

	ADD_IN_LIST_(7,  0)
	ADD_IN_LIST_(9,  1)
	ADD_IN_LIST_(17, 2)
	ADD_IN_LIST_(-6, 1)
	ADD_IN_LIST_(25, 0)
	
	REMOVE_FROM_LIST_(2)

	list_dtor (&list);
	return (int) list.list_error;
}