#pragma once
#include <memory>
#include <string>
#include <vector>

#include "mirrorapi.h"

typedef long jlong;

class API
{
public:
    static jlong openDB(const char *db_path);
    static jlong newIterator(jlong japi_db_handle);
    static void closeIterator(jlong japi_db_handle);
};
