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
    //string result =  a->insert()->table("COMPANY")->addFields("12, 'danil', 5, 'gorod', 55")->addColumn("ID, NAME, AGE, ADDRESS, SALARY")->SQL();

    // метод select
    //string result =  a->select()->addFields("NAME")->table("COMPANY")->SQL();

    // select с условиями
    //string result =  a->select()->table("COMPANY")->where("NAME", "=", "roma")->SQL();

    //string result =  a->select()->table("COMPANY")->where("AGE", "<", "20")->andWhere("SALARY", ">=", "100")->SQL();

    // string result =  a->select()->table("COMPANY")->where("AGE", "<", "20")->orWhere("SALARY", ">", "100")->SQL();

    // метод  update
    //string result =  a->update()->table("COMPANY")->setUpdate("NAME = 'ALEKSANDR'")->whereUpdate("NAME = 'graghdanin'")->SQL();

    // метод delete
    //string result =  a->remove()->table("COMPANY")->whereDelete("NAME = 'roma'")->SQL();

    // метод replace
    // string result = a->replace()->table("COMPANY")->addColumn("ID, NAME, AGE, ADDRESS, SALARY")->addFields("6, 'chicha', 10, 'Home', 100")->SQL();

    //метод distinct выборка уникальных значений
    //string result = a->distinct()->table("COMPANY")->addColumn("NAME")->SQL();


    //////////////////Операторы фильтрации
    // оператор IN
    //string result = a->operatorIN()->table("COMPANY")->addColumn("NAME")->addFields("'Roma', 'andrey'")->SQL();

    //оператор NOT IN 
    // string result = a->operatorNOTIN()->table("COMPANY")->addColumn("NAME")->addFields("'Roma', 'andrey'")->SQL();

    //оператор between
    //string result = a->operatorBetween()->table("COMPANY")->addColumn("AGE")->BetweenFields("10", "17")->SQL();

    //оператор not between
    // string result = a->operatorNotBetween()->table("COMPANY")->addColumn("AGE")->BetweenFields("10", "17")->SQL();

    //оператор LIKE 
    // string result = a->operatorLIKE()->table("COMPANY")->addColumn("NAME")->addFields("'roma'")->SQL();
    
    //оператор GLOB
    string result = a->operatorGLOB()->table("COMPANY")->addColumn("NAME")->addFields("'das*'")->SQL();


    // cout << result << endl;

    const char *requestSql = result.data();
    sqlite3orm::getInstance()->execAndPrint(requestSql);

    return 0;
}