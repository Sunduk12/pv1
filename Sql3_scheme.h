#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <vector>
#include <exception>


using namespace std;
class Fields
{
public:
    Fields* name(string fieldName)
    {
        this->fieldName = fieldName;
        return this;
    }
    Fields* integer()
    {
        this->fieldType = "INTEGER";
        return this;
    }
    Fields* text()
    {
        this->fieldType = "TEXT";
        return this;
    }
    Fields* blob()
    {
        this->fieldType = "BLOB";
        return this;
    }
    Fields* numeric()
    {
        this->fieldType = "NUMERIC";
        return this;
    }
    Fields* real()
    {
        this->fieldType = "REAL";
        return this;
    }
    string getField()
    {
        return this->fieldName + ' ' + this->fieldType;
    }
private:
    string fieldType;
    string fieldName;
    string fieldIndex;
};

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
                sql = sql + this->fields[i]->getField();
            
            if (this->fields.size() - 1 == i)
                sql = sql + '\n';
            else
                sql = sql + ',' + '\n';
        }
        sql = sql + ");";
        return sql;
    }
    string drop(bool ifExists = false)
    {
        string sql = "DROP TABLE ";
        if (ifExists)
            sql = sql + "IF NOT EXISTS ";
       sql=sql + this->tableName;
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
    Sql3_scheme* addField(Fields* field)
    {
       this->fields.push_back(field);
        return this;
    }
    Fields* newField()
    {
        Fields* field = new Fields;
        return field;
    }
private:
    string tableName;
    vector<Fields*> fields;
    string typeField[5] = { "INTEGER","BLOB","REAL","NUMERIC","TEXT" };
};

