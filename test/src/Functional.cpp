#include "./Functional/Bind.hpp"
#include "./Functional/BranchPipe.hpp"
#include "./Functional/Compose.hpp"
#include "./Functional/Constant.hpp"

int main() {
  BindTest::run();
  BranchPipeTest::run();
  ComposeTest::run();
  ConstantTest::run();
}
