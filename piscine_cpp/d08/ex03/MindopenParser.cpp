

#include "MindopenParser.hpp"
#include "IncrementByte.hpp"
#include "OutputByte.hpp"
#include "LoopStart.hpp"
#include "DecrementByte.hpp"
#include "LoopEnd.hpp"
#include "Decrement.hpp"
#include "Increment.hpp"
#include "AcceptByte.hpp"

MindopenParser::MindopenParser(std::string filename) :
	_filename(filename)
{
}

MindopenParser::MindopenParser(MindopenParser const &other) :
	_filename(other.getFilename())
{
}

MindopenParser::~MindopenParser()
{
}

MindopenParser				&MindopenParser::operator=(MindopenParser &other)
{
	this->_filename = other.getFilename();
	return *this;
}

std::vector<IInstruction*>	*MindopenParser::parse()
{
	std::vector<IInstruction*>	*instructions = new std::vector<IInstruction*>;
	if (access(this->_filename.c_str(), R_OK))
		return instructions;
	struct stat		mstat;
	stat(this->_filename.c_str(), &mstat);
	if (mstat.st_mode & S_IFDIR)
		return instructions;
	char	c;
	std::ifstream	ifs(this->_filename);

	while (ifs.read(&c, 1))
	{
		switch (c)
		{
			case 'p':
				instructions->push_back(new IncrementByte());
				break;
			case 'm':
				instructions->push_back(new DecrementByte());
				break;
			case 'd':
				instructions->push_back(new Increment());
				break;
			case 'g':
				instructions->push_back(new Decrement());
				break;
			case '.':
				instructions->push_back(new OutputByte());
				break;
			case ',':
				instructions->push_back(new AcceptByte());
				break;
			case '[':
				instructions->push_back(new LoopStart());
				break;
			case ']':
				instructions->push_back(new LoopEnd());
				break;
		}
	}
	return instructions;
}

std::string					MindopenParser::getFilename() const
{
	return this->_filename;
}