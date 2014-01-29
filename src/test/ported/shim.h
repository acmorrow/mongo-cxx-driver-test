#ifndef included_587DD57A_CD2F_4580_81C6_EC13D0764C6
#define included_587DD57A_CD2F_4580_81C6_EC13D0764C6

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>

#define ASSERT ASSERT_TRUE
#define ASSERT_EQUALS ASSERT_EQ
#define ASSERT_NOT_EQUALS ASSERT_NE
#define ASSERT_LESS_THAN_OR_EQUALS ASSERT_LE
#define ASSERT_APPROX_EQUAL ASSERT_NEAR
#define ASSERT_OK(EXPRESSION) ASSERT_EQUALS(::mongo::Status::OK(), (EXPRESSION))
#define ASSERT_NOT_OK(EXPRESSION) ASSERT_NOT_EQUALS(::mongo::Status::OK(), (EXPRESSION))
#define ASSERT_THROWS(STATEMENT, EXCEPTION) ASSERT_THROW(STATEMENT, EXCEPTION)

using namespace mongo;
using boost::shared_ptr;

// from src/mongo/util/mongoutils/checksum.h
inline int checksum( const char* x , int size ) {
    int ck = 0;
    for ( int i=0; i<size; i++ )
        ck += ( (int)x[i] * ( i + 1 ) );
    return ck;
}

#endif
