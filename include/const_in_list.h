#ifndef CONST_IN_LIST_H
#define CONST_IN_LIST_H

typedef long   data_t;
typedef long   next_t;
typedef long   prev_t;

typedef size_t head_t;
typedef size_t tail_t;
typedef size_t free_t;

typedef long   list_error_t;


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

enum error_t
{
	NOT_ERROR = 0,
	DATA_NULL = 1,
	NEXT_NULL = 2,
	PREV_NULL = 4
};

//--------------------------------------------------------------------------------------------------------

const size_t MAX_BIT   = sizeof (list_error_t);

const size_t SIZE_DATA = 16;
const size_t SIZE_NEXT = 16;
const size_t SIZE_PREV = 16;

const long POISON     = -666;
const long FREE_VALUE = -1;

#endif