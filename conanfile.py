from conans import ConanFile, CMake

class Bncsutil(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"

    def requirements(self):
        if self.settings.os == "Windows":
            self.requires("mpir/3.0.0")
        else:
            self.requires("gmp/6.2.0")