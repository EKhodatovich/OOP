#include "read_file.h"

#include <stdio.h> // printf, FILE
#include <stdlib.h> // NULL, malloc

char* read_file_and_return_string_with_all_figures(const char* filename)
{
	FILE* file = NULL;
	errno_t error = fopen_s(&file, filename, "r");
	if (file == NULL || error != 0)
	{
		printf("Couldn't read the file");
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);
	char* char_figure_list = malloc(sizeof(char) * file_size);
	if (char_figure_list == NULL)
	{
		return NULL;
	}
	fread(char_figure_list, sizeof(char), file_size, file);
	fclose(file);

	return char_figure_list;
}