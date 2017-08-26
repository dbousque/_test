

#include "IOperand.hpp"

class Float : public IOperand
{
  public:
    Float(float value);
    Float(Float &other);
    virtual ~Float();

    Float                 &operator=(Float &other);

    int                   getPrecision() const;
    eOperandType          getType() const;

    IOperand const        *operator+(IOperand const &rhs) const;
    IOperand const        *operator-(IOperand const &rhs) const;
    IOperand const        *operator*(IOperand const &rhs) const;
    IOperand const        *operator/(IOperand const &rhs) const;
    IOperand const        *operator%(IOperand const &rhs) const;

    std::string const     &toString() const;

  private:
    float                 _value;
};