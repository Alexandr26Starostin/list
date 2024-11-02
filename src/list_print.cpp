#include <stdio.h>
#include <assert.h>

#include "const_in_list.h"
#include "list_print.h"

#ifdef PRINT_LIST 
	list_error_t print_list (list_t* ptr_list)
	{
		assert (ptr_list);

		printf ("      ");

		for (size_t index_list = 0; index_list < SIZE_LIST; index_list++)
		{
			printf ("%4ld ", index_list);
		}
		printf ("\n");

		printf ("data: ");
		for (size_t index_data = 0; index_data < SIZE_DATA; index_data++)
		{
			printf ("%4ld ", (ptr_list -> data)[index_data]);
		}
		printf ("\n");

		printf ("next: ");
		for (size_t index_next = 0; index_next < SIZE_NEXT; index_next++)
		{
			printf ("%4ld ", (ptr_list -> next)[index_next]);
		}
		printf ("\n");

		printf ("prev: ");
		for (size_t index_prev = 0; index_prev < SIZE_PREV; index_prev++)
		{
			printf ("%4ld ", (ptr_list -> prev)[index_prev]);
		}
		printf ("\n\n");

		printf ("head  == %ld\n\n", (ptr_list -> next)[0]);
		printf ("tail  == %ld\n\n", (ptr_list -> prev)[0]);
		printf ("free  == %ld\n\n", ptr_list -> free);
		printf ("count == %ld\n\n", ptr_list -> count);

		printf ("communications: ");
		for (size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
		{
			printf ("%4ld -> ", index_next);
		}
		printf ("\n\n");

		printf ("--------------------------------------------------------------------------------\n\n");

		getchar ();

		return ptr_list -> list_error;
	}
#endif