#include "./Pack/Append.hpp"
#include "./Pack/Concat.hpp"
#include "./Pack/Drop.hpp"
#include "./Pack/Prepend.hpp"

int main() {
  AppendTest::run();
  ConcatTest::run();
  DropTest::run();
  PrependTest::run();
}
