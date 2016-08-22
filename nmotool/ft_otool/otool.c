

#include "otool.h"

void	handle_file(char *ptr, char type, char *file_name)
{
	t_flags		*options;

	options = (t_flags*)get_current_options();
	if (type == MACH_O_64)
		print_text_section_64(ptr, options, file_name);
	else if (type == MACH_O_32)
		print_text_section_32(ptr, options, file_name);
}