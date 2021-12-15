#include <iostream>
#include <memory>
#include <gtest/gtest.h>

#include "lib/jnim2mock.h"

// TODO - will this work for those objects that Rocks C++ API gives us pointers to (but that we don't own!)
// -- see Java -> org.rocksdb.AbstractImmutableNativeReference#disOwnNativeHandle
/*
class APIIterator_Owned {
  public:
    std::shared_ptr<DB> db;
    std::unique_ptr<Iterator> it;
};

class APIIterator_NonOwned {
  public:
    Iterator *it;
};
*/

// TODO - how to close the DB if we have outstanding references to it
// - perhaps a force flag? throw an exception if false, if true force shutdown
// -

TEST(jnim2mock, useCount)
{

  auto *japi_db = API::openDB("/tmp/test-db1");
  jlong japi_db_handle = reinterpret_cast<jlong>(japi_db);

  GTEST_ASSERT_EQ(japi_db->db.use_count(), 1);

  auto *japi_it1 = API::newIterator(japi_db_handle);
  GTEST_ASSERT_EQ(japi_db->db.use_count(), 2);

  auto *japi_it2 = API::newIterator(japi_db_handle);
  GTEST_ASSERT_EQ(japi_db->db.use_count(), 3);
  GTEST_ASSERT_EQ(japi_it1->db.use_count(), 3);
  GTEST_ASSERT_EQ(japi_it2->db.use_count(), 3);

  // now cleanup
  delete japi_it1;
  GTEST_ASSERT_EQ(japi_db->db.use_count(), 2);
  GTEST_ASSERT_EQ(japi_it1->db.use_count(), 2);
  GTEST_ASSERT_EQ(japi_it2->db.use_count(), 2);

  delete japi_it2;
  GTEST_ASSERT_EQ(japi_db->db.use_count(), 1);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
