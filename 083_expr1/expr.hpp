#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long num;

 public:
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream str_stream;
    str_stream << num;

    return str_stream.str();
  }

  virtual ~NumExpression() {}
};

class operExpression : public Expression {
  const char * oper;
  Expression * l;
  Expression * r;

 public:
  operExpression(const char * oper, Expression * lhs, Expression * rhs) :
      oper(oper), l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream str_stream;
    str_stream << '(' << l->toString() << ' ' << *oper << ' ' << r->toString() << ')';

    return str_stream.str();
  }
  virtual ~operExpression() {
    delete l;
    delete r;
  }
};

class PlusExpression : public operExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : operExpression("+", lhs, rhs) {}
};
