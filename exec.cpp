#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <stdexcept>
#include <iostream>
#include <vector>


//название таблицы и массив строк ключ и значение 
//метод инсерт и селект принимает и возвращает

class connection_bad_exception : std::exception {
public:
    connection_bad_exception(const char * message) {
        this->message = message;
    }
    virtual const char* what(){
        return message;
    }
private:
    const char* message;
};

// model example
class Company
{
public:
    int ID;
    const char* NAME;
    int AGE;
};


class ORM_DATA final
{
public:
    ORM_DATA(const char* db_name)
    {
        this->db_name = db_name;
    }

    void open() {
        int rc = sqlite3_open(db_name, &db);
        if (rc) throw connection_bad_exception("Connection error");
    }

    void close() {
        sqlite3_close(db);
    }
    /// @brief 
    /// @tparam model модель таблицы в базе данных
    /// @param sql_query SQL-запрос 
    /// @return 
    template <typename model>
    std::vector<model*>* query(const char* sql_query) {
        auto collection = new std::vector<model*>();

        

        return collection;
    }

    ~ORM_DATA();
private:
   sqlite3 *db;
   char *zErrMsg = 0;
   char *sql;
   const char* data = "Callback function called";
   const char* db_name;
};




static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
    try {
       
    } catch(connection_bad_exception& e) {
        auto x = e.what();
        std::cout << x << '\n';
    }
    
//    sqlite3 *db;
//    char *zErrMsg = 0;
//    int rc;
//    char *sql;
//    const char* data = "Callback function called";

//    /* Open database */
//    rc = sqlite3_open("test.db", &db);
   
//    if( rc ) {
//       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//       return(0);
//    } else {
//       fprintf(stderr, "Opened database successfully\n");
//    }

//    /* Create SQL statement */
//    sql = "SELECT * from COMPANY";

//    /* Execute SQL statement */
//    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
//    if( rc != SQLITE_OK ) {
//       fprintf(stderr, "SQL error: %s\n", zErrMsg);
//       sqlite3_free(zErrMsg);
//    } else {
//       fprintf(stdout, "Operation done successfully\n");
//    }
//    sqlite3_close(db);
   return 0;
}