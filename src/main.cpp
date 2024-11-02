#include <stdio.h>

#include "const_in_list.h"
#include "list_ctor_dtor.h"
#include "list_print.h"
#include "list_add_element.h"
#include "list_remove_element.h"

int main ()
{
	printf ("Hello, I'm list)))\n");

	list_t list = {};

	if (list_ctor (&list))
	{
		list_dtor (&list);
		return (int) list.list_error;
	}

	print_list (&list);

	if (list_add (&list, 7, 0)) {return (int) list.list_error;}
	print_list (&list);

	if (list_add (&list, 9, 1)) {return (int) list.list_error;}
	print_list (&list);

	if (list_add (&list, 17, 2)) {return (int) list.list_error;}
	print_list (&list);

	if (list_add (&list, -6, 1)) {return (int) list.list_error;}
	print_list (&list);

	if (list_add (&list, 25, 0)) {return (int) list.list_error;}
	print_list (&list);

	if (list_remove (&list, 2)) {return (int) list.list_error;}
	print_list (&list);

	list_dtor (&list);
	return (int) list.list_error;
}