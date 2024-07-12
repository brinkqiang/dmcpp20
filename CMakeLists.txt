cmake_minimum_required(VERSION 3.8)

PROJECT(dmcpp20)

cmake_policy(SET CMP0026 OLD)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
INCLUDE(cmake/UseBackportedModules.cmake)
ModuleSetCompileOptions()

IF(MSVC)
    include(CreateLaunchers)
ENDIF()

ModuleImport("dmlog" "thirdparty/dmlog")
ModuleImport("dmtest" "thirdparty/dmtest")
LibImport("dmcpp20" "src")


IF(WIN32)
    ExeImport("test" "dmcpp20;dmtest")

    IF(MSVC)
        create_target_launcher(dmstringtest WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
    ENDIF()
ELSE()
    find_library(LIB_STD_FS stdc++fs)
    IF(LIB_STD_FS_FOUND)
        ExeImport("test" "dmcpp20;dmtest;${LIB_STD_FS_LIBRARIES}")
    ELSE(LIB_STD_FS_FOUND)
        ExeImport("test" "dmcpp20;dmtest;stdc++fs")
    ENDIF(LIB_STD_FS_FOUND)
ENDIF()
