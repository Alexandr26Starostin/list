#ifndef CONST_IN_LIST_H
#define CONST_IN_LIST_H

typedef long data_t;
typedef long next_t;
typedef long prev_t;

typedef long head_t;
typedef long tail_t;
typedef long free_t;

typedef long list_error_t;


struct list_t
{
	data_t*      data;
	next_t*      next;
	prev_t*      prev;

	head_t       head;
	tail_t       tail;
	free_t       free;

	list_error_t list_error;
};

//--------------------------------------------------------------------------------------------------------

const size_t MAX_BIT = sizeof (list_error_t);

enum error_t
{
	NOT_ERROR = 0,
	DATA_NULL = 1,
	NEXT_NULL = 2,
	PREV_NULL = 4
};

#endif