#include "./Arithmetic/Add.hpp"
#include "./Arithmetic/Decrement.hpp"
#include "./Arithmetic/Divide.hpp"
#include "./Arithmetic/Equals.hpp"
#include "./Arithmetic/Greater.hpp"
#include "./Arithmetic/Increment.hpp"
#include "./Arithmetic/Less.hpp"
#include "./Arithmetic/Multiply.hpp"
#include "./Arithmetic/Not.hpp"
#include "./Arithmetic/Subtract.hpp"

int main() {
  AddTest::run();
  DecrementTest::run();
  DivideTest::run();
  EqualsTest::run();
  GreaterTest::run();
  IncrementTest::run();
  LessTest::run();
  MultiplyTest::run();
  NotTest::run();
  SubtractTest::run();
}
