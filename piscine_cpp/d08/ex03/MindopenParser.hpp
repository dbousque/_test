

#ifndef MINDOPENPARSER_H
# define MINDOPENPARSER_H

#include <string>
#include "IInstruction.hpp"
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

class MindopenParser
{
	public:
		MindopenParser(std::string filename);
		MindopenParser(MindopenParser const &other);
		virtual ~MindopenParser();

		MindopenParser				&operator=(MindopenParser &other);
		std::vector<IInstruction*>	*parse();
		std::string					getFilename() const;

	private:
		std::string		_filename;
};

#endif