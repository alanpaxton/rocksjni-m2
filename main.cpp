#include <iostream>
#include <memory>

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

class Iterator
{
};

class DB
{
public:
  Iterator *newIterator()
  {
    return new Iterator(); // stub
  }
};

class APIDB
{
public:
  std::shared_ptr<DB> db;
};

class APIIterator
{
public:
  std::shared_ptr<DB> db;
  std::unique_ptr<Iterator> it;
};

typedef long jlong;

// our JNI open db method
APIDB *openDB(const char *db_path)
{
  auto *db = new DB(/*db_path*/); // call C++ API to openDB
  auto *api_db = new APIDB();
  api_db->db = std::shared_ptr<DB>(db);
  return api_db;
}

// our JNI create iterator method
APIIterator *newIterator(jlong japi_db_handle)
{
  auto *japi_db = reinterpret_cast<APIDB *>(japi_db_handle);

  // call C++ API to create iterator
  auto *iterator = japi_db->db->newIterator();

  auto *api_iterator = new APIIterator();
  api_iterator->db = japi_db->db;
  api_iterator->it = std::unique_ptr<Iterator>(iterator);
  return api_iterator;
}

// our JNI method for close iterator
void closeIterator(jlong japi_db_handle)
{
  auto *japi_db = reinterpret_cast<APIDB *>(japi_db_handle);
  delete japi_db;
}

void testUseCount()
{

  auto *japi_db = openDB("/tmp/test-db1");
  jlong japi_db_handle = reinterpret_cast<jlong>(japi_db);

  std::cout << "1) japi_db->db.use_count: " << japi_db->db.use_count() << std::endl;
  std::cout << std::endl;

  auto *japi_it1 = newIterator(japi_db_handle);

  std::cout << "2) japi_db->db.use_count: " << japi_db->db.use_count() << std::endl;
  std::cout << "2) japi_it1->db.use_count: " << japi_it1->db.use_count() << std::endl;
  std::cout << std::endl;

  auto *japi_it2 = newIterator(japi_db_handle);

  std::cout << "3) japi_db->db.use_count: " << japi_db->db.use_count() << std::endl;
  std::cout << "3) japi_it1->db.use_count: " << japi_it1->db.use_count() << std::endl;
  std::cout << "3) japi_it2->db.use_count: " << japi_it2->db.use_count() << std::endl;
  std::cout << std::endl;

  // now cleanup
  delete japi_it1;

  std::cout << "4) japi_db->db.use_count: " << japi_db->db.use_count() << std::endl;
  std::cout << "4) japi_it2->db.use_count: " << japi_it2->db.use_count() << std::endl;

  delete japi_it2;

  std::cout << "5) japi_db->db.use_count: " << japi_db->db.use_count() << std::endl;

  std::cout << std::endl;
  std::cout << "DONE" << std::endl;
}

int main(int argc, char *argv[]) {

    std::cout << "Hello, world!\n";
    testUseCount();

    return 0;
}
