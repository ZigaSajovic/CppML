#include "./Algorithm/AllOf.hpp"
#include "./Algorithm/AnyOf.hpp"
#include "./Algorithm/Contains.hpp"
#include "./Algorithm/CountIf.hpp"
#include "./Algorithm/Filter.hpp"
#include "./Algorithm/FilterIds.hpp"
#include "./Algorithm/NoneOf.hpp"

int main() {
  AllOf_Test::run();
  AnyOf_Test::run();
  NoneOf_Test::run();
  Contains_Test::run();
}
