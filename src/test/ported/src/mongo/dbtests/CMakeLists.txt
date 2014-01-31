add_subdirectory(mock)

create_tests (dbtests
  jsobjtests
  jsontests
  mock_dbclient_conn_test
  mock_replica_set_test
  replica_set_monitor_test
)
