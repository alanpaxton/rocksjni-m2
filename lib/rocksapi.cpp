
#include "rocksapi.h"

Iterator *DB::newIterator()
{
    return new Iterator(); // stub
};
