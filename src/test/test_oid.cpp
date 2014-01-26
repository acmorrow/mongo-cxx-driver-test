#include <gtest/gtest.h>
#include <mongo/bson/bson.h>

namespace {

    TEST(OID, gen) {
        const mongo::OID oid1 = mongo::OID::gen();
        const mongo::OID oid2 = mongo::OID::gen();
        EXPECT_NE(oid1, oid2);
    }

} // namespace
