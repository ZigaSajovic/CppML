#include "./TypeTraits/AlignOf.hpp"
#include "./TypeTraits/CopyRefness.hpp"
#include "./TypeTraits/IfValidOr.hpp"
#include "./TypeTraits/IsClass.hpp"
#include "./TypeTraits/IsConstructible.hpp"
#include "./TypeTraits/IsConvertible.hpp"
#include "./TypeTraits/IsSame.hpp"
#include "./TypeTraits/IsSameTemplate.hpp"
#include "./TypeTraits/IsValid.hpp"

int main() {
  AlignOfTest::run();
  CopyRefnessTest::run();
  IfValidOrTest::run();
  IsClassTest::run();
  IsConstructibleTest::run();
  IsConvertibleTest::run();
  IsSameTest::run();
  IsSameTemplateTest::run();
  IsValidTest::run();
}
