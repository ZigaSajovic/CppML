cmake_minimum_required(VERSION 3.12)

add_executable(CppML_Algorithm_Test)
target_sources(
  CppML_Algorithm_Test
  PRIVATE
  src/Algorithm.cpp
)
target_include_directories(
  CppML_Algorithm_Test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_compile_features(CppML_Algorithm_Test PRIVATE cxx_std_14)

add_executable(CppML_Functional_Test)
target_sources(
  CppML_Functional_Test
  PRIVATE
  src/Functional.cpp
)
target_include_directories(
  CppML_Functional_Test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_compile_features(CppML_Functional_Test PRIVATE cxx_std_14)

add_executable(CppML_Pack_Test)
target_sources(
  CppML_Pack_Test
  PRIVATE
  src/Pack.cpp
)
target_include_directories(
  CppML_Pack_Test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_compile_features(CppML_Pack_Test PRIVATE cxx_std_14)

add_executable(CppML_TypeTraits_Test)
target_sources(
  CppML_TypeTraits_Test
  PRIVATE
  src/TypeTraits.cpp
)
target_include_directories(
  CppML_TypeTraits_Test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_compile_features(CppML_TypeTraits_Test PRIVATE cxx_std_14)
