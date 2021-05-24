# TEngine

Game Engine in a funny state ;)

## Building

For linux clang-13 is used for the CI, but other versions should build it aswell.

cmake, python and conan is needed for building. Conan can be installed with pip for python.

    mkdir build
    cd build
    conan export ../Utils/Conan/Luajit/luajit.py
    conan install .. --profile ../Utils/Conan/Profiles/Linux/TEngineRelease -g cmake --build=missing
    conan build ..


