

#include "Tintin_reporter.hpp"

Tintin_reporter::Tintin_reporter()
{

}

Tintin_reporter::Tintin_reporter(Tintin_reporter &other)
{
	(void)other;
}

Tintin_reporter::~Tintin_reporter()
{
}

Tintin_reporter    &Tintin_reporter::operator=(Tintin_reporter &other)
{
  return *(new Tintin_reporter(other));
}
