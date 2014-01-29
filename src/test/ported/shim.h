#ifndef included_587DD57A_CD2F_4580_81C6_EC13D0764C6
#define included_587DD57A_CD2F_4580_81C6_EC13D0764C6

/*
 * Shim to allow mongoclient tests to build with gtest instead of
 * built in MongoDB unittest framework.
 *
 * Note: FAIL(str) has been converted to FAIL() << str; in tests.
 *
 */

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>
#include <mongo/util/mongoutils/str.h>

#define ASSERT ASSERT_TRUE
#define ASSERT_EQUALS ASSERT_EQ
#define ASSERT_NOT_EQUALS ASSERT_NE
#define ASSERT_LESS_THAN_OR_EQUALS ASSERT_LE
#define ASSERT_APPROX_EQUAL ASSERT_NEAR
#define ASSERT_OK(EXPRESSION) ASSERT_EQUALS(::mongo::Status::OK(), (EXPRESSION))
#define ASSERT_NOT_OK(EXPRESSION) ASSERT_NOT_EQUALS(::mongo::Status::OK(), (EXPRESSION))
#define ASSERT_THROWS(STATEMENT, EXCEPTION) ASSERT_THROW(STATEMENT, EXCEPTION)

using namespace mongo;
using namespace mongoutils;
using boost::shared_ptr;

#endif
