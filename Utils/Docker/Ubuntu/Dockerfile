FROM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y apt-transport-https ca-certificates gnupg python3-pip libgl-dev pkg-config libglu1-mesa-dev libxxf86vm-dev lsb-release wget software-properties-common && \
    bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)" 13 && \
    apt-get install -y libc++-11-dev libc++abi-11-dev  && \
    ln -s /usr/bin/clang-13 /usr/bin/clang && \
    ln -s /usr/bin/clang++-13 /usr/bin/clang++ && \
    bash -c "wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null" && \
    apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main' && \
    apt-get update && \
    apt-get install -y cmake && \
    pip3 install conan && \
    conan 'config install Utils/Conan/settings.yml'
    # git clone https://github.com/llvm/llvm-project.git && \
    # cd llvm-project && \
    # cmake -S llvm -B build -G Ninja -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" -DLLVM_USE_LINKER=gold -DCMAKE_BUILD_TYPE=Release && \
    # cmake --build build ninja -j 5 && \
    # cmake --build build --target install && \



