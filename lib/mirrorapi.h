#pragma once
#include <memory>
#include <string>
#include <vector>

#include "rocksapi.h"

class APIDB;
class APIColumnFamilyHandle;
class APIIterator;
class APIDB
{
    std::shared_ptr<DB> db;
    std::vector<std::shared_ptr<ColumnFamilyHandle>> cfhs;

    APIDB(const char *db_path) : db(std::shared_ptr<DB>(new DB(db_path))){};

public:
    static APIDB *openDB(const char *db_path) { return new APIDB(db_path); };

    APIIterator *newIterator();
    APIColumnFamilyHandle *openColumnFamily(const char *name);
};

class APIIterator
{
    friend class APIDB;

    std::shared_ptr<DB> db;
    std::unique_ptr<Iterator> it;

    APIIterator(std::shared_ptr<DB> db, Iterator *iterator) : db(db), it(std::unique_ptr<Iterator>(iterator)){};
};

class APIColumnFamilyHandle
{
    friend class APIDB;

    std::shared_ptr<DB> db;
    std::shared_ptr<ColumnFamilyHandle> cfh;

    APIColumnFamilyHandle(std::shared_ptr<DB> db, std::shared_ptr<ColumnFamilyHandle> cfh) : db(db), cfh(cfh){};
};
