#include "./Pack/Append.hpp"
#include "./Pack/Concat.hpp"
#include "./Pack/Drop.hpp"
#include "./Pack/Front.hpp"
#include "./Pack/Get.hpp"
#include "./Pack/Head.hpp"
#include "./Pack/Insert.hpp"
#include "./Pack/Length.hpp"
#include "./Pack/PackExtractor.hpp"
#include "./Pack/Prepend.hpp"
#include "./Pack/Range.hpp"
#include "./Pack/Tail.hpp"

int main() {
  AppendTest::run();
  ConcatTest::run();
  DropTest::run();
  FrontTest::run();
  GetTest::run();
  HeadTest::run();
  InsertTest::run();
  LengthTest::run();
  PackExtractorTest::run();
  PrependTest::run();
  RangeTest::run();
  TailTest::run();
}
