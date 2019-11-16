#include "./Algorithm/AllOf.hpp"
#include "./Algorithm/AnyOf.hpp"
#include "./Algorithm/Contains.hpp"
#include "./Algorithm/CountIf.hpp"
#include "./Algorithm/Filter.hpp"
#include "./Algorithm/FilterIds.hpp"
#include "./Algorithm/FindIf.hpp"
#include "./Algorithm/FindIfNot.hpp"
#include "./Algorithm/GroupBy.hpp"
#include "./Algorithm/GroupIdsBy.hpp"
#include "./Algorithm/InclusiveScan.hpp"
#include "./Algorithm/MaxElement.hpp"
#include "./Algorithm/NoneOf.hpp"
#include "./Algorithm/Partition.hpp"
#include "./Algorithm/PartitionIds.hpp"
#include "./Algorithm/Pivot.hpp"

int main() {
  AllOfTest::run();
  AnyOfTest::run();
  ContainsTest::run();
  CountIfTest::run();
  FilterTest::run();
  FilterIdsTest::run();
  FindIfTest::run();
  FindIfNotTest::run();
  GroupByTest::run();
  GroupIdsByTest::run();
  InclusiveScanTest::run();
  MaxElementTest::run();
  NoneOfTest::run();
  PartitionTest::run();
  PartitionIdsTest::run();
  PivotTest::run();
}
