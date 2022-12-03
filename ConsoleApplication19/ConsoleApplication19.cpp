
#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <vector>
#include <exception>
#include "../sqlite3orm.h"
#include "../Sql3_scheme.h"

using namespace std;


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


