

#include <iostream>
#include <string>

class Contact
{

public:
	Contact();
	~Contact();
	std::string	toStr(void) const;

	void		setFirstName(std::string value);
	void		setLastName(std::string value);
	void		setNickname(std::string value);
	void		setLogin(std::string value);
	void		setPostalAddress(std::string value);
	void		setEmailAddress(std::string value);
	void		setPhoneNumber(std::string value);
	void		setBirthdayDate(std::string value);
	void		setFavoriteMeal(std::string value);
	void		setUnderwearColor(std::string value);
	void		setDarkestSecret(std::string value);

	std::string	getFirstName() const;
	std::string	getLastName() const;
	std::string	getNickname() const;

private:
	std::string	_first_name;
	std::string	_last_name;
	std::string	_nickname;
	std::string	_login;
	std::string	_postal_address;
	std::string	_email_address;
	std::string	_phone_number;
	std::string	_birthday_date;
	std::string	_favorite_meal;
	std::string	_underwear_color;
	std::string	_darkest_secret;

};