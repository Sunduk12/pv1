#include <sqlite3.h>
#include <stdio.h>
#include "sqlite3orm.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string selectSQL(string tableName, vector <string> vfields)
{

string select = "SELECT";
string from = "FROM";
string fields;
for (int i = 0; i < vfields.size(); i++)
{  
    fields += vfields[i] + "," + " ";
}
fields.pop_back();
fields.pop_back();

string result = select + " " + fields + " " + from + " "+ tableName;
return result;
}


static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: \n", (const char *)data);
    //data.id = i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    const char *sql;
    const char *data = "Callback function called";
    
    user user1;
    user& user1link = user1;

vector <string> vfields = {"ID", "AGE", "NAME"};
string result = selectSQL("COMPANY", vfields);


const char *requestSql  = result.data();

sqlite3orm::getInstance()->exec(requestSql, callback, (void *)data);

return 0;
}
