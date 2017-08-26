

#include "IOperand.hpp"

class Int8 : public IOperand
{
  public:
    Int8();
    Int8(Int8 &other);
    virtual ~Int8();

    Int8                  &operator=(Int8 &other);

    int                   getPrecision() const;
    eOperandType          getType() const;

    IOperand const        *operator+(IOperand const &rhs) const;
    IOperand const        *operator-(IOperand const &rhs) const;
    IOperand const        *operator*(IOperand const &rhs) const;
    IOperand const        *operator/(IOperand const &rhs) const;
    IOperand const        *operator%(IOperand const &rhs) const;

    std::string const     &toString() const;

  private:
    int8_t                _value;
};