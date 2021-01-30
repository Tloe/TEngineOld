from conans import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
#from conan.tools.microsoft import visual
from conans.tools import os_info, vcvars
import os, shutil

class TEngine(ConanFile):
    name = "tengine"
    version = "0.1"
    license = "Copyright (c) Terje Loe 2012-2021. Commercial. All rights reserved, may not be used without a valid license."
    url = "<!-- <Package recipe repository url here, for issues about the package> -->"
    description = "Game engine"
    settings = "os", "compiler", "build_type", "arch"
    requires = "assimp/5.0.1","enet/1.3.17","libpng/1.6.37","glew/2.1.0","luajit/2.0.5"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
       
    def _config_cmake(self):
        if os_info.is_windows:
            cmake = CMake(self)
            with vcvars(self):
                cmake.configure()
        else:
            cmake = CMake(self)
            cmake.configure()
        return cmake

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate

    def build(self):
        cmake = self._config_cmake()
        if os_info.is_windows:
            with vcvars(self):
                cmake.build()
        else:
            cmake.build()