#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "sqlite3orm.h"
#include "Sql3_query.h"

using namespace std;

int main(int argc, char const *argv[])
{
    const char *sql;
    const char *data = "Callback function called";

    user user1;
    user &user1link = user1;

    querySQL *a = new querySQL();

    //  cout << a->select("COMPANY")->insert("COMPANY","ID, NAME, AGE", "10,'vlad', 37")->selectSQL();

    // string result = a->insert("COMPANY", "ID, NAME, AGE", "21,'misha', 74000")->selectSQL();
    string result = a->selectTable("COMPANY")->addFields("NAME")->addFields("AGE")->selectSQL();

    const char *requestSql = result.data();
    sqlite3orm::getInstance()->execAndPrint(requestSql);

    return 0;
}