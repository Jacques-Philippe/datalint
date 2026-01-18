from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import copy
import os


class DatalintLibConan(ConanFile):
    name = "datalintlib"
    version = "0.1.0"
    license = "MIT"
    author = "Jacques-Philippe Amiot <jacques.p.amiot@gmail.com>"
    url = "https://github.com/Jacques-Philippe/datalint"
    description = "A C++ library for data linting"
    topics = ("cpp", "data", "validation")
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,  # default to static
        "fPIC": True,
    }
    exports_sources = (
        "datalintlib/include/**",
        "datalintlib/src/**",
        "datalintlib/CMakeLists.txt",
    )
    generators = "CMakeDeps"

    def layout(self):
        # Let conan know the folder layout
        self.folders.source = "."
        self.folders.build = "build"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_CXX_STANDARD"] = 20
        tc.variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="datalintlib")
        cmake.build()

    def package(self):
        # install headers and library
        cmake = CMake(self)
        cmake.install()

        # fallback: manual copy if you don't have install target
        copy(
            self,
            "*.h",
            src=os.path.join(self.source_folder, "datalintlib/include"),
            dst=os.path.join(self.package_folder, "include"),
        )
        if self.options.shared:
            copy(
                self,
                "datalintlib.*",
                src=self.build_folder,
                dst=os.path.join(self.package_folder, "lib"),
                keep_path=False,
                symlinks=True,
            )
        else:
            copy(
                self,
                "*.lib",
                src=self.build_folder,
                dst=os.path.join(self.package_folder, "lib"),
                keep_path=False,
            )
            copy(
                self,
                "*.a",
                src=self.build_folder,
                dst=os.path.join(self.package_folder, "lib"),
                keep_path=False,
            )

    def package_info(self):
        self.cpp_info.libs = ["datalintlib"]
