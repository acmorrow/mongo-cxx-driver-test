add_definitions(-DMONGO_EXPOSE_MACROS)

add_library(mocklib
  mock_conn_registry.cpp
  mock_dbclient_connection.cpp
  mock_dbclient_cursor.cpp
  mock_remote_db_server.cpp
  mock_replica_set.cpp
)
target_link_libraries(mocklib mongoclient ${Boost_LIBRARIES})
add_dependencies(mocklib mongo-cxx-driver)
