cmake_minimum_required( VERSION 3.8 )
set(CMAKE_SYSTEM_NAME Linux )

SET(CLANG_VERSION "8")

SET (CMAKE_C_COMPILER             "/usr/bin/clang-${CLANG_VERSION}")
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")
 
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++-${CLANG_VERSION}")
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
 
SET (CMAKE_AR      "/usr/bin/llvm-ar-${CLANG_VERSION}")
SET (CMAKE_LINKER  "/usr/bin/llvm-ld-${CLANG_VERSION}")
SET (CMAKE_NM      "/usr/bin/llvm-nm-${CLANG_VERSION}")
SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump-${CLANG_VERSION}")
SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib-${CLANG_VERSION}")
