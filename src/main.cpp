#include <stdio.h>

#include "const_in_list.h"
#include "list_ctor_dtor.h"
#include "list_print.h"


int main ()
{
	printf ("Hello, I'm list)))\n");

	list_t list = {};

	if (list_ctor (&list))
	{
		list_dtor (&list);
		return (int) list.list_error;
	}

	list_print (&list);

	list_dtor (&list);
	return (int) list.list_error;
}