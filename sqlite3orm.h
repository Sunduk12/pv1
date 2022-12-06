#include <sqlite3.h>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>
#include "sqlite3orm-models.h"

using namespace std;

class sqlite3ormStorage
{
private:
    sqlite3ormStorage();
    ~sqlite3ormStorage();
    static sqlite3ormStorage *p_instance;

public:
    user *user1;
    static sqlite3ormStorage *getInstance()
    {
        if (!p_instance)
            p_instance = new sqlite3ormStorage();
        return p_instance;
    }
};

sqlite3ormStorage *sqlite3ormStorage::p_instance = 0;

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
        vector<map<char *, char *>> rows;
        vector<map<char *, char *>> *rowsPointer;

        int rc = sqlite3_exec(this->db, sql, callback_map, &rows, &zErrMsg);

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

        rowsPointer = &rows;

        for (int f = 0; f < rowsPointer->size(); f++)
        {
            map<char *, char *> row = rowsPointer->at(f);
            map<char *, char *>::iterator it = row.begin();

            for (int i = 0; it != row.end(); it++, i++)
            {
                fprintf(stdout, "key:%s value:%s\n", it->first, it->second);
            }
        }
    }

    static int callback_map(void *data, int argc, char **argv, char **azColName)
    {
        vector<map<char *, char *>> *rows = (vector<map<char *, char *>> *)data;
        map<char *, char *> row;
        for (int i = 0; i < argc; i++)
        {
            row[azColName[i]] = argv[i];
        }
        rows->push_back(row);
        return 0;
    }
};

sqlite3orm *sqlite3orm::p_instance = 0;