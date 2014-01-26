#include <iostream>

#include <gtest/gtest.h>

#include <mongo/bson/bson.h>
#include <mongo/client/dbclient.h>

namespace {

    // Check that we can reproduce the example from bsonspec.org
    TEST(OID, gen) {
        const mongo::OID anOid = mongo::OID::gen();
    }

} // namespace
