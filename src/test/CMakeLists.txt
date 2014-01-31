include (ExternalProject)

# Get and build gtest

set_directory_properties (PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/src/third_party)
ExternalProject_Add (
  googletest
  URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON

  CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
  -Dgtest_force_shared_crt=ON
)

# Add googletest include dir
ExternalProject_Get_Property (googletest source_dir)
include_directories (${source_dir}/include)

# Add googletest library dir
ExternalProject_Get_Property (googletest binary_dir)
link_directories (${binary_dir})

# Get and build mongo-cxx-driver

# Basic build options for building the driver.
# TODO: Make concurrency of build match cmake (how?)
set (MONGOCLIENT_SCONS_FLAGS
  ${MONGOCLIENT_SCONS_FLAGS}
  --warn=no-missing-sconscript
  --cache
  --full
  --use-system-boost
  --allocator=system
  --cpppath=${Boost_INCLUDE_DIRS}
  --libpath=${Boost_LIBRARY_DIRS}
  --ssl
  --use-sasl-client
)

# On Mavericks, presume that boost is linked to libc++
if (APPLE)
  if(NOT ${CMAKE_SYSTEM_VERSION} VERSION_LESS "13")
    list (APPEND MONGOCLIENT_SCONS_FLAGS --osx-version-min=10.8 --libc++)
  endif ()
endif ()

# If we are doing a debug build, then build mongoclient the same way
if (CMAKE_BUILD_TYPE MATCHES Debug)
    list (APPEND MONGOCLIENT_SCONS_FLAGS --dbg=on)
endif ()

if (BUILD_SHARED_LIBS)
  list (APPEND MONGOCLIENT_SCONS_FLAGS --sharedclient)
endif ()

ExternalProject_Add(
  mongo-cxx-driver
  GIT_REPOSITORY https://github.com/TylerBrock/mongo-cpp-driver.git
  GIT_TAG legacy
  LOG_DOWNLOAD ON
  LOG_INSTALL ON
  CONFIGURE_COMMAND ""
  BUILD_IN_SOURCE 1
  BUILD_COMMAND ""
  INSTALL_COMMAND scons --prefix=<INSTALL_DIR> ${MONGOCLIENT_SCONS_FLAGS} install-mongoclient
)

# NOTE: The following should not be necessary if libmongoclient had a properly constructed
# config.h header, see CXX-23.
add_definitions (-DMONGO_SSL)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG)
endif ()

# Add mongo-cxx-driver installed headers and libs
ExternalProject_Get_Property (mongo-cxx-driver install_dir)
include_directories (${install_dir}/include)
include_directories (${PROJECT_SOURCE_DIR}/src/test)
link_directories (${install_dir}/lib)

add_library(clienttest_main clienttest_main.cpp)
target_link_libraries(clienttest_main mongoclient gtest)

macro (create_test suite_name test_name)
  add_executable (${test_name} ${test_name}.cpp)
  add_dependencies (${test_name} mongo-cxx-driver googletest)
  target_link_libraries (${test_name} mongoclient ${Boost_LIBRARIES} gtest clienttest_main)
  add_test (${suite_name}.${test_name} ${test_name})
endmacro ()

macro (create_tests suite_name)
  foreach (test_name ${ARGN})
    create_test (${suite_name} ${test_name})
  endforeach ()
endmacro ()

create_tests (bson
  test_oid
)

macro (create_ported_test test_path test_name)
  add_executable (${test_name} ${test_path}/${test_name}.cpp)
  add_dependencies (${test_name} mongo-cxx-driver googletest)
  target_link_libraries(${test_name} mongoclient ${Boost_LIBRARIES} gtest clienttest_main)
  add_test (ported.${test_name} ${test_name})
endmacro ()

create_ported_test (ported/src/mongo/bson bson_field_test)
create_ported_test (ported/src/mongo/bson bson_obj_test)
create_ported_test (ported/src/mongo/bson bson_validate_test)
create_ported_test (ported/src/mongo/bson bsonobjbuilder_test)

create_ported_test (ported/src/mongo/client replica_set_monitor_test)

#create_ported_test (ported/src/mongo/dbtests jsobjtests)
#create_ported_test (ported/src/mongo/dbtests jsontests)

create_ported_test (ported/src/mongo/util/net sock_test)
