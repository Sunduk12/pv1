
#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Sql3_scheme {
public:
    string sql3_tab()
    {

        string sql = "CREATE TABLE " +this->table_name;
        sql = sql + '(' + '\n';
        for (int i = 0;i < this->fields.size();i++)
        {
            for (int j = 0; j < this->fields[i].size();j++)
            {
                sql = sql + this->fields[i][j] + "    ";
            }
            sql = sql + '\n';
        }
        sql = sql + ");";
        return sql;
    }
    Sql3_scheme table(string table_name)
    {
        this->table_name = table_name;
        return *this;
    }
    Sql3_scheme add_field(string field_name, string field_type) 
    {
        vector<string>field = { field_name, field_type };
        this->fields.push_back(field);
        return *this;
    }
private:
    string table_name;
    vector<vector<string>> fields;
};

int main(int argc, char* argv[])
{
    Sql3_scheme new_scheme;
   cout<< new_scheme.add_field("age", "INT").add_field("name", "TEXT").table("chello").sql3_tab();

  //  new_scheme.add_field("name", "TEXT");
    
  //  vector< vector<string>> mass = { { "age","INT"},{"name","TEXT"},{"address","TEXT"} };
    //cout << ("chello", mass); 
   
}


