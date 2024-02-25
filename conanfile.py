from conan import ConanFile
from conan.tools.files import copy
from conan.tools.files import rename
import os

class Bncsutil(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    requires = (
        "gmp/6.3.0",
    )

    def generate(self):
        # Workaround for a conan bug producing wrongly named libraries..
        if self.settings.os == "Windows":
            gmp_libdir = self.dependencies["gmp"].cpp_info.libdir
            gmp_from_name = f"{gmp_libdir}\libgmp.a"
            gmp_to_name = f"{gmp_libdir}\gmp.lib"
            gmpxx_from_name = f"{gmp_libdir}\libgmpxx.a"
            gmpxx_to_name = f"{gmp_libdir}\gmpxx.lib"

            if os.path.isfile(gmp_from_name):
                print("Renaming " + gmp_from_name + " to " + gmp_to_name)
                rename(self, gmp_from_name, gmp_to_name)
            if os.path.isfile(gmpxx_from_name):
                print("Renaming " + gmpxx_from_name + " to " + gmpxx_to_name)
                rename(self, gmpxx_from_name, gmpxx_to_name)

            for dep in self.dependencies.values():
                if dep.cpp_info.libdirs:
                    copy(self, "*.lib", dep.cpp_info.libdirs[0], self.build_folder)
                if dep.cpp_info.bindirs:
                    copy(self, "*.dll", dep.cpp_info.bindirs[0], self.build_folder)