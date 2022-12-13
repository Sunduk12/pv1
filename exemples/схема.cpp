#include <stdio.h> 
#include <sqlite3.h>  
#include <string> 
#include <iostream> 
#include <vector> 
#include <exception>
#include "../sqlite3orm.h" 
#include "../Sql3_scheme.h"

using namespace std;

int main()
{
	Sql3_scheme* new_scheme = new Sql3_scheme;
	string sql = new_scheme->table("chello") // указываем имя таблицы
		->addField(new_scheme->newField()->name("age")->integer()) // добавляем поле типа INTEGER
		->addField(new_scheme->newField()->name("name")->text()) // добавляем поле типа TEXT
		->addField(new_scheme->newField()->name("sgz")->blob()) //добавляем поле типа BLOB
		->addField(new_scheme->newField()->name("wgds")->real()) // добавляем поле типа REAL
		->addField(new_scheme->newField()->name("fgdfg")->numeric()) //добавляем поле типа NUMERIC
		->create(true); // если тру, влючает иф нот екзист

	const char* sqll = sql.data();
	cout << sqll << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll);

	Sql3_scheme* new_scheme4 = new Sql3_scheme;
	string Sql2 = new_scheme4->table("chello")
		->rename("Hello");//поменяли название таблицы
	const char* sqll3 = Sql2.data();
	cout << sqll3 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll3);

	Sql3_scheme* new_scheme5 = new Sql3_scheme;
	string Sql3 = new_scheme5->table("Hello")
		->addColumn("sdada", "TEXT");//добавили новую колонку
	const char* sqll4 = Sql3.data();
	cout << sqll4 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll4);

	Sql3_scheme* new_scheme6 = new Sql3_scheme;
	string Sql4 = new_scheme6->table("Hello")
		->renameColumn("sdada", "Text"); //переименовали колонку
	const char* sqll5 = Sql4.data();
	cout << sqll5 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll5);

	Sql3_scheme* new_scheme2 = new Sql3_scheme;
	string Sql = new_scheme2->table("Hello")
		->dropColumn("age"); //удалить колонку age
	const char* sqll1 = Sql.data();
	cout << sqll1 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll1);

	//Sql3_scheme* new_scheme3 = new Sql3_scheme;
	//string Sql1 = new_scheme3->table("Hello")
	//	->drop();// удаление таблицы
	//const char* sqll2 = Sql1.data();
	//cout << sqll2 << '\n';
	//sqlite3orm::getInstance()->execAndPrint(sqll2);
}