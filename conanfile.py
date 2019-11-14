from conans import ConanFile, CMake


class CppMLConan(ConanFile):
  name = "CppML"
  version = "0.0.0"
  license = "MIT"
  author = "Ziga Sajovic -- ziga.sajovic+conan@xlab.si"
  url = "https://github.com/bernedom/SI"
  description = "A Meta Language for C++."
  topics = ("metaprogramming", "meta-programming",
            "template-meta-programming", "cplusplus-library")
  exports_sources = "include/*", "CMakeLists.txt", "cmake/CppMLConfig.cmake.in", "LICENSE"
  no_copy_source = True

  def _configure_cmake(self):
    cmake = CMake(self)
    cmake.configure()
    return cmake

  def build(self):
    cmake = self._configure_cmake()
    cmake.build()

  def test(self):
    cmake = self._configure_cmake()
    cmake.test()

  def package(self):
    cmake = self._configure_cmake()
    cmake.install()

  def package_id(self):
    self.info.header_only()
