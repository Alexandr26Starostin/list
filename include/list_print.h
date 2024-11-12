#ifndef LIST_PRINT_H
#define LIST_PRINT_H

#include "const_in_list.h"


list_error_t print_list      (list_t* ptr_list, FILE* file);
error_t      list_dump       (list_t* ptr_list, const char* operation, size_t target, char* str_for_system, FILE* file);
error_t      open_list_file  (FILE**  ptr_file);
error_t      close_list_file (FILE*   file);
#endif