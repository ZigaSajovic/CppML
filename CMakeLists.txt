#--
# Copyright Ziga Sajovic, XLAB 2019
# Distributed under the MIT License
#
# https://github.com/ZigaSajovic/CppML

#--
# CppML's CMake scripts are based on approaches outlined in
# Cmake line by line - creating a header-only library
# (http://dominikberner.ch/cmake-interface-lib/)
#--
cmake_minimum_required(VERSION 3.12)
project("CppML" VERSION 0.0.0
                DESCRIPTION "A Meta Language for C++."
                HOMEPAGE_URL "https://github.com/ZigaSajovic/CppML"
                LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
 
add_library(${PROJECT_NAME} INTERFACE)
# Allow linking when CppML is a subproject
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if(BUILD_TESTS)
  add_subdirectory(./test)
endif()
 
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
 
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
 
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)
 
configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
 
install(EXPORT ${PROJECT_NAME}_Targets
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
 
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
