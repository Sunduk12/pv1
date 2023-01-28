class queryBuilder
{
public:
    // ОСНОВНОЙ БИЛДЕР
    string SQL()
    {
        // обработка всех запросов
        if (this->queryType == "select") return this->buildSelect();
        if (this->queryType == "insert") return this->buildInsert();
        if (this->queryType == "insert") return this->buildDelete();
        if (this->queryType == "insert") return this->buildDistinct();
        if (this->queryType == "insert") return this->buildReplace();
        if (this->queryType == "insert") return this->buildUpdate();

        return "error";
    }
    // ОСНОВНЫЕ ОПЕРАЦИИ С ДАННЫМИ (БИЛДЕРЫ)
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
        return sql = this->queryType + " " + fields + " FROM " + tableName + " " + buildWhere();
    }
    //Сделать нормальный метод Insert 
    string buildInsert()
    {
        sql = "INSERT INTO " + this->tableName + " ( " + this->columnName + " ) " + " VALUES " + " ( " + this->fieldName + " )";

        return sql;
    }

    string buildDistinct()
    {
        // выборка уникальных значений из колонки!
        sql = "SELECT DISTINCT " + columnName + " FROM " + this->tableName + ";";

        return sql;
    }

    string buildReplace()
    {
        sql = "INSERT OR REPLACE INTO " + this->tableName + " ( " + this->columnName + " ) " + "\n" + "VALUES " + " ( " + this->fieldName + " ) ";

        return sql;
    }

    string buildDelete()
    {
        sql = "DELETE FROM " + this->tableName + "\n" + buildWhere();

        return sql;
    }

    string buildUpdate()
    {

        sql = "UPDATE " + this->tableName + "\n" + "SET " + strSetUpdate + "\n" + buildWhere() + ";";

        return sql;
    }
        // ДОП БИЛДЕРЫ
        string
        buildWhere()
    {
        string where = " WHERE ";
        if (vWhere.size() == 0)
        {
            return "";
        }

        vWhere.erase(vWhere.begin());
        for (int i = 0; i < this->vWhere.size(); i++)
        {
            where += this->vWhere[i];
        }

        return where;
    }

    // СБОР ИНФОРМАЦИИ ДЛЯ БИЛДЕРОВ
    queryBuilder *setUpdate(string strSetUpdate)
    {
        this->strSetUpdate = strSetUpdate;

        return this;
    }

    queryBuilder *table(string tableName)
    {
        this->tableName = tableName;

        return this;
    }
    queryBuilder *addColumn(string columnName)
    {
        this->columnName = columnName;

        return this;
    }
    queryBuilder *addFields(string vfields)
    {
        this->vfields.push_back(vfields);
        this->fieldName = vfields;

        return this;
    }
    queryBuilder *where(string fieldName, string condition, string value, string orAnd = "and")
    {
        // Обработка исключения condition where
        int e = 1;
        for (int i = 0; i < 7; i++)
        {
            if (condition == conditionWhere[i])
            {
                e = 0;
                break;
            }
        }
        if (e)
            throw std::runtime_error("no such condition exists! enter one of the following: =, !=, <>, >, <, <=, >=");
        // Обработка исключения where or and
        int e1 = 1;
        for (int i = 0; i < 16; i++)
        {
            if (orAnd == orAndwhere[i])
            {
                e1 = 0;
                break;
            }
        }
        if (e1)
            throw std::runtime_error("you have selected an invalid operation! please choose one of the options: or, and");

        this->resWhere = fieldName + " " + condition + " '" + value + "'";
        this->resWhereOrAnd = " " + orAnd + " ";
        this->vWhere.push_back(resWhereOrAnd);
        this->vWhere.push_back(resWhere);
        return this;
    }
    // УСТАНОВКА queryType ДЛЯ СБОРКИ
    queryBuilder *select()
    {
        this->queryType = "select";
        return this;
    }

    queryBuilder *insert()
    {
        this->queryType = "insert";
        return this;
    }

    queryBuilder *update()
    {
        this->queryType = "update";
        return this;
    }

    queryBuilder *remove() // remove = delete SQL
    {
        this->queryType = "delete";
        return this;
    }

    queryBuilder *replace()
    {
        this->queryType = "replace";
        return this;
    }
    queryBuilder *distinct()
    {
        this->queryType = "distinct";
        return this;
    }
private:
    vector<string> vfields;
    string queryType;
    string tableName;
    string columnName;
    string fieldName;
    string sql;
    //update
    string strSetUpdate;
    // для where
    vector<string> vWhere;
    string resWhere;
    string resWhereOrAnd;
    // исключения
    string orAndwhere[16] = {"or", "or ", " or", " or ", "and", "and ", " and", " and ", "OR", "OR ", " OR", " OR ", "AND", "AND ", " AND", " AND "};
    string conditionWhere[7] = {"=", "!=", "<>", ">", "<", "<=", ">="};
};