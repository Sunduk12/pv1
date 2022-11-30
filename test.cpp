#include <sqlite3.h>
#include <stdio.h>
#include "sqlite3orm.h"

sqlite3orm * sqlite3orm::p_instance = 0;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    char *zErrMsg = 0;
    int rc;
    const char *sql;
    const char *data = "Callback function called";

    /* Create SQL statement */
    sql = "SELECT * from COMPANY";

    /* Execute SQL statement */
    rc = sqlite3orm::getInstance()->exec(sql, callback, (void *)data, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Operation done successfully\n");
    }
    
    return 0;
}
