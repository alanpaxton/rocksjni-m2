#include <iostream>
#include <memory>
#include <gtest/gtest.h>

#include "lib/jniapi.h"

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

TEST(jniapi, useCount)
{

  auto japi_db_handle = API::openDB("/tmp/test-db1");
  auto *japi_db = reinterpret_cast<APIDB *>(japi_db_handle);

  GTEST_ASSERT_EQ(japi_db->db_use_count(), 1);

  auto japi_it1_handle = API::newIterator(japi_db_handle);
  auto *japi_it1 = reinterpret_cast<APIIterator *>(japi_it1_handle);
  GTEST_ASSERT_EQ(japi_db->db_use_count(), 2);

  auto japi_it2_handle = API::newIterator(japi_db_handle);
  auto *japi_it2 = reinterpret_cast<APIIterator *>(japi_it2_handle);
  GTEST_ASSERT_EQ(japi_db->db_use_count(), 3);
  GTEST_ASSERT_EQ(japi_it1->db_use_count(), 3);
  GTEST_ASSERT_EQ(japi_it2->db_use_count(), 3);

  // now cleanup
  delete japi_it1;
  GTEST_ASSERT_EQ(japi_db->db_use_count(), 2);
  GTEST_ASSERT_EQ(japi_it1->db_use_count(), 2);
  GTEST_ASSERT_EQ(japi_it2->db_use_count(), 2);

  delete japi_it2;
  GTEST_ASSERT_EQ(japi_db->db_use_count(), 1);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
