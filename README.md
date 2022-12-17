Этот проект является студенческим заданием в ВФ УдГУ в группе ИСиП 2 курс.
#



# SQLite3 ORM: обзор

**ORM** — технология программирования, которая связывает базы данных с концепциями объектно-ориентированных языков программирования, создавая «виртуальную объектную базу данных».

## До начала работы

Установить зависимости SQLite3 и [библиотеку](https://www.sqlite.org/cintro.html) для работы cpp. Вы можете использовать для этого [менеджер пакетов](https://github.com/microsoft/vcpkg).

Перед тем как приступить к работе, необходимо скачать библиотеки `sqlite3orm-models.h` и `sqlite3orm.h` из нашего репозитория.

Далее добавляем эти библиотеки в наш проект и подключаем их:
```c++
 #include "sqlite3orm.h"
```

<br>Вы можете использовать функцию *main* для выполнения SQL запросов:

```c++
  int main(int argc, char const* argv[])
  {
     const char* sql;
     sql = "SELECT * from chello";
     sqlite3orm::getInstance()->execAndPrint(sql);
     return 0;
  }
```

## Работа с таблицами

Для начала нам нужно создать таблицу. Для этого испульзуем:
```c++
Sql3_scheme* new_scheme = new Sql3_scheme; 
	string sql = new_scheme->table("chello")
```
Название таблицы можно сделать любым.

<br>Для добавления колонки в таблицу используется:
```c++
->addField(new_scheme->newField()->name("age")->integer())
```
Всего типов данных в колонках 5: INTEGER, TEXT, BLOB, REAL, NUMERIC. Для каждого типа данных нужна своя колонка.

<br>Для реализации кода используется:

```c++
const char* sqll = sql.data();
	cout << sqll << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll);
```
<br>Если хотите переименовать таблицу:

```c++
Sql3_scheme* new_scheme4 = new Sql3_scheme;
	string Sql2 = new_scheme4->table("chello")
		->rename("Hello");
	const char* sqll3 = Sql2.data();
	cout << sqll3 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll3);
```

<br>Если хотите добавить новый столбец столбец:

```c++
Sql3_scheme* new_scheme5 = new Sql3_scheme;
	string Sql3 = new_scheme5->table("Hello")
		->addColumn("sdada", "TEXT");
		const char* sqll4 = Sql3.data();
	cout << sqll4 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll4);
```
<br>Ессли хотите переименовать столбец:

```c++
Sql3_scheme* new_scheme6 = new Sql3_scheme;
	string Sql4 = new_scheme6->table("Hello")
		->renameColumn("sdada", "Text"); 
		const char* sqll5 = Sql4.data();
	cout << sqll5 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll5);
```
Переименовывать можно любые столбцы, которые есть в вашей таблице.

<br>Если хотите удалить столбец:

```c++
Sql3_scheme* new_scheme2 = new Sql3_scheme;
	string Sql = new_scheme2->table("Hello")
		->dropColumn("age"); 
	const char* sqll1 = Sql.data();
	cout << sqll1 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll1);
```

<br>Если хотите удалить всю таблицу:

```c++
Sql3_scheme* new_scheme3 = new Sql3_scheme;
	string Sql1 = new_scheme3->table("Hello")
		->drop();
	const char* sqll2 = Sql1.data();
	cout << sqll2 << '\n';
	sqlite3orm::getInstance()->execAndPrint(sqll2);
```