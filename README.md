# TEngine

Hobby game engine by Terje Loe

This project has been worked on in a private repo alone by me and been made public recently.
Currently working on cleaning things up.

## Getting started

Dependencies are handled with conan so it needs to be installed. To configure and build dependencies:

'''
mkdir build
cd build
export CC=clang
export CXX=clang
conan install .. -s compiler=clang -s compiler.version=10.0.1 -s compiler.libcxx=libstdc++ --build=missing
cmake ..
make
'''

Theres a bug with building GLEW on FreeBSD so the conan glew install will fail theres a temporary
fix in the first post of this issue: https://github.com/nigels-com/glew/issues/210.
Edit the CMakeLists.txt file in:
~/.conan/data/glew/2.1.0/bincrafters/stable/source/_source_subfolder/build/cmake/

In addition to the dependencies handled by conan there is also a dependency on OpenGL which nix systems
should have installed and it comes with VS.

Then run cmake in the same directory

'''
cmake ..
'''
