#include <sqlite3.h>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>
#include "sqlite3orm-models.h"

using namespace std;

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

    vector<map<string, string>> exec(
        const char *sql /* SQL запрос */
    )
    {
        char *zErrMsg = 0;
        vector<map<string, string>> rows;

        int rc = sqlite3_exec(this->db, sql, callback, &rows, &zErrMsg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            throw std::runtime_error("SQL error");
        }

        return rows;
    }

    static int callback(void *data, int argc, char **argv, char **azColName)
    {
        vector<map<string, string>> *rows = (vector<map<string, string>> *)data;
        map<string, string> row;
        for (int i = 0; i < argc; i++)
        {
            row[azColName[i]] = argv[i];
        }
        rows->push_back(row);
        return 0;
    }

    void printResult(vector<map<string, string>> rows)
    {
        for (int f = 0; f < rows.size(); f++)
        {
            map<string, string> row = rows.at(f);
            map<string, string>::iterator it = row.begin();
            cout << "--------- row #" << f + 1 << endl;
            for (int i = 0; it != row.end(); it++, i++)
            {
                cout << it->first << " : " << it->second << endl;
            }
        }
    }

    void execAndPrint(
        const char *sql /* SQL запрос */
    )
    {
        this->printResult(this->exec(sql));
    }
};

sqlite3orm *sqlite3orm::p_instance = 0;