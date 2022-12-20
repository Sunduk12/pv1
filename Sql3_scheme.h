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
    Fields* primaryKey()
    {
        this->limit = "PRIMARY KEY";
        return this;
    }
    string getField()
    {
        return this->fieldName + ' ' + this->fieldType+' '+this->limit;
    }

private:
    string fieldType;
    string fieldName;
    string limit;
};

class Sql3_scheme {
public:

    string create(bool ifNotExists = false)
    {

        this->sql = "CREATE TABLE ";
        if (ifNotExists)
            this->sql = this->sql + "IF NOT EXISTS ";

        this->sql = this->sql + this->tableName;
        this->sql = this->sql + '(' + '\n';
        for (int i = 0;i < this->fields.size();i++)
        {    
            this->sql = this->sql + this->fields[i]->getField();
            
            if (this->fields.size() - 1 == i)
                this->sql = this->sql + '\n';
            else
                this->sql = this->sql + ',' + '\n';
        }
        this->sql = this->sql + ");";
        clear();
        return this->sql;
    }
    string drop(bool ifExists = false)
    {
        this->sql = "DROP TABLE ";
        if (ifExists)
            this->sql = this->sql + "IF NOT EXISTS ";
        this->sql= this->sql + this->tableName;
       clear();
        return this->sql;
    }
    string rename(string newTableName)
    {
        this->sql = "ALTER TABLE " + this->tableName + " RENAME TO " + newTableName;
        clear();
        return this->sql;
    }
    string dropColumn(string columnName)
    {
        this->sql = "ALTER TABLE " + this->tableName + " DROP COLUMN " + columnName;
        clear();
        return this->sql;
    }
    string addColumn(Fields* field)
    {
                 this->sql = "ALTER TABLE " + this->tableName + " ADD COLUMN " + field->getField();
                clear();
                return this->sql;
    }
    string renameColumn(string columnName, string newColumnName)
    {
        this->sql = "ALTER TABLE " + this->tableName + " RENAME COLUMN " + columnName +" TO " + newColumnName;
        clear();
        return this->sql;
    }
    string createIndex(string indexName, bool ifNotExists=false)
    {
        this->sql = "CREATE INDEX ";
        if (ifNotExists)
            this->sql = this->sql + "IF NOT EXISTS ";
        this->sql = this->sql  + indexName + " ON " + this->tableName + " (";
        for (int i = 0;i < this->columnsToIndex.size();i++)
        {
            this->sql = this->sql + this->columnsToIndex[i];

            if (this->columnsToIndex.size() - 1 == i)
                this->sql = this->sql+')';
            else
                this->sql = this->sql + ',' + ' ';
        }
        return this->sql;
        clear();
    }
    string dropIndex(string indexName)
    {
        this->sql = "DROP INDEX " + indexName;
        return this->sql;
        clear();
    }
    string reindex(string indexOrTableName)
    {
        this->sql = "REINDEX " + indexOrTableName;
        return this->sql;
        clear();
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
    Sql3_scheme* addColumnToIndex(string columnName)
    {
        this->columnsToIndex.push_back(columnName);
            return this;
    }
    void clear()
    {
        for (int i = 0;i < this->fields.size();i++) {
            delete this->fields[i];
        }
        this->tableName.clear();
        vector<Fields*>().swap(this->fields);
        vector<string>().swap(this->columnsToIndex);
    }
    string getRawSql()
    {
        return this->sql;
    }
private:
    string tableName;
    vector<Fields*> fields;
    string typeField[5] = { "INTEGER","BLOB","REAL","NUMERIC","TEXT" };
    string sql;
    vector<string> columnsToIndex;
};