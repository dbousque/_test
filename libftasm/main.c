

#include "includes/libfts.h"

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

void	test_puts(void)
{
	char	*tmp;

	printf("ft_puts :\n");
	tmp = "salut";
	printf("  ft_puts called with \"%s\" : \"", tmp);
	fflush(stdout);
	ft_puts(tmp);
	fflush(stdout);
	printf("\"\n");
	fflush(stdout);
	tmp = "";
	printf("  ft_puts called with \"%s\" : \"", tmp);
	fflush(stdout);
	ft_puts(tmp);
	fflush(stdout);
	printf("\"\n");
	fflush(stdout);
	tmp = "a";
	printf("  ft_puts called with \"%s\" : \"", tmp);
	fflush(stdout);
	ft_puts(tmp);
	fflush(stdout);
	printf("\"\n");
	fflush(stdout);
	tmp = "é";
	printf("  ft_puts called with \"%s\" : \"", tmp);
	fflush(stdout);
	ft_puts(tmp);
	fflush(stdout);
	printf("\"\n");
	fflush(stdout);
	tmp = NULL;
	printf("  ft_puts called with NULL : \"");
	fflush(stdout);
	ft_puts(tmp);
	fflush(stdout);
	printf("\"\n");
	fflush(stdout);
}

void	test_strlen(void)
{
	char	*tmp;

	printf("ft_strlen :\n");
	tmp = "salut";
	printf("  ft_strlen of \"%s\" : %ld\n", tmp, ft_strlen(tmp));
	tmp = "";
	printf("  ft_strlen of \"%s\" : %ld\n", tmp, ft_strlen(tmp));
	tmp = "lol";
	printf("  ft_strlen of \"%s\" : %ld\n", tmp, ft_strlen(tmp));
	tmp = " ";
	printf("  ft_strlen of \"%s\" : %ld\n", tmp, ft_strlen(tmp));
}

char	check_memset(char *str, char c, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

char	ft_strequ(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (str1[i] != str2[i])
		return (0);
	return (1);
}

void	test_memset(void)
{
	char	*tmp;
	char	*tmp2;
	size_t	size;

	tmp = NULL;
	printf("ft_memset :\n");
	printf("  will it crash with a len of 0... ");
	ft_memset(tmp, 0, 0);
	printf("apparently not\n");
	size = sizeof(char) * 351;
	tmp = (char*)malloc(size + sizeof(char));
	tmp2 = (char*)malloc(size);
	printf("  ft_memset called with 0 on 351 bytes long str, checking... ");
	ft_memset(tmp, 0, size);
	printf(check_memset(tmp, 0, size) ? "ok\n" : "not ok\n");
	printf("  ft_memset called with 10 on 351 bytes long str, checking... ");
	ft_memset(tmp, 10, size);
	printf(check_memset(tmp, 10, size) ? "ok\n" : "not ok\n");
	printf("  ft_memset called with 'a' on 351 bytes long str, checking... ");
	ft_memset(tmp, 'a', size);
	printf(check_memset(tmp, 'a', size) ? "ok\n" : "not ok\n");
	printf("  checking that the return value of memset == ft_memset for 128... ");
	ft_memset(tmp, 128, size);
	memset(tmp2, 128, size);
	tmp[size] = '\0';
	tmp2[size] = '\0';
	printf(ft_strequ(tmp, tmp2) ? "ok\n" : "not ok\n");
	printf("  checking that the return value of memset == ft_memset for 256... ");
	ft_memset(tmp, 256, size);
	memset(tmp2, 256, size);
	tmp[size] = '\0';
	tmp2[size] = '\0';
	printf(ft_strequ(tmp, tmp2) ? "ok\n" : "not ok\n");
	printf("  checking that the return value of memset == ft_memset for 257... ");
	ft_memset(tmp, 257, size);
	memset(tmp2, 257, size);
	tmp[size] = '\0';
	tmp2[size] = '\0';
	printf(ft_strequ(tmp, tmp2) ? "ok\n" : "not ok\n");
	printf("  checking that the return value of memset == ft_memset for -257... ");
	ft_memset(tmp, -257, size);
	memset(tmp2, -257, size);
	tmp[size] = '\0';
	tmp2[size] = '\0';
	printf(ft_strequ(tmp, tmp2) ? "ok\n" : "not ok\n");
}

void	test_memcpy(void)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	printf("ft_memcpy :\n");
	tmp2 = (char*)malloc(sizeof(char) * 100);
	tmp = "salut";
	printf("  checking for \"%s\" : ", tmp);
	tmp3 = ft_memcpy(tmp2, tmp, strlen(tmp) + 1);
	printf("ret value %s, copy %s, ret : \"%s\"\n", tmp3 == tmp2 ? "ok" : "not ok", ft_strequ(tmp2, tmp) ? "ok" : "not ok", tmp3);
	tmp = "";
	printf("  checking for \"%s\" : ", tmp);
	tmp3 = ft_memcpy(tmp2, tmp, strlen(tmp) + 1);
	printf("ret value %s, copy %s, ret : \"%s\"\n", tmp3 == tmp2 ? "ok" : "not ok", ft_strequ(tmp2, tmp) ? "ok" : "not ok", tmp3);
	tmp = "传/傳 è à";
	printf("  checking for \"%s\" : ", tmp);
	tmp3 = ft_memcpy(tmp2, tmp, strlen(tmp) + 1);
	printf("ret value %s, copy %s, ret : \"%s\"\n", tmp3 == tmp2 ? "ok" : "not ok", ft_strequ(tmp2, tmp) ? "ok" : "not ok", tmp3);
	tmp = "une autre chaîne de caractères";
	printf("  checking for \"%s\" : ", tmp);
	tmp3 = ft_memcpy(tmp2, tmp, strlen(tmp) + 1);
	printf("ret value %s, copy %s, ret : \"%s\"\n", tmp3 == tmp2 ? "ok" : "not ok", ft_strequ(tmp2, tmp) ? "ok" : "not ok", tmp3);
}

void	test_strdup(void)
{
	char	*res;
	char	*tmp;

	printf("ft_strdup :\n");
	tmp = "salut";
	res = ft_strdup(tmp);
	printf("  ret for \"%s\" at address %p : address %p, value \"%s\"\n", tmp, tmp, res, res);
	tmp = "";
	res = ft_strdup(tmp);
	printf("  ret for \"%s\" at address %p : address %p, value \"%s\"\n", tmp, tmp, res, res);
	tmp = "une chaîne plus longue avec des caractères spéciaux";
	res = ft_strdup(tmp);
	printf("  ret for \"%s\" at address %p : address %p, value \"%s\"\n", tmp, tmp, res, res);
}

void	test_cat(void)
{
	int		fd;
	char	*str;

	printf("ft_cat :\n");
	printf("  writing text to file 'lol'...\n");
	fd = open("lol", O_RDWR | O_CREAT | O_TRUNC, 0777);
	str = "Salut, un petit texte pour le mettre dans mon fichier";
	write(fd, str, strlen(str));
	printf("  calling ft_cat on its file descriptor : \"");
	fflush(stdout);
	close(fd);
	fd = open("lol", O_RDONLY);
	ft_cat(fd);
	printf("\"\n");
	close(fd);
	printf("  ft_cat(-1) : \"");
	fflush(stdout);
	ft_cat(-1);
	fflush(stdout);
	printf("\"\n");
	printf("  ft_cat(1) : \"");
	fflush(stdout);
	ft_cat(1);
	fflush(stdout);
	printf("\"\n");
	printf("  ft_cat(2) : \"");
	fflush(stdout);
	ft_cat(2);
	fflush(stdout);
	printf("\"\n");
	printf("  ft_cat(255) : \"");
	fflush(stdout);
	ft_cat(255);
	fflush(stdout);
	printf("\"\n");
	printf("  ft_cat(0) (entrez du texte) : \n");
	fflush(stdout);
	ft_cat(0);
	fflush(stdout);
	printf("\n");
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
	test_strlen();
	test_memset();
	test_memcpy();
	test_strdup();
	test_cat();
	return (0);
}