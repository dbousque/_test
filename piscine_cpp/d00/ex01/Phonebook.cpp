

#include "Phonebook.hpp"

Phonebook::Phonebook() : _current_ind(0)
{
}

Phonebook::~Phonebook()
{
}

void	Phonebook::_setField(void (Contact::*setter)(std::string), std::string name)
{
	std::string	input;

	std::cout << name << " : ";
	getline(std::cin, input);
	(this->_contacts[this->_current_ind].*setter)(input);
}

void	Phonebook::_addContact(void)
{
	if (this->_current_ind == 8)
	{
		std::cout << "The phonebook is full, you cannot add a new entry." << std::endl;
		return ;
	}
	std::cout << " - Enter a new contact :" << std::endl;

	this->_setField(&Contact::setFirstName, "First name");
	this->_setField(&Contact::setLastName, "Last name");
	this->_setField(&Contact::setNickname, "Nickname");
	this->_setField(&Contact::setLogin, "Login");
	this->_setField(&Contact::setPostalAddress, "Postal address");
	this->_setField(&Contact::setEmailAddress, "Email address");
	this->_setField(&Contact::setPhoneNumber, "Phone number");
	this->_setField(&Contact::setBirthdayDate, "Birthday date");
	this->_setField(&Contact::setFavoriteMeal, "Favorite meal");
	this->_setField(&Contact::setUnderwearColor, "Underwear color");
	this->_setField(&Contact::setDarkestSecret, "Darkest secret");

	std::cout << std::endl;
	this->_current_ind++;
}

std::string	nTimesChar(int n, char c)
{
	std::string	res;

	res = "";
	for (int i = 0; i < n; i++)
	{
		res += c;
	}
	return (res);
}

void	Phonebook::_displayContact(const Contact *contact, int ind) const
{
	std::string	index;
	std::string	first_name;
	std::string	last_name;
	std::string	nickname;

	index = std::to_string(ind);
	if (index.length() < 10)
		index = nTimesChar(10 - index.length(), ' ') + index;
	first_name = contact->getFirstName();
	last_name = contact->getLastName();
	nickname = contact->getNickname();
	if (first_name.length() > 10)
		first_name = first_name.substr(0, 9) + ".";
	if (last_name.length() > 10)
		last_name = last_name.substr(0, 9) + ".";
	if (nickname.length() > 10)
		nickname = nickname.substr(0, 9) + ".";
	std::cout << std::setw(10) << index << "|";
	std::cout << std::setw(10) << first_name << "|";
	std::cout << std::setw(10) << last_name << "|";
	std::cout << std::setw(10) << nickname << std::endl;
}

int		getRawInt(std::string inp)
{
	if (inp.length() > 2)
		return (-1);
	for (size_t i = 0; i < inp.length(); i++)
	{
		if (!std::isdigit(inp[i]))
			return (-1);
	}
	return (std::stoi(inp));
}

void	Phonebook::_displayContacts(void) const
{
	int			index;
	std::string	inp;

	if (this->_current_ind == 0)
	{
		std::cout << "No entry yet" << std::endl;;
		return ;
	}
	std::cout << "   Index  |First name|Last name | Nickname " << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
	for (int i = 0; i < this->_current_ind; i++)
	{
		this->_displayContact(&(this->_contacts[i]), i);
	}
	std::cout << std::endl << "Index : ";
	getline(std::cin, inp);
	index = getRawInt(inp);
	if (index < 0 || index >= this->_current_ind)
	{
		std::cout << "Invalid index" << std::endl;
		return ;
	}
	std::cout << this->_contacts[index].toStr() << std::endl << std::endl;
}

void	Phonebook::launch(void)
{
	std::string	command;

	while (true)
	{
		std::cout << "Enter a command : ";
		getline(std::cin, command);
		if (command == "EXIT")
		{
			std::cout << "Goodbye." << std::endl;
			return ;
		}
		if (command == "ADD")
			this->_addContact();
		else if (command == "SEARCH")
		{
			this->_displayContacts();
		}
		else
			std::cout << "Unexpected command" << std::endl;
	}
}