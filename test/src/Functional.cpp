#include "./Functional/Bind.hpp"
#include "./Functional/BranchPipe.hpp"
#include "./Functional/Compose.hpp"
#include "./Functional/Constant.hpp"
#include "./Functional/Curry.hpp"
#include "./Functional/CurryR.hpp"
#include "./Functional/Identity.hpp"
#include "./Functional/IfElse.hpp"
#include "./Functional/InvokeWith.hpp"
#include "./Functional/Map.hpp"
#include "./Functional/Partial.hpp"
#include "./Functional/PartialR.hpp"
#include "./Functional/Product.hpp"
#include "./Functional/ProductMap.hpp"
#include "./Functional/ToList.hpp"
#include "./Functional/Unwrap.hpp"

int main() {
  BindTest::run();
  BranchPipeTest::run();
  ComposeTest::run();
  ConstantTest::run();
  CurryTest::run();
  CurryRTest::run();
  IdentityTest::run();
  IfElseTest::run();
  InvokeWithTest::run();
  MapTest::run();
  PartialTest::run();
  PartialRTest::run();
  ProductTest::run();
  ProductMapTest::run();
  ToListTest::run();
  UnwrapTest::run();
}
