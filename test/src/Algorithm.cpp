#include "./Algorithm/AllOf.hpp"
#include "./Algorithm/AnyOf.hpp"
#include "./Algorithm/Contains.hpp"
#include "./Algorithm/CountIf.hpp"
#include "./Algorithm/Filter.hpp"
#include "./Algorithm/FilterIds.hpp"
#include "./Algorithm/FindIdIf.hpp"
#include "./Algorithm/FindIdIfNot.hpp"
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
#include "./Algorithm/ReplaceIf.hpp"
#include "./Algorithm/Rotate.hpp"
#include "./Algorithm/Unique.hpp"
#include "./Algorithm/UniqueCompare.hpp"
#include "./Algorithm/ZipWith.hpp"
#include "./Algorithm/ZipWithVariadic.hpp"

int main() {
  AllOfTest::run();
  AnyOfTest::run();
  ContainsTest::run();
  CountIfTest::run();
  FilterIdsTest::run();
  FilterTest::run();
  FindIdIfNotTest::run();
  FindIdIfTest::run();
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
  ReplaceIfTest::run();
  RotateTest::run();
  UniqueCompareTest::run();
  UniqueTest::run();
  ZipWithTest::run();
  ZipWithVariadicTest::run();
}
