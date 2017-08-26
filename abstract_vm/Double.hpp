

#include "IOperand.hpp"

class Double : public IOperand
{
  public:
    Double();
    Double(Double &other);
    virtual ~Double();

    Double                &operator=(Double &other);

    int                   getPrecision() const;
    eOperandType          getType() const;

    IOperand const        *operator+(IOperand const &rhs) const;
    IOperand const        *operator-(IOperand const &rhs) const;
    IOperand const        *operator*(IOperand const &rhs) const;
    IOperand const        *operator/(IOperand const &rhs) const;
    IOperand const        *operator%(IOperand const &rhs) const;

    std::string const     &toString() const;

  private:
    double                _value;
};