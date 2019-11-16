cmake_minimum_required(VERSION 3.12)

add_executable(CppML_Algorithm_Test)
target_sources(CppML_Algorithm_Test
               PRIVATE
               src/Algorithm.cpp)
target_include_directories(
  CppML_Algorithm_Test
  PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
