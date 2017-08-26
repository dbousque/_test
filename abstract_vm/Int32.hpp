

#include "IOperand.hpp"

class Int32 : public IOperand
{
  public:
    Int32();
    Int32(Int32 &other);
    virtual ~Int32();

    Int32                 &operator=(Int32 &other);

    int                   getPrecision() const;
    eOperandType          getType() const;

    IOperand const        *operator+(IOperand const &rhs) const;
    IOperand const        *operator-(IOperand const &rhs) const;
    IOperand const        *operator*(IOperand const &rhs) const;
    IOperand const        *operator/(IOperand const &rhs) const;
    IOperand const        *operator%(IOperand const &rhs) const;

    std::string const     &toString() const;

  private:
    int32_t               _value;
};