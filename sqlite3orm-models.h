class sqlite3ormModel
{
private:
    const char *tableName;

public:
    sqlite3ormModel(/* args */);
    ~sqlite3ormModel();

    /**
     * заполняет данные из дб
     */
    // void fillCallbackRow(void *data, int argc, char **argv, char **azColName)
    // {
    //     int i;
    //     fprintf(stderr, "%s: ", (const char *)data);

    //     for (i = 0; i < argc; i++)
    //     {
    //         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    //     }

    //     printf("\n");
    // }

    void fill()
    {
    }
};

sqlite3ormModel::sqlite3ormModel(/* args */)
{
}

sqlite3ormModel::~sqlite3ormModel()
{
}

class user : public sqlite3ormModel
{
    
private:
public:
    int id;
    char* name;
    
    user()
    {
    }
    ~user(){};
};
