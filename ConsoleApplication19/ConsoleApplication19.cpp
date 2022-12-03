
#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "../sqlite3orm.h"


using namespace std;
class Sql3_scheme {
public:

    string sql3_tab(bool ifNotExists=false)
    {

        string sql = "CREATE TABLE ";
        if (ifNotExists)
            sql = sql + "IF NOT EXISTS ";
            
        sql=sql +this->table_name;
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
        string sql="DROP TABLE "+ this->table_name;
        return sql;
    }
    string rename(string newTableName)
    {
        string sql = "ALTER TABLE " + this->table_name + " RENAME TO " + newTableName;
        return sql;
    }
    string truncate()
    {
        string sql = "TRUNCATE TABLE " + this->table_name;
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
    string type_field[5] = {"INTEGER","BLOB","REAL","NUMERIC","TEXT" };
};

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: \n", (const char*)data);
    //data.id = i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char* argv[])
{
    const char* data = "dsfdg";
    Sql3_scheme* new_scheme = new Sql3_scheme;
   // cout << new_scheme->add_field("age", "INTEGER")->add_field("name", "text")->add_field("address","BLOB")->table("chello")->sql3_tab();
    string sql = new_scheme->table("chello")->rename("nechello");
  //     ->add_field("age", "INTEGER")
  //     ->add_field("name", "TEXT")
  //     ->add_field("address", "BLOB")
  //   ->table("chello")
  //     ->sql3_tab(true);
 
   const char* sql1 = sql.data();
   cout << sql1<<'\n';
  sqlite3orm::getInstance()->exec(sql1,callback,(void *)data);
    // ->rename("nechello");
  //  vector< vector<string>> mass = { { "age","INT"},{"name","TEXT"},{"address","TEXT"} };
    //cout << ("chello", mass); 
   
}


