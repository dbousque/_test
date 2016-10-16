#include "CatModule.hpp"

CatModule::CatModule() 
{
	std::string *title = new std::string("CAT");
	std::string *ears = new std::string("\\    /\\");
	std::string *eyes = new std::string(" )  ( ')");
	std::string *body = new std::string("(  /  )");
	std::string *legs = new std::string("\\(__)|");

	std::string *str = new std::string("~~~~~~~~~~~~");

	this->_fields.push_back(new Field(static_cast<void*>(title), Field::MODULE_TITLE));	//0
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::STRING));			//1
	this->_fields.push_back(new Field(static_cast<void*>(ears), Field::STRING));		//2 ears
	this->_fields.push_back(new Field(static_cast<void*>(eyes), Field::STRING));		//3 eyes
	this->_fields.push_back(new Field(static_cast<void*>(body), Field::STRING));		//4 body
	this->_fields.push_back(new Field(static_cast<void*>(legs), Field::STRING));		//5 legs
	this->_fields.push_back(new Field(static_cast<void*>(str), Field::STRING));			//6
}

CatModule::CatModule(CatModule &other):
	_fields(*(other.getFields()))
{
	
}

CatModule::~CatModule()
{
}

CatModule	&CatModule::operator=(CatModule &other)
{
	this->_fields = *(other.getFields());
	return *this;
}


void				CatModule::update()
{
	static int frame = 0;
	std::string *eyes;
	std::string *legs;

	if (frame % FRAME == 1) {
		eyes = new std::string("  )  ( -)");
		legs = new std::string(" \\(__)\\");
	}
	else if (frame % FRAME == 2) {
		eyes = new std::string("  )  ( ')");
		legs = new std::string(" \\(__)|");
	}
	else if (frame % FRAME == 3) {
		eyes = new std::string("  )  ( -)");
		legs = new std::string(" \\(__)\\");
	}
	else {
		eyes = new std::string("  )  ( ')");
		legs = new std::string(" \\(__)|");
	}

	frame++;

	Field *tmp = new Field(static_cast<void*>(eyes), Field::STRING);
	delete this->_fields[3];
	this->_fields[3] = tmp;

	Field *tmp2 = new Field(static_cast<void*>(legs), Field::STRING);
	delete this->_fields[5];
	this->_fields[5] = tmp2;
}


std::vector<Field*>	*CatModule::getFields()
{
	return &(this->_fields);
}
