set (BUILD_SHARED_LIBS ON)

# We need to know where boost is, both to inform the build of mongo-cxx-driver, and
# so we can use it in our tests, so find it, and add it to our include and lib paths.

find_package (Boost
  REQUIRED
  COMPONENTS filesystem program_options system thread
)

include_directories (${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})

add_subdirectory (test)
