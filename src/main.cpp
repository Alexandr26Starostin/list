#include <stdio.h>

#include "const_in_list.h"
#include "list_ctor_dtor.h"
#include "list_print.h"
#include "list_operations.h"

#define ADD_IN_LIST_(element, position) \
	if (list_add (&list, element, position)) {return (int) list.list_error;} \
	print_list (&list, list_file);                 \
	status = list_dump (&list, "Add", (list.next)[position], str_for_system, list_file, &number_of_picture); \
	if (status) {close_list_file (list_file); list_dtor (&list); return status;}        

#define REMOVE_FROM_LIST_(position) \
	if (list_remove (&list, position)) {return (int) list.list_error;} \
	print_list (&list, list_file);                 \
	status = list_dump (&list, "Remove", position, str_for_system, list_file, &number_of_picture); \
	if (status) {close_list_file (list_file); list_dtor (&list); return status;}     

//-------------------------------------------------------------------------------------------------     

int main () 
{
	list_t list = {};
	
	error_t status = NOT_ERROR;

	FILE* list_file = NULL;

	status = open_list_file (&list_file);
	if (status) {return status;} 

	if (list_ctor (&list))
	{
		list_dtor (&list);
		close_list_file (list_file);
		return (int) list.list_error;
	}

	char str_for_system [] 	 = "dot list.dot -Tpng -o pictures/list_0000.png";
	size_t number_of_picture = 0;

	print_list (&list, list_file);
	status = list_dump (&list, "Add", 0, str_for_system, list_file, &number_of_picture); 
	if (status) {return status;}

	ADD_IN_LIST_(7,  0)
	ADD_IN_LIST_(9,  1)
	ADD_IN_LIST_(17, 2)
	ADD_IN_LIST_(-6, 1)
	ADD_IN_LIST_(25, 0)
	
	REMOVE_FROM_LIST_(2)

	list_dtor (&list);
	close_list_file (list_file);
	return (int) list.list_error;
}