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
#include "./Algorithm/Reduce.hpp"
#include "./Algorithm/RemoveIdsIf.hpp"
#include "./Algorithm/RemoveIf.hpp"
#include "./Algorithm/Rotate.hpp"

int main() {
  AllOfTest::run();
  AnyOfTest::run();
  ContainsTest::run();
  CountIfTest::run();
  FilterIdsTest::run();
  FilterTest::run();
  FindIfNotTest::run();
  FindIfTest::run();
  GroupByTest::run();
  GroupIdsByTest::run();
  InclusiveScanTest::run();
  MaxElementTest::run();
  NoneOfTest::run();
  PartitionIdsTest::run();
  PartitionTest::run();
  PivotTest::run();
  ReduceTest::run();
  RemoveIdsIfTest::run();
  RemoveIfTest::run();
  RotateTest::run();
}
