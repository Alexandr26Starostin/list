#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "const_in_list.h"
#include "list_print.h"


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
	printf ("free  == %ld\n\n", ptr_list  -> free);
	printf ("count == %ld\n\n", ptr_list  -> count);

	printf ("communications: ");
	for (size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
	printf ("%4ld -> ", index_next);
	}
	printf ("\n\n");

	printf ("--------------------------------------------------------------------------------\n\n");

	return ptr_list -> list_error;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

error_t list_dump (list_t* ptr_list, FILE* dump_file)
{
	assert (ptr_list);

	dump_file = fopen ("list.dot", "w");
	if (dump_file == NULL) {printf ("Not find list.dot\n"); return NOT_FIND_LIST_DOT;}

	fprintf (dump_file, "digraph\n{\n\trankdir = LR;\n\tnode[fontsize=9];\n\tedge[color=\"green\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\tfree [shape=\"rectangle\", color = \"green\"]\n\n\t\t"
						"names_free [shape=record, label=\" index | data | next | prev \"]\n\n\t\t"); 

	for	(size_t index_next = (ptr_list -> free); index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		fprintf (dump_file, "name%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \"]\n\t\t", 
			index_next, index_next, index_next, (ptr_list -> data)[index_next], (ptr_list -> next)[index_next], (ptr_list -> prev)[index_next]);
	}

	fprintf (dump_file, "\n\t\tname%ld:<f%ld> ", (ptr_list -> free), (ptr_list -> free));

	for	(size_t index_next = (ptr_list -> next)[(ptr_list -> free)]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		fprintf (dump_file, "-> name%ld:<f%ld> ", index_next, index_next);
	}

	fprintf (dump_file, "[penwidth = 6.0, color=\"white\"]\n\t\t");

	fprintf (dump_file, "name%ld:<f%ld> ", (ptr_list -> free), (ptr_list -> free));

	for	(size_t index_next = (ptr_list -> next)[(ptr_list -> free)]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		fprintf (dump_file, "-> name%ld:<f%ld> ", index_next, index_next);
	}

	fprintf (dump_file, "\n\n\t\tfree -> names_free -> name%ld [penwidth = 6.0, color=\"white\"]\n\t}\n\n\t", (ptr_list -> free));

	//---------------------------------------------------------------------------------------------------------------------------------------------------------

	fprintf (dump_file, "edge[color=\"red\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\tlist [shape=\"rectangle\", color = \"red\"]\n\n\t\t"
						"names_list [shape=record, label=\" index | data | next | prev \"]\n\n\t\t"); 

	fprintf (dump_file, "name%d [shape=record, label=\"<f%d> %4d | %4ld | %4ld | %4ld \"]\n\t\t", 
			0,0, 0, (ptr_list -> data)[0], (ptr_list -> next)[0], (ptr_list -> prev)[0]);
		
	for	(size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		fprintf (dump_file, "name%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \"]\n\t\t", 
			index_next, index_next, index_next, (ptr_list -> data)[index_next], (ptr_list -> next)[index_next], (ptr_list -> prev)[index_next]);
	}

	fprintf (dump_file, "\n\t\tname%d:<f%d> ", 0, 0);

	for	(size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		fprintf (dump_file, "-> name%ld:<f%ld> ", index_next, index_next);
	}

	fprintf (dump_file, "[penwidth = 6.0, color=\"white\"]\n\t\t");

	fprintf (dump_file, "name%d:<f%d> ", 0, 0);

	for	(size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		fprintf (dump_file, "-> name%ld:<f%ld> ", index_next, index_next);
	}

	fprintf (dump_file, "\n\t\tname%ld -> name%d\n\t\t", (ptr_list -> prev)[0], 0);

	fprintf (dump_file, "list -> names_list -> name%d [penwidth = 6.0, color=\"white\"]\n\t}\n}", 0);

	//--------------------------------------------------------------------------------------------------------------------------------------------------

	fclose (dump_file);

	getchar ();

	system ("dot list.dot -Tpng -o list.png");

	return NOT_ERROR;
}
