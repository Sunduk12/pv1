class querySQL
{
public:
    // ОСНОВНОЙ БИЛДЕР
    string SQL()
    {

        if (this->queryType == "select")
            return this->buildSelect();
        else if (this->queryType == "insert")
            return this->buildInsert();
        else if (this->queryType == "update")
            return this->buildUpdate();
        else if (this->queryType == "delete")
            return this->buildDelete();
        else if (this->queryType == "replace")
            return this->buildReplace();

        return "error";
    }
    // билдеры
    string buildReplace()
    {
        resReplace = "INSERT OR REPLACE INTO " + this->tableName + " ( " + columnName + " ) " + "\n" + "VALUES " + " ( " + fieldName + " ) ";

        return resReplace;
    }

    string buildDelete()
    {
        resDelete = "DELETE FROM " + this->tableName + "\n" + "WHERE " + strWhereDelete;

        return resDelete;
    }

    string buildUpdate()
    {

        resUpdate = "UPDATE " + this->tableName + "\n" + "SET " + strSetUpdate + "\n" + "WHERE " + strWhereUpdate + ";";

        return resUpdate;
    }

    string buildSelect()
    {
        string fields;

        if (vfields.size() == 0)
        {
            fields = "*";
        }
        else
        {
            for (int i = 0; i < this->vfields.size(); i++)
            {
                fields += this->vfields[i] + "," + " ";
            }
            fields.pop_back();
            fields.pop_back();
        }
        resSelectTable = this->queryType + " " + fields + " from " + tableName + " " + resWhere + " " + resWhereAnd + " " + resWhereOr;

        return resSelectTable;
    }

    string buildInsert()
    {
        resInsert = "insert into " + this->tableName + " ( " + columnName + " ) " + " values " + " ( " + fieldName + " )";

        return resInsert;
    }

    /////////////////////////////////
    // queryType

    querySQL *select()
    {
        this->queryType = "select";
        return this;
    }

    querySQL *insert(string expression)
    {
        this->queryType = "insert";
        return this;
    }

    querySQL *update()
    {
        this->queryType = "update";
        return this;
    }

    querySQL *delete1()
    {
        this->queryType = "delete";
        return this;
    }

    querySQL *replace()
    {
        this->queryType = "replace";
        return this;
    }

    querySQL *table(string tableName)
    {
        this->tableName = tableName;

        return this;
    }

    //------------------------------------
    // сбор информации

    querySQL *orWhere(string fieldName, string value, string fieldIF)
    {
        this->resWhereOr = " or " + fieldName + " " + value + " '" + fieldIF + +"'";

        return this;
    }

    querySQL *andWhere(string fieldName, string value, string fieldIF)
    {
        this->resWhereAnd = " and " + fieldName + " " + value + " '" + fieldIF + +"'";

        return this;
    }

    querySQL *where(string fieldName, string value, string fieldIF)
    {
        int e = 1;

        for (int i = 0; i < 7; i++)
        {
            if (value == conditionWhere[i])
            {
                e = 0;
                break;
            }
        }

        if (e)
            throw std::runtime_error("no such condition exists! enter one of the following: =, !=, <>, >, <, <=, >=");

        this->resWhere = "where " + fieldName + " " + value + " '" + fieldIF + +"'";
        return this;
    }

    querySQL *addColumn(string columnName)
    {
        this->columnName = columnName;

        return this;
    }

    querySQL *addFields(string vfields)
    {
        this->vfields.push_back(vfields);
        this->fieldName = vfields;

        return this;
    }

    querySQL *setUpdate(string strSetUpdate)
    {
        this->strSetUpdate = strSetUpdate;

        return this;
    }

    querySQL *whereUpdate(string strWhereUpdate)
    {
        this->strWhereUpdate = strWhereUpdate;

        return this;
    }

    querySQL *whereDelete(string strWhereDelete)
    {
        this->strWhereDelete = strWhereDelete;

        return this;
    }

private:
    // исключения
    string fieldIF;
    string conditionWhere[7] = {"=", "!=", "<>", ">", "<", "<=", ">="};

    // delete informatiom
    string strWhereDelete;

    //  update informatiom
    string strSetUpdate;
    string strWhereUpdate;

    // результаты сбора инф
    vector<string> vfields;
    string tableName;
    string queryType;
    string fieldName;
    string columnName;
    string resWhere;
    string resWhereOr;
    string resWhereAnd;
    string resAddFields;

    // результаты билдеров
    string resInsert;
    string resSelectTable;
    string resUpdate;
    string resDelete;
    string resReplace;
};