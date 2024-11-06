CC=g++
FLAGS=-Iinclude -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE -D_EJC
FILES=main.o list_error.o list_ctor_dtor.o list_print.o list_operations.o

TARGET = list
# pathsub
# addprefix
# wildcard

PATCHED_FILES = $(addprefix build/, $(FILES))

all: prepare $(TARGET)

prepare:
	mkdir -p build

$(TARGET): $(FILES)
	@echo "Linling..."
	@$(CC) $(FLAGS) $(PATCHED_FILES) -o $(TARGET)

main.o: src/main.cpp
	@$(CC) -c $(FLAGS) src/main.cpp -o build/main.o

list_error.o: src/list_error.cpp
	@$(CC) -c $(FLAGS) src/list_error.cpp -o build/list_error.o

list_ctor_dtor.o: src/list_ctor_dtor.cpp
	@$(CC) -c $(FLAGS) src/list_ctor_dtor.cpp -o build/list_ctor_dtor.o

list_print.o: src/list_print.cpp
	@$(CC) -c $(FLAGS) src/list_print.cpp -o build/list_print.o

list_operations.o: src/list_operations.cpp
	@$(CC) -c $(FLAGS) src/list_operations.cpp -o build/list_operations.o

clean:
	rm -rf $(TARGET)
	cd build && rm -rf *.o
