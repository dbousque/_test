

#include "libfts.h"

void	test_bzero(void)
{
	char	*ptr;
	size_t	i;
	size_t	size;
	char	ok;

	printf("ft_bzero :\n  setting all characters to 10\n");
	printf("  calling ft_bzero\n  checking that all characters are 0...");
	size = sizeof(char) * 100;
	ptr = (char*)malloc(size);
	i = 0;
	while (i < size)
	{
		ptr[i] = 10;
		i++;
	}
	ft_bzero(ptr, size);
	i = 0;
	ok = 1;
	while (i < size)
	{
		if (ptr[i] != 0)
			ok = 0;
		i++;
	}
	printf(ok ? " ok\n" : " not ok\n");
	printf("  calling ft_bzero with 0 as second parameter, will it crash ?\n");
	ft_bzero(ptr, 0);
	printf("  apparently not\n");
}

void	test_strcat(void)
{
	char	*str1;

	printf("ft_strcat :\n  feeding with \"salut \" and \"les gars\"\n");
	str1 = (char*)malloc(sizeof(char) * (strlen("salut les gars") + 1));
	str1[0] = 's';
	str1[1] = 'a';
	str1[2] = 'l';
	str1[3] = 'u';
	str1[4] = 't';
	str1[5] = ' ';
	str1[6] = '\0';
	str1[strlen("salut les gars")] = 'o';
	ft_strcat(str1, "les gars");
	printf("  res : \"%s\"\n", str1);
	printf("  feeding with \"\" and \"salut\"\n");
	str1[0] = '\0';
	ft_strcat(str1, "salut");
	printf("  res : \"%s\"\n", str1);
	printf("  feeding with \"\" and \"\"\n");
	str1[0] = '\0';
	ft_strcat(str1, "");
	printf("  res : \"%s\"\n", str1);
	printf("  feeding with \"salut\" and \"\"\n");
	str1[0] = 's';
	str1[1] = 'a';
	str1[2] = 'l';
	str1[3] = 'u';
	str1[4] = 't';
	str1[5] = '\0';
	ft_strcat(str1, "");
	printf("  res : \"%s\"\n", str1);
}

void	test_isalpha(void) {
	int		tmp;

	printf("ft_isalpha :");
	printf("\n  testing with 'a' :     ");
	tmp = ft_isalpha('a');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'a' - 1 : ");
	tmp = ft_isalpha('a' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'a' + 1 : ");
	tmp = ft_isalpha('a' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'z' :     ");
	tmp = ft_isalpha('z');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'z' + 1 : ");
	tmp = ft_isalpha('a' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'z' - 1 : ");
	tmp = ft_isalpha('z' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'A' :     ");
	tmp = ft_isalpha('A');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'A' - 1 : ");
	tmp = ft_isalpha('A' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'A' + 1 : ");
	tmp = ft_isalpha('A' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'Z' :     ");
	tmp = ft_isalpha('Z');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'Z' + 1 : ");
	tmp = ft_isalpha('Z' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'Z' - 1 : ");
	tmp = ft_isalpha('Z' - 1);
	printf(tmp ? "true" : "false");
	printf("\n");
}

void	test_isdigit(void)
{
	int		tmp;

	printf("ft_isdigit :");
	printf("\n  testing with '0' :     ");
	tmp = ft_isdigit('0');
	printf(tmp ? "true" : "false");
	printf("\n  testing with '0' - 1 : ");
	tmp = ft_isdigit('0' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '0' + 1 : ");
	tmp = ft_isdigit('0' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '9' :     ");
	tmp = ft_isdigit('9');
	printf(tmp ? "true" : "false");
	printf("\n  testing with '9' - 1 : ");
	tmp = ft_isdigit('9' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '9' + 1 : ");
	tmp = ft_isdigit('9' + 1);
	printf(tmp ? "true" : "false");
	printf("\n");
}

void	test_isalnum(void)
{
	int		tmp;

	printf("ft_isalnum (same as two previous tests) :");
		printf("\n  testing with 'a' :     ");
	tmp = ft_isalnum('a');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'a' - 1 : ");
	tmp = ft_isalnum('a' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'a' + 1 : ");
	tmp = ft_isalnum('a' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'z' :     ");
	tmp = ft_isalnum('z');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'z' + 1 : ");
	tmp = ft_isalnum('a' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'z' - 1 : ");
	tmp = ft_isalnum('z' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'A' :     ");
	tmp = ft_isalnum('A');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'A' - 1 : ");
	tmp = ft_isalnum('A' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'A' + 1 : ");
	tmp = ft_isalnum('A' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'Z' :     ");
	tmp = ft_isalnum('Z');
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'Z' + 1 : ");
	tmp = ft_isalnum('Z' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 'Z' - 1 : ");
	tmp = ft_isalnum('Z' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '0' :     ");
	tmp = ft_isalnum('0');
	printf(tmp ? "true" : "false");
	printf("\n  testing with '0' - 1 : ");
	tmp = ft_isalnum('0' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '0' + 1 : ");
	tmp = ft_isalnum('0' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '9' :     ");
	tmp = ft_isalnum('9');
	printf(tmp ? "true" : "false");
	printf("\n  testing with '9' - 1 : ");
	tmp = ft_isalnum('9' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '9' + 1 : ");
	tmp = ft_isalnum('9' + 1);
	printf(tmp ? "true" : "false");
	printf("\n");	
}

void	test_isascii(void)
{
	int		tmp;

	printf("ft_isascii :");
	printf("\n  testing with 0 :   ");
	tmp = ft_isascii(0);
	printf(tmp ? "true" : "false");
	printf("\n  testing with -1 :  ");
	tmp = ft_isascii(-1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 1 :   ");
	tmp = ft_isascii(1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 127 : ");
	tmp = ft_isascii(127);
	printf(tmp ? "true" : "false");
	printf("\n  testing with 128 : ");
	tmp = ft_isascii(128);
	printf(tmp ? "true" : "false");
	printf("\n");
}

void	test_isprint(void)
{
	int		tmp;

	printf("ft_isprint :");
	printf("\n  testing with 0 :       ");
	tmp = ft_isprint(0);
	printf(tmp ? "true" : "false");
	printf("\n  testing with ' ' :     ");
	tmp = ft_isprint(' ');
	printf(tmp ? "true" : "false");
	printf("\n  testing with ' ' - 1 : ");
	tmp = ft_isprint(' ' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with ' ' + 1 : ");
	tmp = ft_isprint(' ' + 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '~' :     ");
	tmp = ft_isprint('~');
	printf(tmp ? "true" : "false");
	printf("\n  testing with '~' - 1 : ");
	tmp = ft_isprint('~' - 1);
	printf(tmp ? "true" : "false");
	printf("\n  testing with '~' + 1 : ");
	tmp = ft_isprint('~' + 1);
	printf(tmp ? "true" : "false");
	printf("\n");
}

void	test_toupper(void)
{
	int		tmp;

	printf("ft_toupper :");
	printf("\n  testing with 'a' :           ");
	tmp = ft_toupper('a');
	printf("'%c'", tmp);
	printf("\n  testing with 'a' - 1 ('`') : ");
	tmp = ft_toupper('a' - 1);
	printf("'%c'", tmp);
	printf("\n  testing with 'a' + 1 :       ");
	tmp = ft_toupper('a' + 1);
	printf("'%c'", tmp);
	printf("\n  testing with 'z' :           ");
	tmp = ft_toupper('z');
	printf("'%c'", tmp);
	printf("\n  testing with 'z' + 1 ('{') : ");
	tmp = ft_toupper('z' + 1);
	printf("'%c'", tmp);
	printf("\n  testing with 'z' - 1 :       ");
	tmp = ft_toupper('z' - 1);
	printf("'%c'", tmp);
	printf("\n");
}

void	test_tolower(void)
{
	int		tmp;

	printf("ft_toupper :");
	printf("\n  testing with 'A' :           ");
	tmp = ft_toupper('A');
	printf("'%c'", tmp);
	printf("\n  testing with 'A' - 1 ('@') : ");
	tmp = ft_toupper('A' - 1);
	printf("'%c'", tmp);
	printf("\n  testing with 'A' + 1 :       ");
	tmp = ft_toupper('A' + 1);
	printf("'%c'", tmp);
	printf("\n  testing with 'Z' :           ");
	tmp = ft_toupper('Z');
	printf("'%c'", tmp);
	printf("\n  testing with 'Z' + 1 ('[') : ");
	tmp = ft_toupper('Z' + 1);
	printf("'%c'", tmp);
	printf("\n  testing with 'Z' - 1 :       ");
	tmp = ft_toupper('Z' - 1);
	printf("'%c'", tmp);
	printf("\n");
}

void	test_puts(void) {
	char	*tmp;

	printf("ft_puts :\n");
	tmp = "salut";
	//printf("  puts called with \"%s\" : \"", tmp);
	//ft_puts(tmp);
	//printf("\"\n");
	int len = get_len(tmp);
	printf("there\n");
	printf("  get_len : %d\n", len);
}

int		main(void)
{
	printf(" -- BEGINNING TESTS\n");
	test_bzero();
	test_strcat();
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_isascii();
	test_isprint();
	test_toupper();
	test_tolower();
	test_puts();
	return (0);
}