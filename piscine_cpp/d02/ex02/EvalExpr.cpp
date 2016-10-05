

#include "EvalExpr.hpp"

EvalExpr::EvalExpr() :
	_to_parse("0");
{
}

EvalExpr::EvalExpr(std::string const &to_parse) :
	_to_parse(to_parse);
{
}

EvalExpr::EvalExpr(EvalExpr &other)
{

}

EvalExpr::~EvalExpr()
{

}


EvalExpr	&EvalExpr::operator=(EvalExpr &other)
{
	this->_to_parse = other.getExpr();
	return *this;
}
