#include "./Pack/Append.hpp"
#include "./Pack/Concat.hpp"
#include "./Pack/Drop.hpp"
#include "./Pack/Front.hpp"
#include "./Pack/Get.hpp"
#include "./Pack/Prepend.hpp"

int main() {
  AppendTest::run();
  ConcatTest::run();
  DropTest::run();
  FrontTest::run();
  GetTest::run();
  PrependTest::run();
}
