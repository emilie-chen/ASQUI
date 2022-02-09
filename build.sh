#!/bin/bash
if [[ -d build-osx ]]
then
    rm -rf build-osx
fi

./build-inc.sh

#cmake -DCMAKE_TOOLCHAIN_FILE="./vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=arm64-osx -B build-osx -S . -GXcode
