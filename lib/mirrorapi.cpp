
#include "mirrorapi.h"

APIColumnFamilyHandle *APIDB::openColumnFamily(const char *name)
{
    for (std::shared_ptr<ColumnFamilyHandle> cfh : cfhs)
    {
        if (cfh->name.compare(name) == 0)
        {
            return new APIColumnFamilyHandle(db, cfh);
        }
    }
    auto cfh = std::shared_ptr<ColumnFamilyHandle>(new ColumnFamilyHandle(name));
    cfhs.push_back(cfh);
    return new APIColumnFamilyHandle(db, cfh);
};

APIIterator *APIDB::newIterator()
{
    // call C++ API to create iterator
    return new APIIterator(db, db->newIterator());
};