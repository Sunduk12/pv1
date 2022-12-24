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
	setlocale(LC_ALL, "rus");

	cout << "Для создания новой таблицы введите ее название:" << '\n';
	string table;
	cin >> table;
	Sql3_scheme* new_scheme = new Sql3_scheme;


	cout << "Хотите добавить новую колонку? Да - 1, нет - 2(написать нужную цифру)." << '\n';
	int choise;
	cin >> choise;

	while (choise == 1)
	{
		cout << "Для создания новой колонки введите ее название:" << '\n';
		string column;
		cin >> column;
		cout << "Выберите тип колонки: INTEGER - 1, TEXT - 2, BLOB - 3, REAL - 4, NUMERIC - 5 (написать нужную цифру)." << '\n';
		int type;
		cin >> type;
		Fields* field = new_scheme->newField()->name(column);
		if (type == 1)
		{
			new_scheme->addField(field->integer()); // добавляем поле типа INTEGER
		}

		else if (type == 2)
		{
			new_scheme->addField(field->text()); // добавляем поле типа TEXT
		}

		else if (type == 3)
		{
			new_scheme->addField(field->blob()); //добавляем поле типа BLOB
		}

		else if (type == 4)
		{
			new_scheme->addField(field->real()); // добавляем поле типа REAL
		}

		else if (type == 5)
		{

			new_scheme->addField(field->numeric()); //добавляем поле типа NUMERIC
		}

		else
		{
			cout << "Некорректный ввод" << '\n';
		}

		cout << "Хотите добавить новую колонку? Да - 1, нет - 2(написать нужную цифру)." << '\n';
		cin >> choise;
	}

	string sql = new_scheme->create(true);
	const char* sqll = sql.data();
	cout << sqll << '\n';
	//sqlite3orm::getInstance()->execAndPrint(sqll);