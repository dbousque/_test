

#include "IOperand.hpp"

class Int16 : public IOperand
{
  public:
    Int16();
    Int16(Int16 &other);
    virtual ~Int16();

    Int16                 &operator=(Int16 &other);

    int                   getPrecision() const;
    eOperandType          getType() const;

    IOperand const        *operator+(IOperand const &rhs) const;
    IOperand const        *operator-(IOperand const &rhs) const;
    IOperand const        *operator*(IOperand const &rhs) const;
    IOperand const        *operator/(IOperand const &rhs) const;
    IOperand const        *operator%(IOperand const &rhs) const;

    std::string const     &toString() const;

  private:
    int16_t               _value;
};