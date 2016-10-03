

#include "Account.class.hpp"
#include <iostream>

Account::Account(void) : _accountIndex(Account::_nbAccounts), _amount(0), _nbDeposits(0), _nbWithdrawals(0)
{
	Account::_nbAccounts++;
}

Account::Account(int initial_deposit) : _accountIndex(Account::_nbAccounts), _nbDeposits(0), _nbWithdrawals(0)
{
	if (initial_deposit > 0)
	{
		this->_amount = initial_deposit;
		Account::_totalAmount += initial_deposit;
	}
	Account::_nbAccounts++;
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";created" << std::endl;
}

Account::~Account(void)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";closed" << std::endl;
	Account::_nbAccounts--;
	Account::_totalAmount -= this->_amount;
}

void	Account::makeDeposit(int deposit)
{
	if (deposit > 0)
	{
		Account::_displayTimestamp();
		std::cout << "index:" << this->_accountIndex << ";";
		std::cout << "p_amount:" << this->_amount << ";";
		std::cout << "deposit:" << deposit << ";";
		this->_amount += deposit;
		this->_nbDeposits++;
		Account::_totalAmount += deposit;
		Account::_totalNbDeposits++;
		std::cout << "amount:" << this->_amount << ";";
		std::cout << "nb_deposits:" << this->_nbDeposits << std::endl;
	}
}

bool	Account::makeWithdrawal(int withdrawal)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "p_amount:" << this->_amount << ";withdrawal:";
	if (withdrawal > this->_amount)
	{
		std::cout << "refused" << std::endl;
		return (false);
	}
	std::cout << withdrawal << ";";
	this->_amount -= withdrawal;
	this->_nbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
	return (true);
}

int		Account::checkAmount(void) const
{
	return this->_amount;
}

void	Account::displayStatus(void) const
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->_amount << ";";
	std::cout << "deposits:" << this->_nbDeposits << ";";
	std::cout << "withdrawals:" << this->_nbWithdrawals << std::endl;
}

std::string	maybe_zeroed(int inp)
{
	if (inp < 10)
		return "0" + std::to_string(inp);
	return std::to_string(inp);
}

void	Account::_displayTimestamp(void)
{
	time_t		current_time;
	struct tm	*my_time;

	current_time = time(0);
	my_time = localtime(&current_time);
	std::cout << "[";
	std::cout << (1900 + my_time->tm_year);
	std::cout << maybe_zeroed(my_time->tm_mon + 1);
	std::cout << maybe_zeroed(my_time->tm_mday);
	std::cout << "_";
	std::cout << maybe_zeroed(my_time->tm_hour);
	std::cout << maybe_zeroed(my_time->tm_min);
	std::cout << maybe_zeroed(my_time->tm_sec);
	std::cout << "] ";
}

int		Account::getNbAccounts(void)
{
	return Account::_nbAccounts;
}

int		Account::getTotalAmount(void)
{
	return Account::_totalAmount;
}

int		Account::getNbDeposits(void)
{
	return Account::_totalNbDeposits;
}

int		Account::getNbWithdrawals(void)
{
	return Account::_totalNbWithdrawals;
}

void		Account::displayAccountsInfos(void)
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() << ";";
	std::cout << "total:" << Account::getTotalAmount() << ";";
	std::cout << "deposits:" << Account::getNbDeposits() << ";";
	std::cout << "withdrawals:" << Account::getNbWithdrawals() << std::endl;
}

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;