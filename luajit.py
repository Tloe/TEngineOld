from conans import ConanFile, tools

class LuajitConan(ConanFile):
    name = "luajit"
    version = "2.0.5"
    license = "MIT"
    author = "Andrew Tomazos <andrewtomazos@gmail.com>"
    url = "https://luajit.org"
    topics = ("lua",)
    description = "a Just-In-Time Compiler for Lua"
    settings = "os", "compiler", "build_type", "arch"

    def source(self):
        tools.get("https://luajit.org/download/LuaJIT-2.0.5.tar.gz")

    def build(self):
        if self.settings.os == "Windows":
            with tools.chdir("LuaJIT-2.0.5/src"):
                self.run("msvcbuild static")
        else:
            with tools.chdir("LuaJIT-2.0.5"):
                self.run('make')

    def package(self):
        ljs = "LuaJIT-2.0.5/src"
        if self.settings.os == "Windows":
            self.copy("luajit.exe", dst="bin", src=ljs)
            self.copy("lua51.lib", dst="lib", src=ljs)
        else:
            self.copy("luajit", dst="bin", src=ljs)
            self.copy("libluajit.a", dst="lib", src=ljs)
        self.copy("lua.h", dst="include", src=ljs)
        self.copy("lualib.h", dst="include", src=ljs)
        self.copy("lauxlib.h", dst="include", src=ljs)
        self.copy("luaconf.h", dst="include", src=ljs)
        self.copy("lua.hpp", dst="include", src=ljs)
        self.copy("luajit.h", dst="include", src=ljs)

    def package_info(self):
        if self.settings.os == "Windows":
            self.cpp_info.libs = ["lua51"]
        else:
            self.cpp_info.libs = ["luajit"]
