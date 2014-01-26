include(ExternalProject)

# Get and build gtest

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/src/third_party)
ExternalProject_Add(
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
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

# Add googletest library dir
ExternalProject_Get_Property(googletest binary_dir)
link_directories(${binary_dir})

# Get and build mongo-cxx-driver

# TODO: Make dbg state match CMake.
# TODO: Make shared library build match CMake
# TODO: Make concurrency of build match cmake
# TODO: Only do --libc++ when building on OS X when libc++ is the system default
set(MONGOCLIENT_BUILD_OPTS
  --full
  --sharedclient
  --use-system-boost
  --allocator=system
  --ssl
  --use-sasl-client
  --dbg=on
  --cpppath=${Boost_INCLUDE_DIRS}
  --libpath=${Boost_LIBRARY_DIRS}
  --osx-version-min=10.7
  --libc++
)

ExternalProject_Add(
  mongo-cxx-driver
  GIT_REPOSITORY https://github.com/TylerBrock/mongo-cpp-driver.git
  GIT_TAG legacy
  LOG_DOWNLOAD ON
  LOG_BUILD ON
  CONFIGURE_COMMAND ""
  BUILD_IN_SOURCE 1
  BUILD_COMMAND scons ${MONGOCLIENT_BUILD_OPTS} mongoclient
  INSTALL_COMMAND scons --prefix=<INSTALL_DIR> ${MONGOCLIENT_BUILD_OPTS} check-install-mongoclient
)

# Add mongo-cxx-driver installed headers and libs
ExternalProject_Get_Property(mongo-cxx-driver install_dir)
include_directories(${install_dir}/include)
link_directories(${install_dir}/lib)

macro (create_test suite_name test_name)
  add_executable (${test_name} ${test_name}.cpp)
  add_dependencies (${test_name} mongo-cxx-driver googletest)
  target_link_libraries (${test_name} mongoclient ${Boost_LIBRARIES} gtest gtest_main)
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
