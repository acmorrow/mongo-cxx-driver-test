cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project (mongo-cxx-driver-test)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib/cmake")

include (InstallRequiredSystemLibraries)

enable_testing()
add_subdirectory (src)
