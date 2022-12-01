#include <sqlite3.h>
#include <stdio.h>
#include "sqlite3orm.h"



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
    
    sql = "SELECT * from COMPANY";
    
    user user1;
    user& user1link = user1;

    sqlite3orm::getInstance()->exec(sql, callback, (void *)data);

    //printf("%i\n", user1->id ); 
    
    return 0;
}
