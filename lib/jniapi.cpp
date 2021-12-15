// our JNI open db method
#include "jniapi.h"

jlong API::openDB(const char *db_path)
{
    // call C++ API to openDB
    auto *japi_db = APIDB::openDB(db_path);

    return reinterpret_cast<jlong>(japi_db);
}

// our JNI create iterator method
jlong API::newIterator(jlong japi_db_handle)
{
    auto *japi_db = reinterpret_cast<APIDB *>(japi_db_handle);

    // call C++ API to create iterator
    return reinterpret_cast<jlong>(japi_db->newIterator());
}

// our JNI method for close iterator
void API::closeIterator(jlong japi_db_handle)
{
    auto *japi_db = reinterpret_cast<APIDB *>(japi_db_handle);

    // call C++ API to delete the iterator
    delete japi_db;
}
