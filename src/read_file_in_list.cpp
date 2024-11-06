#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "const_in_list.h"
#include "read_file_in_list.h"

error_t read_file (int argc, char** argv, FILE** ptr_dump_file)
{
	assert (argv);
	assert (ptr_dump_file);

	size_t index_argv = 0;
	char* ptr_name_file = NULL;

	for (;(int) index_argv < argc; index_argv++)
	{
		ptr_name_file = strstr (argv[index_argv], "-f");
		if (ptr_name_file != NULL)
		{
			*ptr_dump_file = fopen (ptr_name_file + SIZE_FLAG, "w");
			return NOT_ERROR;
		}
	}

	if ((int) index_argv == argc) 
	{
		printf ("List wants to eat one dump_file)) Don't be greedy\nUse flag -f get dump_file to list");
		return FEW_FILES;
	}

	if (*ptr_dump_file == NULL)
	{
		printf ("cmd_file == NULL\n");

		printf ("Not find file\n"); 
		printf ("Write in format: 1) exe  2) -f<dump_file>  3) other \n");

		fclose (*ptr_dump_file);

		return NOT_FIND_DUMP_FILE;
	}

	return NOT_FIND_DUMP_FILE;
}