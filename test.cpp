#include <sqlite3.h>
#include <stdio.h>
#include "sqlite3orm.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class querySQL
{
public:

querySQL* where(string fieldName, string meaning, string fieldIF)
{

this->resWhere = "where " + fieldName + " " + meaning + " '" + fieldIF + "';";

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

string result = this->queryType + " " + fields +  " from " + tableName + "\n" + resWhere;
return result;

}


querySQL* select(string tableName)
{
this->tableName = tableName;
this->queryType = "select";

return this;
}

querySQL* addFields(string vfields)
{
    this->vfields.push_back(vfields);

return this;
}


private:


vector <string> vfields;
string tableName;
string queryType;

string fieldIF;
string meaning;
string fieldName;
string resWhere;

};


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

querySQL *a = new querySQL();

string result = a->select("COMPANY")->where("NAME", "=", "roma")->selectSQL();



const char *requestSql  = result.data();
sqlite3orm::getInstance()->exec(requestSql, callback, (void *)data);

// querySQL wh;

// wh.where("Name", "=", "roma");
return 0;
}
