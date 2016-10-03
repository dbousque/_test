

#include <iostream>
#include <iomanip>
#include "Contact.hpp"

class Phonebook {

public:
	Phonebook();
	~Phonebook();
	void	launch(void);

private:
	Contact		_contacts[8];
	int			_current_ind;

	Contact		_getNContact(int n) const;
	void		_displayContacts(void) const;
	void		_displayContact(const Contact *contact, int ind) const;
	void		_addContact(void);
	void		_setField(void (Contact::*setter)(std::string), std::string name);

};