

#include "NinjaTrap.hpp"
#include <iostream>

std::string const	default_name = "default_name";
std::string			ninja_name = "NinjaTrap ";

NinjaTrap::NinjaTrap() : ClapTrap(default_name, 60, 60, 120, 120, 1, 60, 5, 0, ninja_name)
{
	std::cout << "NinjaTrap: O-KAY! Thanks for giving me a second chance, God. I really appreciate it." << std::endl;
	std::cout << "Jack: What? No, nooo, you are so STUPID! Whatever. You're welcome." << std::endl;
}

NinjaTrap::NinjaTrap(std::string const &name) : ClapTrap(name, 60, 60, 120, 120, 1, 60, 5, 0, ninja_name)
{
	std::cout << "Jack: You. Are. Not. Dead! Your new designation is FR4G-TP. Fragtrap. You are a merciless killing machine. Got it?" << std::endl;
}

NinjaTrap::~NinjaTrap()
{
	std::cout << "NinjaTrap " << this->_name << " deleted" << std::endl;
}
