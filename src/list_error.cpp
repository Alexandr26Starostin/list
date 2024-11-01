#include <stdio.h>
#include <assert.h>

#include "list_error.h"

static list_error_t verifier    (long status, const char* file, int line);
static long         print_error (long danger_bit);

//--------------------------------------------------------------------------------------------------------

list_error_t list_error (list_t* ptr_list, const char* file, int line)
{
	assert (ptr_list);
	assert (file);

	long status = ptr_list -> list_error; 

	if (status)
	{
		verifier (status, file, line);
	}

	return status;
}

//---------------------------------------------------------------------------------------------------------

static list_error_t verifier (long status, const char* file, int line)
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
		case DATA_NULL:           	 {printf ("pointer on data  == NULL;                                     code_error == %ld\n", danger_bit);     break;}
		case NEXT_NULL:           	 {printf ("pointer on next  == NULL;                                     code_error == %ld\n", danger_bit);     break;}
		case PREV_NULL:           	 {printf ("pointer on prev  == NULL;                                     code_error == %ld\n", danger_bit);     break;}

		default:                 	 {printf ("this error not find: %ld\n",                                                        danger_bit);     break;}
	}

	return danger_bit;
}