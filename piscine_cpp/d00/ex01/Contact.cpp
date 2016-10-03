

#include "Contact.hpp"

Contact::Contact(void)
{
}

Contact::~Contact(void)
{
}

void		Contact::setFirstName(std::string value)
{
	this->_first_name = value;
}

void		Contact::setLastName(std::string value)
{
	this->_last_name = value;
}

void		Contact::setNickname(std::string value)
{
	this->_nickname = value;
}

void		Contact::setLogin(std::string value)
{
	this->_login = value;
}

void		Contact::setPostalAddress(std::string value)
{
	this->_postal_address = value;
}

void		Contact::setEmailAddress(std::string value)
{
	this->_email_address = value;
}

void		Contact::setPhoneNumber(std::string value)
{
	this->_phone_number = value;
}

void		Contact::setBirthdayDate(std::string value)
{
	this->_birthday_date = value;
}

void		Contact::setFavoriteMeal(std::string value)
{
	this->_favorite_meal = value;
}

void		Contact::setUnderwearColor(std::string value)
{
	this->_underwear_color = value;
}

void		Contact::setDarkestSecret(std::string value)
{
	this->_darkest_secret = value;
}

std::string	Contact::getFirstName(void) const
{
	return this->_first_name;
}

std::string	Contact::getLastName(void) const
{
	return this->_last_name;
}

std::string	Contact::getNickname(void) const
{
	return this->_nickname;
}

std::string	Contact::toStr(void) const
{	
	return _first_name + "\n" +
			_last_name + "\n" +
			_nickname + "\n" +
			_login + "\n" +
			_postal_address + "\n" +
			_email_address + "\n" +
			_phone_number + "\n" +
			_birthday_date + "\n" +
			_favorite_meal + "\n" +
			_underwear_color + "\n" +
			_darkest_secret;
}