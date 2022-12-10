#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <vector>
#include <exception>


using namespace std;

class Sql3_scheme {
public:

    string create(bool ifNotExists = false)
    {

        string sql = "CREATE TABLE ";
        if (ifNotExists)
            sql = sql + "IF NOT EXISTS ";

        sql = sql + this->tableName;
        sql = sql + '(' + '\n';
        for (int i = 0;i < this->fields.size();i++)
        {
            for (int j = 0; j < this->fields[i].size();j++)
            {
                sql = sql + this->fields[i][j] + "    ";
            }
            if (this->fields.size() - 1 == i)
                sql = sql + '\n';
            else
                sql = sql + ',' + '\n';
        }
        sql = sql + ");";
        return sql;
    }
    string drop()
    {
        string sql = "DROP TABLE " + this->tableName;
        return sql;
    }
    string rename(string newTableName)
    {
        string sql = "ALTER TABLE " + this->tableName + " RENAME TO " + newTableName;
        return sql;
    }
    string dropColumn(string columnName)
    {
        string sql = "ALTER TABLE " + this->tableName + " DROP COLUMN " + columnName;
        return sql;
    }
    string addColumn(string columnName,string columnType)
    {
        int e = 1;


        for (int i = 0;i < 5;i++)
        {
            if (columnType == typeField[i])
            {
                string sql = "ALTER TABLE " + this->tableName + " ADD COLUMN " + columnName + ' ' + columnType;
                e = 0;
                return sql;
                break;
            }
        }
        if (e)
            throw exception("Wrong field type! Please use types: INTEGER, BLOB, REAL, NUMERIC, TEXT");
   
    }
    string renameColumn(string columnName, string newColumnName)
    {
        string sql = "ALTER TABLE " + this->tableName + " RENAME COLUMN " + columnName +" TO " + newColumnName;
        return sql;
    }
    Sql3_scheme* table(string tableName)
    {
        this->tableName = tableName;
        return this;
    }
    Sql3_scheme* addField(string fieldName, string fieldType)
    {
        int e = 1;


        for (int i = 0;i < 5;i++)
        {
            if (fieldType == typeField[i])
            {
                vector<string>field = { fieldName, fieldType };
                this->fields.push_back(field);
                e = 0;
                break;
            }
        }
        if (e)
            throw exception("Wrong field type! Please use types: INTEGER, BLOB, REAL, NUMERIC, TEXT");
        return this;
    }
private:
    string tableName;
    vector<vector<string>> fields;
    string typeField[5] = { "INTEGER","BLOB","REAL","NUMERIC","TEXT" };
};