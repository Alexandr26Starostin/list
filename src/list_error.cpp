#include <stdio.h>
#include <assert.h>

#include "list_error.h"

static list_error_t verifier    (list_error_t status, const char* file, int line);
static long         print_error (long danger_bit);

//--------------------------------------------------------------------------------------------------------

list_error_t list_error (list_t* ptr_list, const char* file, int line)
{
	assert (ptr_list);
	assert (file);

	size_t index_prev = 0;
	for (size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		index_prev = (ptr_list -> prev)[index_next];

		if (index_next != (size_t) (ptr_list -> next)[index_prev])
		{
			printf ("wrong communications with elements: %4ld <-> %4ld  (index_prev <-> index_next)\n", index_prev, index_next);
			ptr_list -> list_error |= ERROR_IN_COMMUNICATIONS;
		}
	}

	list_error_t status = ptr_list -> list_error; 

	if (status)
	{
		verifier (status, file, line);
	}

	return status;
}

//---------------------------------------------------------------------------------------------------------

static list_error_t verifier (list_error_t status, const char* file, int line)
{
	assert (file);

	printf ("Find error in %s:%d\n", file, line);

	long danger_bit = 0;

	for (size_t index_bit = 0; index_bit < MAX_BIT; index_bit++)
	{
		danger_bit = (1 << index_bit) & status;
		if (danger_bit)
		{
			print_error (danger_bit);
		}
	}

	return status;
}

static long print_error (long danger_bit)
{
	switch (danger_bit)
	{
		case DATA_NULL:               {printf ("Pointer on data  == NULL;                                                                           code_error == %ld\n", danger_bit);     break;}
		case NEXT_NULL:               {printf ("Pointer on next  == NULL;                                                                           code_error == %ld\n", danger_bit);     break;}
		case PREV_NULL:               {printf ("Pointer on prev  == NULL;                                                                           code_error == %ld\n", danger_bit);     break;}
		case PREV_MORE_COUNT:         {printf ("When program add new element after prev_element: index prev_element > count elements in list;       code_error == %ld\n", danger_bit);     break;}
		case REMOVE_NULL:             {printf ("Can not remove element with index == 0;                                                             code_error == %ld\n", danger_bit);     break;}
		case ERROR_IN_COMMUNICATIONS: {printf ("Wrong communications with elements                                                                  code_error == %ld\n", danger_bit);     break;}
		case LIST_FULL:               {printf ("He can not add element; List is full; change const SIZE_DATA, SIZE_NEXT, SIZE_PREV                  code_error == %ld\n", danger_bit);     break;}
		case NOT_ELEMENTS_IN_LIST:    {printf ("He can not remote element; List is empty; Add elements in list                                      code_error == %ld\n", danger_bit);     break;}

		default:                      {printf ("this error not find: %ld\n",                                                                                              danger_bit);     break;}
	}

	return danger_bit;
}