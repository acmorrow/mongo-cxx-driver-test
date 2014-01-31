set (BUILD_SHARED_LIBS ON)

# We need to know where boost is, both to inform the build of mongo-cxx-driver, and
# so we can use it in our tests, so find it, and add it to our include and lib paths.

find_package (Boost
  REQUIRED
  COMPONENTS filesystem program_options system thread
)

include_directories (${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})

option(SANITIZE "SANITIZE" OFF)
if(SANITIZE)
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    list(APPEND CMAKE_C_FLAGS "-fsanitize=address")
    list(APPEND CMAKE_C_LINK_FLAGS "-fsanitize=address")
    list(APPEND CMAKE_CXX_LINK_FLAGS "-fsanitize=address")
  else()
    message(WARNING "Option SANITIZE specified but compiler is not clang (${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ID}).")
  endif()
 endif()

add_subdirectory (test)
