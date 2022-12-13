#include <sqlite3.h>
#include <stdio.h>
#include "sqlite3orm.h"
#include <string>
#include <vector>
#include <iostream>
#include <exception>

using namespace std;

class querySQL
{
public:
    // querySQL *update(string tableName, string colseEqualsValue, string whereCondition = "")
    // {
        
    //     return this;
    // }

    querySQL *insert(string tableName, string columnName, string fieldName)
    {
        this->resInsert = "insert into " + tableName + " ( " + columnName + " ) " + " values " + " ( " + fieldName + " )";

        return this;
    }

    querySQL *orWhere(string fieldName, string value, string fieldIF)
    {
        this->resWhereOr = " or " + fieldName + " " + value + " '" + fieldIF + +"'";

        return this;
    }

    querySQL *andWhere(string fieldName, string value, string fieldIF)
    {
        this->resWhereAnd = " and " + fieldName + " " + value + " '" + fieldIF + +"'";

        return this;
    }

    querySQL *where(string fieldName, string value, string fieldIF)
    {
        int e = 1;

        for (int i = 0; i < 7; i++)
        {
            if (value == conditionWhere[i])
            {
                e = 0;
                break;
            }
        }

        if (e)
            throw std::runtime_error("no such condition exists! enter one of the following: =, !=, <>, >, <, <=, >=");

        this->resWhere = "where " + fieldName + " " + value + " '" + fieldIF + +"'";
        return this;
    }

    querySQL *selectTable(string tableName)
    {

        this->tableName = tableName;
        this->queryType = "select";

        return this;
    }

    string selectSQL()
    {
        string fields;

        if (vfields.size() == 0)
        {
            fields = "*";
        }
        else
        {
            for (int i = 0; i < this->vfields.size(); i++)
            {
                fields += this->vfields[i] + "," + " ";
            }
            fields.pop_back();
            fields.pop_back();
        }

        resSelectTable = this->queryType + " " + fields + " from " + tableName + "\n";

        
        string result = resSelectTable + resAddFields + resWhere + resWhereAnd + resWhereOr + resInsert;
        return result;
    }

    querySQL *select(string tableName)
    {
        this->tableName = tableName;
        this->queryType = "select";

        return this;
    }

    querySQL *addFields(string vfields)
    {
        this->vfields.push_back(vfields);

        return this;
    }

private:
    vector<string> vfields;
    string tableName;
    string queryType;

    string fieldIF;
    string meaning;
    string fieldName;
    string resWhere;
    string conditionWhere[7] = {"=", "!=", "<>", ">", "<", "<=", ">="};

    string resWhereOr;
    string resWhereAnd;
    string resInsert;
    string resSelectTable;
    string resAddFields;


};

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: \n", (const char *)data);
    // data.id = i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}