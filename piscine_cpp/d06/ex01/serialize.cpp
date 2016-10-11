

#include <iomanip>
#include <iostream>

struct	Data
{
	std::string		s1;
	int				n;
	std::string		s2;
};

std::string	alphanumeric = "abcdefghijklmnopqrstuvwxyz0123456789";

void	dump_memory(void *addr, size_t size)
{
	unsigned char	*read_addr;

	read_addr = reinterpret_cast<unsigned char *>(addr);
	for (size_t i = 0; i < size; i++)
		std::cout << std::setbase(16) << static_cast<int>(read_addr[i]) << " ";
	std::cout << std::setbase(10) << std::endl;
}

void	*serialize(void)
{
	static bool		already_called = false;
	unsigned char	*data = new unsigned char[16 + sizeof(int)];

	if (!already_called)
	{
		already_called = true;
		srand(time(NULL));
	}
	for (int i = 0; i < 8; i++)
		data[i] = alphanumeric[rand() % alphanumeric.length()];
	*(reinterpret_cast<int*>(data + 8)) = rand();
	for (int i = 8 + sizeof(int); i < 8 + sizeof(int) + 8; i++)
		data[i] = alphanumeric[rand() % alphanumeric.length()];
	return reinterpret_cast<void*>(data);
}

Data	*deserialize(void *raw)
{
	unsigned char	*actual_raw;
	Data			*res = new Data;

	actual_raw = reinterpret_cast<unsigned char*>(raw);
	res->s1 = "";
	res->n = 0;
	res->s2 = "";
	for (int i = 0; i < 8; i++)
		res->s1 += actual_raw[i];
	res->n = *(reinterpret_cast<int*>(actual_raw + 8));
	for (int i = 8 + sizeof(int); i < 8 + sizeof(int) + 8; i++)
		res->s2 += actual_raw[i];
	return res;
}

unsigned char	*eight_first(unsigned char *str)
{
	unsigned char	*res = new unsigned char[9];

	for (int i = 0; i < 8; i++)
		res[i] = str[i];
	res[8] = '\0';
	return res;
}

int		main(void)
{
	void			*raw = serialize();
	unsigned char	*data;
	Data			*deserialized_data;
	unsigned char	*tmp;

	std::cout << "Dumping raw memory received from serialize() :" << std::endl;
	dump_memory(raw, 16 + sizeof(int));
	data = reinterpret_cast<unsigned char*>(raw);
	tmp = eight_first(data);
	std::cout << " -> which reads as [\"" << tmp;
	delete tmp;
	tmp = eight_first(data + 8 + sizeof(int));
	std::cout << "\", " << *(reinterpret_cast<int*>(data + 8)) << ", \"" << tmp;
	delete tmp;
	std::cout << "\"]" << std::endl;

	deserialized_data = deserialize(raw);
	std::cout << std::endl << "Deserialized data :" << std::endl;
	std::cout << "s1 : " << deserialized_data->s1 << std::endl;
	std::cout << "n  : " << deserialized_data->n << std::endl;
	std::cout << "s2 : " << deserialized_data->s2 << std::endl;

	delete data;
	delete deserialized_data;
	return (0);
}