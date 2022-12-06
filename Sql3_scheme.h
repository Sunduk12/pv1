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

        sql = sql + this->table_name;
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
        string sql = "DROP TABLE " + this->table_name;
        return sql;
    }
    string rename(string newTableName)
    {
        string sql = "ALTER TABLE " + this->table_name + " RENAME TO " + newTableName;
        return sql;
    }
    string dropColumn(string columnName)
    {
        string sql = "ALTER TABLE " + this->table_name + " DROP COLUMN " + columnName;
        return sql;
    }
    string addColumn(string columnName,string columnType)
    {
        int e = 1;


        for (int i = 0;i < 5;i++)
        {
            if (columnType == type_field[i])
            {
                string sql = "ALTER TABLE " + this->table_name + " ADD COLUMN " + columnName + ' ' + columnType;
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
        string sql = "ALTER TABLE " + this->table_name + " RENAME COLUMN " + columnName +" TO " + newColumnName;
        return sql;
    }
    Sql3_scheme* table(string table_name)
    {
        this->table_name = table_name;
        return this;
    }
    Sql3_scheme* add_field(string field_name, string field_type)
    {
        int e = 1;


        for (int i = 0;i < 5;i++)
        {
            if (field_type == type_field[i])
            {
                vector<string>field = { field_name, field_type };
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
    string table_name;
    vector<vector<string>> fields;
    string type_field[5] = { "INTEGER","BLOB","REAL","NUMERIC","TEXT" };
};