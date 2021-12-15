// our JNI open db method
#include "jnim2mock.h"
APIDB *API::openDB(const char *db_path)
{
    auto *db = new DB(/*db_path*/); // call C++ API to openDB
    auto *api_db = new APIDB();
    api_db->db = std::shared_ptr<DB>(db);
    return api_db;
}

// our JNI create iterator method
APIIterator *API::newIterator(jlong japi_db_handle)
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
void API::closeIterator(jlong japi_db_handle)
{
    auto *japi_db = reinterpret_cast<APIDB *>(japi_db_handle);
    delete japi_db;
}
