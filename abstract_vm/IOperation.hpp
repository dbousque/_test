

#ifndef IOPERATION_H
# define IOPERATION_H

class IOperation
{
  public:
    virtual               ~IOperation() {}
    virtual void          execute() const = 0;
}

#endif