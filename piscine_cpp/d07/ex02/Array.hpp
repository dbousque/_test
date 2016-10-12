

#ifndef ARRAY_H
# define ARRAY_H

#include <cstdlib>
#include <stdexcept>

template <typename T>
class Array
{
	public:
		Array() :
			_elts(reinterpret_cast<T*>(NULL)),
			_len(0)
		{
		}

		Array(unsigned int n)
		{
			this->_elts = new T[n];
			this->_len = n;
		}

		Array(Array &other)
		{
			if (other.size() == 0)
			{
				this->_elts = NULL;
				this->_len = 0;
			}
			else
			{
				this->_elts = new T[other.size()];
				for (size_t i = 0; i < other.size(); i++)
					this->_elts[i] = other.getElts()[i];
				this->_len = other.size();
			}
		}

		~Array()
		{
			if (this->_elts)
				delete [] this->_elts;
		}

		Array	&operator=(Array &other)
		{
			if (this->_len != 0)
				delete [] this->_elts;
			if (other.size() == 0)
			{
				this->_elts = NULL;
				this->_len = 0;
				return *this;
			}
			this->_elts = new T[other.size()];
			for (size_t i = 0; i < other.size(); i++)
				this->_elts[i] = other.getElts()[i];
			this->_len = other.size();
			return *this;
		}

		T		&operator[](int n)
		{
			if (n < 0 || static_cast<size_t>(n) >= this->_len)
				throw std::out_of_range("Array out of bounds");
			return this->_elts[n];
		}

		T		*getElts() const
		{
			return this->_elts;
		}

		size_t	size() const
		{
			return this->_len;
		}

	private:
		T		*_elts;
		size_t	_len;
};

#endif