#include <sqlite3.h>
#include <exception>
#include <stdexcept>

class sqlite3orm
{
private:
    sqlite3 *db;
    const char *dbPath;
    sqlite3orm(const char *dbPath)
    {
        this->dbPath = dbPath;
        int rc = sqlite3_open(this->dbPath, &this->db);
        if (rc)
        {
            throw std::runtime_error("Can't open database");
        }
    }

    ~sqlite3orm()
    {
        sqlite3_close(this->db);
    }

    static sqlite3orm *p_instance;

public:
    static sqlite3orm *getInstance()
    {
        if (!p_instance)
            p_instance = new sqlite3orm("test.db");
        return p_instance;
    }

    sqlite3 *getDb()
    {
        return this->db;
    }

    void exec(
        const char *sql,                                /* SQL to be evaluated */
        int (*callback)(void *, int, char **, char **), /* Callback function */
        void *data                                      /* 1st argument to callback */
    )
    {
        char *zErrMsg = 0;
        int rc = sqlite3_exec(this->db, sql, callback, (void *)data, &zErrMsg);
        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            throw std::runtime_error("SQL error");
        }
        else
        {
            fprintf(stdout, "Operation done successfully\n");
        }
    }
};

class sqlite3ormModel
{
private:
    /* data */
public:
    sqlite3ormModel(/* args */);
    ~sqlite3ormModel();
};

sqlite3ormModel ::sqlite3ormModel(/* args */)
{
}

sqlite3ormModel ::~sqlite3ormModel()
{
}
