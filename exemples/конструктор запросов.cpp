#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <exception>

#include "../sqlite3orm.h" 
// #include "../Sql3_scheme.h"
#include "../Sql3_query.h"

using namespace std;

int main(int argc, char const *argv[])
{
    querySQL *a = new querySQL();

    // метод инсерт
    // string result =  a->insert()->table("COMPANY")->addFields("6, 'chicha', 10, 'Home', 0")->addColumn("ID, NAME, AGE, ADDRESS, SALARY")->buildInsert(); 

    // метод select
    string result =  a->select()->table("COMPANY")->buildSelect();

    //select с условиями
    //string result =  a->select()->table("COMPANY")->where("NAME", "=", "roma")->buildSelect();

    //string result =  a->select()->table("COMPANY")->where("AGE", "<", "20")->andWhere("SALARY", ">=", "100")->buildSelect();


    // string result =  a->select()->table("COMPANY")->where("AGE", "<", "20")->orWhere("SALARY", ">", "100")->buildSelect();

    //метод  update
    // string result =  a->update()->table("COMPANY")->setUpdate("NAME = 'roma'")->whereUpdate("NAME = 'ROMA'")->SQL();

    //метод delete
    //string result =  a->delete1()->table("COMPANY")->whereDelete("NAME = 'roma'")->SQL();

    //метод replace
    //string result = a->replace()->table("COMPANY")->addColumn("ID, NAME, AGE, ADDRESS, SALARY")->addFields("6, 'chicha', 10, 'Home', 100")->SQL();


    //  cout << result;

    const char *requestSql = result.data();
    sqlite3orm::getInstance()->execAndPrint(requestSql);

    return 0;
}