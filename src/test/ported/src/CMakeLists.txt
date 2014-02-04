# Ported mongo tests and mocklib expect to be built with the macros exposed
add_definitions(-DMONGO_EXPOSE_MACROS)

add_subdirectory(mongo)
