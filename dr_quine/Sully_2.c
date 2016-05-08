

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

static char	*ft_get_array(int n, int *length)
{
	int		signe;
	char	*res;

	*length = 0;
	signe = 1;
	if (n == 0)
		*length = 1;
	if (n < 0)
	{
		*length = 1;
		signe = -1;
	}
	while (n != 0)
	{
		n /= 10;
		(*length)++;
	}
	if (!(res = (char*)malloc(sizeof(char) * (*length + 1))))
		return (NULL);
	if (signe == -1)
		res[0] = '-';
	else
		res[0] = '0';
	return (res);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		length;

	res = ft_get_array(n, &length);
	if (res == NULL)
		return (NULL);
	res[length] = '\0';
	length--;
	while (length >= 0)
	{
		if (length != 0 || res[length] != '-')
		{
			if (n < 0)
				res[length] = -(n % 10) + '0';
			else
				res[length] = n % 10 + '0';
		}
		n /= 10;
		length--;
	}
	return (res);
}

void	write_no_real(char *str, int fd)
{
	while (*str)
	{
		if (*str == '"')
			write(fd, "\\\"", 2);
		else if (*str == '\n')
			write(fd, "\\n", 2);
		else if (*str == '\t')
			write(fd, "\\t", 2);
		else if (*str == '\\')
			write(fd, "\\\\", 2);
		else
			write(fd, str, 1);
		str++;
	}
}

int		ft_strlen(const char *s)
{
	int		length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		length;
	char	*res;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	length = 0;
	while (s1[length])
	{
		res[length] = s1[length];
		length++;
	}
	i = 0;
	while (s2[i])
	{
		res[length + i] = s2[i];
		i++;
	}
	res[length + i] = '\0';
	return (res);
}

int		main(int argc, char **argv)
{
	char	*str;
	char	*filename;
	char	*command;
	int		fd;
	int		len;
(void)argc;
	int i = 2;
	if (i <= 0)
		return (0);
	len = ft_strlen(argv[0]) - 1;
	while (len >= 0 && argv[0][len] == ' ')
		len--;
	if (len > 4 && argv[0][len - 4] == 'S' && argv[0][len - 3] == 'u' && argv[0][len - 2] == 'l' && argv[0][len - 1] == 'l' && argv[0][len] == 'y')
		i++;
	if (!(filename = ft_strjoin(ft_strjoin("Sully_", ft_itoa(i - 1)), ".c")))
		return (0);
	if ((fd = open(filename, O_RDWR | O_CREAT | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		return (0);
	if (!(command = ft_strjoin("gcc -Wall -Wextra -Werror ", filename)))
		return (0);
	filename[ft_strlen(filename) - 2] = '\0';
	if (!(command = ft_strjoin(ft_strjoin(command, " -o "), filename)))
		return (0);
	if (!(command = ft_strjoin(ft_strjoin(command, " && ./"), filename)))
		return (0);
	str = "\n\n#include <unistd.h>\n#include <fcntl.h>\n#include <sys/stat.h>\n#include <stdlib.h>\n\nstatic char\t*ft_get_array(int n, int *length)\n{\n\tint\t\tsigne;\n\tchar\t*res;\n\n\t*length = 0;\n\tsigne = 1;\n\tif (n == 0)\n\t\t*length = 1;\n\tif (n < 0)\n\t{\n\t\t*length = 1;\n\t\tsigne = -1;\n\t}\n\twhile (n != 0)\n\t{\n\t\tn /= 10;\n\t\t(*length)++;\n\t}\n\tif (!(res = (char*)malloc(sizeof(char) * (*length + 1))))\n\t\treturn (NULL);\n\tif (signe == -1)\n\t\tres[0] = '-';\n\telse\n\t\tres[0] = '0';\n\treturn (res);\n}\n\nchar\t\t*ft_itoa(int n)\n{\n\tchar\t*res;\n\tint\t\tlength;\n\n\tres = ft_get_array(n, &length);\n\tif (res == NULL)\n\t\treturn (NULL);\n\tres[length] = '\\0';\n\tlength--;\n\twhile (length >= 0)\n\t{\n\t\tif (length != 0 || res[length] != '-')\n\t\t{\n\t\t\tif (n < 0)\n\t\t\t\tres[length] = -(n % 10) + '0';\n\t\t\telse\n\t\t\t\tres[length] = n % 10 + '0';\n\t\t}\n\t\tn /= 10;\n\t\tlength--;\n\t}\n\treturn (res);\n}\n\nvoid\twrite_no_real(char *str, int fd)\n{\n\twhile (*str)\n\t{\n\t\tif (*str == '\"')\n\t\t\twrite(fd, \"\\\\\\\"\", 2);\n\t\telse if (*str == '\\n')\n\t\t\twrite(fd, \"\\\\n\", 2);\n\t\telse if (*str == '\\t')\n\t\t\twrite(fd, \"\\\\t\", 2);\n\t\telse if (*str == '\\\\')\n\t\t\twrite(fd, \"\\\\\\\\\", 2);\n\t\telse\n\t\t\twrite(fd, str, 1);\n\t\tstr++;\n\t}\n}\n\nint\t\tft_strlen(const char *s)\n{\n\tint\t\tlength;\n\n\tlength = 0;\n\twhile (s[length])\n\t\tlength++;\n\treturn (length);\n}\n\nchar\t*ft_strjoin(char const *s1, char const *s2)\n{\n\tint\t\tlength;\n\tchar\t*res;\n\tint\t\ti;\n\n\tif (s1 == NULL || s2 == NULL)\n\t\treturn (NULL);\n\tlength = ft_strlen(s1) + ft_strlen(s2);\n\tif (!(res = (char*)malloc(sizeof(char) * (length + 1))))\n\t\treturn (NULL);\n\tlength = 0;\n\twhile (s1[length])\n\t{\n\t\tres[length] = s1[length];\n\t\tlength++;\n\t}\n\ti = 0;\n\twhile (s2[i])\n\t{\n\t\tres[length + i] = s2[i];\n\t\ti++;\n\t}\n\tres[length + i] = '\\0';\n\treturn (res);\n}\n\nint\t\tmain(int argc, char **argv)\n{\n\tchar\t*str;\n\tchar\t*filename;\n\tchar\t*command;\n\tint\t\tfd;\n\tint\t\tlen;\n(void)argc;\n\tint i = ;\n\tif (i <= 0)\n\t\treturn (0);\n\tlen = ft_strlen(argv[0]) - 1;\n\twhile (len >= 0 && argv[0][len] == ' ')\n\t\tlen--;\n\tif (len > 4 && argv[0][len - 4] == 'S' && argv[0][len - 3] == 'u' && argv[0][len - 2] == 'l' && argv[0][len - 1] == 'l' && argv[0][len] == 'y')\n\t\ti++;\n\tif (!(filename = ft_strjoin(ft_strjoin(\"Sully_\", ft_itoa(i - 1)), \".c\")))\n\t\treturn (0);\n\tif ((fd = open(filename, O_RDWR | O_CREAT | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)\n\t\treturn (0);\n\tif (!(command = ft_strjoin(\"gcc -Wall -Wextra -Werror \", filename)))\n\t\treturn (0);\n\tfilename[ft_strlen(filename) - 2] = '\\0';\n\tif (!(command = ft_strjoin(ft_strjoin(command, \" -o \"), filename)))\n\t\treturn (0);\n\tif (!(command = ft_strjoin(ft_strjoin(command, \" && ./\"), filename)))\n\t\treturn (0);\n\tstr = \"\";\n\twrite(fd, str, 1777);\n\twrite(fd, ft_itoa(i - 1), ft_strlen(ft_itoa(i - 1)));\n\twrite(fd, str + 1777, 767);\n\twrite_no_real(str, fd);\n\twrite(fd, str + 2544, 197);\n\tsystem(command);\n\treturn (0);\n}\n";
	write(fd, str, 1777);
	write(fd, ft_itoa(i - 1), ft_strlen(ft_itoa(i - 1)));
	write(fd, str + 1777, 767);
	write_no_real(str, fd);
	write(fd, str + 2544, 197);
	system(command);
	return (0);
}
