#include "./TypeTraits/CopyRefness.hpp"
#include "./TypeTraits/IfValidOr.hpp"
#include "./TypeTraits/IsSame.hpp"
#include "./TypeTraits/IsSameTemplate.hpp"
#include "./TypeTraits/IsValid.hpp"

int main() {
  CopyRefnessTest::run();
  IfValidOrTest::run();
  IsSameTest::run();
  IsSameTemplateTest::run();
  IsValidTest::run();
}
