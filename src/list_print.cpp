#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "const_in_list.h"
#include "list_error.h"
#include "list_print.h"


list_error_t print_list (list_t* ptr_list, FILE* file)
{
	assert (ptr_list);
	assert (file);

	if (list_error (ptr_list, __FILE__, __LINE__))
	{
		return ptr_list -> list_error;
	}

	fprintf (file, "      ");

	for (size_t index_list = 0; index_list < SIZE_LIST; index_list++)
	{
		fprintf (file, "%4ld ", index_list);
	}
	fprintf (file, "\n");

	fprintf (file, "data: ");
	for (size_t index_data = 0; index_data < SIZE_DATA; index_data++)
	{
		fprintf (file, "%4ld ", (ptr_list -> data)[index_data]);
	}
	fprintf (file, "\n");

	fprintf (file, "next: ");
	for (size_t index_next = 0; index_next < SIZE_NEXT; index_next++)
	{
		fprintf (file, "%4ld ", (ptr_list -> next)[index_next]);
	}
	fprintf (file, "\n");

	fprintf (file, "prev: ");
	for (size_t index_prev = 0; index_prev < SIZE_PREV; index_prev++)
	{
		fprintf (file, "%4ld ", (ptr_list -> prev)[index_prev]);
	}
	fprintf (file, "\n\n");

	fprintf (file, "head  == %ld\n\n", (ptr_list -> next)[0]);
	fprintf (file, "tail  == %ld\n\n", (ptr_list -> prev)[0]);
	fprintf (file, "free  == %ld\n\n", ptr_list  -> free);
	fprintf (file, "count == %ld\n\n", ptr_list  -> count);

	fprintf (file, "communications: ");
	for (size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
	fprintf (file, "%4ld -> ", index_next);
	}
	fprintf (file, "\n\n");

	fprintf (file, "--------------------------------------------------------------------------------\n\n");

	return ptr_list -> list_error;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

error_t list_dump (list_t* ptr_list, const char* operation, size_t target, char* str_for_system, FILE* file)
{
	assert (ptr_list);
	assert (operation);
	assert (str_for_system);
	assert (file);

	if (list_error (ptr_list, __FILE__, __LINE__))
	{
		return (error_t) ptr_list -> list_error;
	}

	FILE* dump_file = fopen ("list.dot", "w");
	if (dump_file == NULL) {printf ("Not find list.dot\n"); return NOT_FIND_LIST_DOT;}

	fprintf (dump_file, "digraph\n{\n\trankdir = LR;\n\tnode[fontsize=9];\n\tedge[color=\"green\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\tcommunications_in_free [shape=\"rectangle\", color = \"green\", style=\"filled\",fillcolor=\"lightgreen\"]\n\n\t\t"
						"names_free [shape=record, label=\" index | data | next | prev \", style=\"filled\",fillcolor=\"yellow\"]\n\n\t\t"); 

	for	(size_t index_next = (ptr_list -> free); index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		if (index_next == target)
		{
			fprintf (dump_file, "name%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \", style=\"filled\",fillcolor=\"violet\"]\n\t\t", 
				index_next, index_next, index_next, (ptr_list -> data)[index_next], (ptr_list -> next)[index_next], (ptr_list -> prev)[index_next]);
		}
		else
		{
			fprintf (dump_file, "name%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \"]\n\t\t", 
				index_next, index_next, index_next, (ptr_list -> data)[index_next], (ptr_list -> next)[index_next], (ptr_list -> prev)[index_next]);
		}
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

	fprintf (dump_file, "\n\n\t\tcommunications_in_free -> names_free -> name%ld [penwidth = 6.0, color=\"white\"]\n\t}\n\n\t", (ptr_list -> free));

	//---------------------------------------------------------------------------------------------------------------------------------------------------------

	fprintf (dump_file, "edge[color=\"red\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\tcommunications_in_list [shape=\"rectangle\", color = \"red\", style=\"filled\",fillcolor=\"red\"]\n\n\t\t"
						"names_list [shape=record, label=\" index | data | next | prev \", style=\"filled\",fillcolor=\"yellow\"]\n\n\t\t"); 

	fprintf (dump_file, "name%d [shape=record, label=\"<f%d> %4d | %4ld | %4ld | %4ld \"]\n\t\t", 
			0,0, 0, (ptr_list -> data)[0], (ptr_list -> next)[0], (ptr_list -> prev)[0]);
		
	for	(size_t index_next = (ptr_list -> next)[0]; index_next != 0; index_next = (ptr_list -> next)[index_next])
	{
		if (index_next == target)
		{
			fprintf (dump_file, "name%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \", style=\"filled\",fillcolor=\"violet\"]\n\t\t", 
				index_next, index_next, index_next, (ptr_list -> data)[index_next], (ptr_list -> next)[index_next], (ptr_list -> prev)[index_next]);
		}
		else 
		{
			fprintf (dump_file, "name%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \"]\n\t\t", 
				index_next, index_next, index_next, (ptr_list -> data)[index_next], (ptr_list -> next)[index_next], (ptr_list -> prev)[index_next]);
		}
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

	fprintf (dump_file, "communications_in_list -> names_list -> name%d [penwidth = 15.0, color=\"white\"]\n\t}\n\n\t", 0);

	//-------------------------------------------------------------------------------------------------------------------------------------------------

	fprintf (dump_file, "edge[color=\"white\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\t"); 

	fprintf (dump_file, "header [shape=record, label=\"<f0> head | <f1> tail | <f2> free\", style=\"filled\",fillcolor=\"lightblue\"]\n\t}\n\t\t");

	fprintf (dump_file, "edge[color=\"blue\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\t"); 
	fprintf (dump_file, "header:<f0> -> name_ph%ld\n\theader:<f1> -> name_ph%ld\n\theader:<f2> -> name_ph%ld\n\t}\n\n\t", (ptr_list -> next)[0], (ptr_list -> prev)[0], ptr_list -> free);

	//--------------------------------------------------------------------------------------------------------------------------------------------------

	fprintf (dump_file, "edge[color=\"white\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\tphysical_list [shape=\"rectangle\", color = \"black\"]\n\n\t\t"
						"names_physical_list [shape=record, label=\" index | data | next | prev \", style=\"filled\",fillcolor=\"yellow\"]\n\n\t\t"); 

	for	(size_t index_data = 0; index_data < SIZE_DATA; index_data++)
	{
		if ((ptr_list -> prev)[index_data] == -1)
		{
			fprintf (dump_file, "name_ph%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \", style=\"filled\",fillcolor=\"lightgreen\"]\n\t\t", 
				index_data, index_data, index_data, (ptr_list -> data)[index_data], (ptr_list -> next)[index_data], (ptr_list -> prev)[index_data]);
		}
		else
		{
			fprintf (dump_file, "name_ph%ld [shape=record, label=\"<f%ld> %4ld | %4ld | %4ld | %4ld \", style=\"filled\",fillcolor=\"red\"]\n\t\t", 
				index_data, index_data, index_data, (ptr_list -> data)[index_data], (ptr_list -> next)[index_data], (ptr_list -> prev)[index_data]);
		}
	}

	fprintf (dump_file, "\n\t\tname_ph%d:<f%d> ", 0, 0);

	for	(size_t index_data = 0; index_data < SIZE_DATA; index_data++)
	{
		fprintf (dump_file, "-> name_ph%ld:<f%ld> ", index_data, index_data);
	}

	fprintf (dump_file, "\n\t\tphysical_list -> names_physical_list -> name_ph%d\n\t}\n\n\t", 0);

	//--------------------------------------------------------------------------------------------------------------------------------------------------

	fprintf (dump_file, "edge[color=\"white\",fontsize=12]\n\n\t"
						"subgraph\n\t{\n\t\t");

	fprintf (dump_file, "%s_element[shape=\"rectangle\", color = \"orange\", style=\"filled\",fillcolor=\"orange\"]\n\t}\n\n\t", operation);

	//--------------------------------------------------------------------------------------------------------------------------------------------------

	fprintf (dump_file, "\n}");

	fclose (dump_file);

	//getchar ();

	system (str_for_system);

	fprintf (file, "\t<img src=\"pictures/list_1.png\" style=\"width: 80%\">\n\n");

	return NOT_ERROR;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

error_t open_list_file (FILE** ptr_file)
{
	assert (ptr_file);

	*ptr_file = fopen ("list.html", "w");

	if (*ptr_file == NULL)
	{
		printf ("Not find 'list.dot'.\n");
		return NOT_FIND_LIST_FILE;
	}

	fprintf (*ptr_file, "<pre>\n");

	return NOT_ERROR;
}

error_t close_list_file (FILE* file)
{
	assert (file);

	fprintf (file, "</pre>\n");

	fclose (file);

	return NOT_ERROR;
}
