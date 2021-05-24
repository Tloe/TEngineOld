from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conans.tools import os_info, vcvars, which
import os, shutil

class TEngine(ConanFile):
    name = "tengine"
    version = "0.1"
    license = "Copyright (c) Terje Loe 2012-2021. Commercial. All rights reserved, may not be used without a valid license."
    url = "<!-- <Package recipe repository url here, for issues about the package> -->"
    description = "Game engine"
    settings = "os", "compiler", "build_type", "arch"
    # "assimp/5.0.1" removed for now for shorter ci runtime
    requires = "libpng/1.6.37","glew/2.1.0","luajit/2.0.5", "catch2/2.11.1"
    options = {"shared": [True, False]}
    default_options = {"shared": False}

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
