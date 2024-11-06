#include <stdio.h>

#include "const_in_list.h"
#include "list_ctor_dtor.h"
#include "list_print.h"
#include "list_operations.h"
#include "read_file_in_list.h"

#define ADD_IN_LIST_(element, position) \
	if (list_add (&list, element, position)) {return (int) list.list_error;} \
	print_list (&list);         
	//list_dump  (&list, dump_file);         

#define REMOVE_FROM_LIST_(position) \
	if (list_remove (&list, position)) {return (int) list.list_error;} \
	print_list (&list);         
	//list_dump  (&list, dump_file);         

int main (int argc, char** argv) 
{
	printf ("Hello, I'm list)))\n");

	list_t list = {};

	if (list_ctor (&list))
	{
		list_dtor (&list);
		return (int) list.list_error;
	}

	FILE* dump_file    = NULL;
	if (error_t status = read_file (argc, argv, &dump_file)) {return status;}

	print_list (&list);

	ADD_IN_LIST_(7,  0)
	ADD_IN_LIST_(9,  1)
	ADD_IN_LIST_(17, 2)
	ADD_IN_LIST_(-6, 1)
	ADD_IN_LIST_(25, 0)
	
	REMOVE_FROM_LIST_(2)

	list_dump  (&list, dump_file);

	list_dtor (&list);
	fclose    (dump_file);
	return (int) list.list_error;
}