

#include <string>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <cerrno>
#include <limits.h>
#include <iomanip>
#include <sstream>
#include <limits>

double		get_double(std::string input, bool *error)
{
	char	*end;
	double	res;

	if (input == "nan" || input == "nanf")
		return std::numeric_limits<double>::quiet_NaN();
	if (input == "+inff" || input == "+inf")
		return std::numeric_limits<double>::infinity();
	if (input == "-inff" || input == "-inf")
		return -std::numeric_limits<double>::infinity();
	end = NULL;
	res = strtod(input.c_str(), &end);
	if (*end != '\0' || errno != 0 || res == HUGE_VAL || res == -HUGE_VAL)
	{
		if (input.c_str() != end && *end == 'f' && *(end + 1) == '\0')
		{
			*end = '\0';
			res = get_double(input, error);
			*end = 'f';
			return res;
		}
		*error = true;
		return (0.0);
	}
	return res;
}

std::string		get_float_format(double val)
{
	std::ostringstream	stri;
	int					point;

	if (std::isnan(val))
		return "nan";
	if (val == -std::numeric_limits<double>::infinity())
		return "-inf";
	if (std::isinf(val))
		return "+inf";
	stri << val;
	std::string res = stri.str();
	point = -1;
	for (size_t i = 0; i < res.length(); i++)
	{
		if (res[i] == '.')
			point = i;
	}
	if (point == -1)
		return res + ".0";
	for (size_t i = res.length() - 1; i > 0; i--)
	{
		if (res[i] == '0' && res[i - 1] != '.')
			res[i] = '\0';
		else
			break ;
	}
	return res;
}

void	convert_char(std::string input, double val)
{
	char		c;

	if (val > nextafter(CHAR_MAX, 0) || val < nextafter(CHAR_MIN, 0)
		|| std::isnan(val) || std::isinf(val))
	{
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	if (input.length() == 1)
	{
		if (input[0] < 32 || input[0] >= 127)
		{
			std::cout << "char: Non displayable" << std::endl;
			return ;
		}
		else if (input[0] < '0' || input[0] > '9')
		{
			std::cout << "char: '" << input << "'" << std::endl;
			return ;
		}
	}
	c = static_cast<char>(val);
	if (c < 32 || c >= 127)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << c << "'" << std::endl;
}

void	convert_int(double val)
{
	int			res;

	if (val > nextafter(INT_MAX, 0) || val < nextafter(INT_MIN, 0) || std::isnan(val))
	{
		std::cout << "int: impossible" << std::endl;
		return ;
	}
	res = static_cast<int>(val);
	std::cout << "int: " << res << std::endl;
}

void	convert_float(double val)
{
	float		res;

	if (!std::isnan(val) && !std::isinf(val))
	{
		if (val > std::numeric_limits<float>::max() || val < std::numeric_limits<float>::lowest())
		{
			std::cout << "float: impossible" << std::endl;
			return ;
		}
	}
	res = static_cast<float>(val);
	std::cout << "float: " << get_float_format(res) << "f" << std::endl;
}

void	convert_double(double val)
{
	std::cout << "double: " << get_float_format(val) << std::endl;
}

void	convert(char *input)
{
	std::string		str_inp = static_cast<std::string>(input);
	double			val;
	bool			error;

	error = false;
	val = get_double(str_inp, &error);
	if (error)
	{
		if (str_inp.length() == 1)
			convert_char(str_inp, val);
		else
			std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return ;
	}
	convert_char(str_inp, val);
	convert_int(val);
	convert_float(val);
	convert_double(val);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Format : ./convert <string_literal>" << std::endl;
		return (0);
	}
	convert(argv[1]);
	return (0);
}