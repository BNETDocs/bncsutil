from conan import ConanFile
from conan.tools.files import copy

class Bncsutil(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    requires = (
        "gmp/6.3.0",
    )

    def generate(self):
        for dep in self.dependencies.values():
            if dep.cpp_info.libdirs:
                copy(self, "*.lib", dep.cpp_info.libdirs[0], self.build_folder)
            if dep.cpp_info.bindirs:
                copy(self, "*.dll", dep.cpp_info.bindirs[0], self.build_folder)