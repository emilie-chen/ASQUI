#!/bin/bash
arch -x86_64 cmake -DCMAKE_TOOLCHAIN_FILE="./vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-osx -B build-osx -S . -GXcode
