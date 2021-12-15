#pragma once
#include <memory>

typedef long jlong;

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

class API
{
public:
    static APIDB *openDB(const char *db_path);
    static APIIterator *newIterator(jlong japi_db_handle);
    static void closeIterator(jlong japi_db_handle);
};
