

#include <unistd.h>

void	write_no_real(char *str)
{
	while (*str)
	{
		if (*str == '"')
			write(1, "\\\"", 2);
		else if (*str == '\n')
			write(1, "\\n", 2);
		else if (*str == '\t')
			write(1, "\\t", 2);
		else if (*str == '\\')
			write(1, "\\\\", 2);
		else
			write(1, str, 1);
		str++;
	}
}

/*
   Un commentaire en dehors de mes fonctions
*/

int		main(void)
{
	char	*str;

	/*
	   Un commentaire dans mon main
	*/

	str = "\n\n#include <unistd.h>\n\nvoid\twrite_no_real(char *str)\n{\n\twhile (*str)\n\t{\n\t\tif (*str == '\"')\n\t\t\twrite(1, \"\\\\\\\"\", 2);\n\t\telse if (*str == '\\n')\n\t\t\twrite(1, \"\\\\n\", 2);\n\t\telse if (*str == '\\t')\n\t\t\twrite(1, \"\\\\t\", 2);\n\t\telse if (*str == '\\\\')\n\t\t\twrite(1, \"\\\\\\\\\", 2);\n\t\telse\n\t\t\twrite(1, str, 1);\n\t\tstr++;\n\t}\n}\n\n/*\n   Un commentaire en dehors de mes fonctions\n*/\n\nint\t\tmain(void)\n{\n\tchar\t*str;\n\n\t/*\n\t   Un commentaire dans mon main\n\t*/\n\n\tstr = \"\";\n\twrite(1, str, 436);\n\twrite_no_real(str);\n\twrite(1, str + 436, 86);\n\treturn (0);\n}\n";
	write(1, str, 436);
	write_no_real(str);
	write(1, str + 436, 86);
	return (0);
}
