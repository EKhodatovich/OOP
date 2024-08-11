#include "figure_list_funcs.h"
#include "read_file.h"
#include <crtdbg.h> // _CrtDumpMemoryLeaks
#include <stdio.h> // printf
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Pass file with figures and positions");
        return 0;
    }
    char* filename = argv[1];
	char* char_figure_list = read_file_and_return_string_with_all_figures(filename);

	Figures_List* figure_list=create_list_of_figures(char_figure_list);
	draw_all_figures(figure_list);

	print_attacks_of_all_figures(figure_list);

	delete_all_figures(figure_list);
	_CrtDumpMemoryLeaks();	
	return 0;

}
