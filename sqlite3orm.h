#include <sqlite3.h>
#include <exception>
#include <stdexcept>

class sqlite3orm
{
private:
    sqlite3 *db;
    const char *dbPath;

public:
    sqlite3orm(const char *dbPath);
    ~sqlite3orm();

    sqlite3 *getDb()
    {
        return this->db;
    }
};

sqlite3orm::sqlite3orm(const char *dbPath)
{
    this->dbPath = dbPath;
    int rc = sqlite3_open(this->dbPath, &this->db);
    if (rc)
    {
        throw std::runtime_error("Can't open database: %s\n");
    }
}

sqlite3orm::~sqlite3orm()
{
    sqlite3_close(this->db);
}


class sqlite3ormModel
{
private:
    
public:
    sqlite3ormModel();
    ~sqlite3ormModel();
};

sqlite3ormModel::sqlite3ormModel()
{
}

sqlite3ormModel::~sqlite3ormModel()
{
}
