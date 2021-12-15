#include <string>

class DB;
class ColumnFamilyHandle;
class Iterator;

class DB
{
    std::string path;

public:
    Iterator *newIterator();
    DB(const char *path) : path(path){};
};

class ColumnFamilyHandle
{
public:
    std::string name;

    ColumnFamilyHandle(std::string name) : name(name){};
};

class Iterator
{
};
