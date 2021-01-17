from conans import ConanFile, CMake, tools

class TEngine(ConanFile):
    name = "tengine"
    version = "0.1"
    license = "<Put the package license here>"
    url = "<!-- <Package recipe repository url here, for issues about the package> -->"
    description = "Game engine"
    settings = "os", "compiler", "build_type", "arch"
    requires = "assimp/5.0.1","enet/1.3.17","libpng/1.6.37","glew/2.1.0","luajit/2.0.5"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"

    def configure(self):
        print("---CONFIGURE---")

    def build(self):
        print("---BUILD---")
        if self.settings.os == "Windows":
            cmake = CMake(self, append_vcvars=True)
        else:
            cmake = CMake(self)
        cmake.configure()
        cmake.build()


