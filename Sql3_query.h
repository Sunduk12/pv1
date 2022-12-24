class filterOperator
{
public:
    // filter operators

    filterOperator(string fieldName ,string condition ,string value)
    {
        this->value = value;
        this->fieldName = fieldName;
        this->condition = condition;
    }

    string getWhere()
    {
        string getWhere = fieldName + " " + condition + " '" + value + "' ";
        return getWhere;
    }

    filterOperator *operatorIN()
    {
        this->operatorType = "IN";

        return this;
    }

    filterOperator *operatorNOTIN()
    {
        this->operatorType = "NOT IN";

        return this;
    }

    filterOperator *operatorBetween()
    {
        this->operatorType = "BETWEEN";

        return this;
    }

    filterOperator *operatorNotBetween()
    {
        this->operatorType = "NOT BETWEEN";

        return this;
    }

    filterOperator *operatorLIKE()
    {
        this->operatorType = "LIKE";

        return this;
    }

    filterOperator *operatorGLOB()
    {
        this->operatorType = "GLOB";

        return this;
    }

    filterOperator *operatorISnull()
    {
        this->operatorType = "IS NULL";

        return this;
    }

    filterOperator *operatorISnotNULL()
    {
        this->operatorType = "IS NOT NULL";

        return this;
    }

private:
    string operatorType;
    string fieldName;
    string condition;
    string value;

};

class querySQL
{
public:
    // ОСНОВНОЙ БИЛДЕР
    string SQL()
    {
        // обработка всех запросов
        // queryType
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
        else if (this->queryType == "distinct")
            return this->buildDistinct();
        // operatorType
        // else if (this->operatorType == "IN")
        //     return this->buildOperatorIN();
        // else if (this->operatorType == "NOT IN")
        //     return this->buildOperatorNOTIN();
        // else if (this->operatorType == "BETWEEN")
        //     return this->buildOperatorBetween();
        // else if (this->operatorType == "NOT BETWEEN")
        //     return this->buildOperatorNotBetween();
        // else if (this->operatorType == "LIKE")
        //     return this->buildOperatorLIKE();
        // else if (this->operatorType == "GLOB")
        //     return this->buildOperatorGLOB();
        // else if (this->operatorType == "IS NULL")
        //     return this->buildOperatorISNULL();
        // else if (this->operatorType == "IS NOT NULL")
        //     return this->buildOperatorISnotNULL();

        return "error";
    }
    // билдеры для operatorType ___________
    string buildOperatorISnotNULL()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " IS NOT NULL" + ";";

        return sql;
    }

    string buildOperatorISNULL()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " IS NULL" + ";";

        return sql;
    }

    string buildOperatorGLOB()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " GLOB " + this->fieldName + ";";

        return sql;
    }

    string buildOperatorLIKE()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " LIKE " + this->fieldName + ";";

        return sql;
    }

    string buildOperatorIN()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " IN " + " ( " + this->fieldName + " ) " + ";";

        return sql;
    }

    string buildOperatorNOTIN()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " NOT IN " + " ( " + this->fieldName + " ) " + ";";

        return sql;
    }

    string buildOperatorBetween()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " BETWEEN " + fields1 + " AND " + fields2 + ";";

        return sql;
    }

    string buildOperatorNotBetween()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " NOT BETWEEN " + fields1 + " AND " + fields2 + ";";

        return sql;
    }
    // билдеры для queryType _______________
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
        sql = "DELETE FROM " + this->tableName + "\n" + "WHERE " + strWhereDelete;

        return sql;
    }

    string buildUpdate()
    {

        sql = "UPDATE " + this->tableName + "\n" + "SET " + strSetUpdate + "\n" + "WHERE " + strWhereUpdate + ";";

        return sql;
    }

    string buildWhereAndOr()
    {
        string Where = "where ";

        if (Where != "where ")
        {
            for (int i = 0; i < this->vWhere.size(); i++)
            {
                Where += this->vWhere[i] + " and ";
            }
        }

        string andWhere = "";
        for (int i = 0; i < this->vAndWhere.size(); i++)
        {
            andWhere += this->vAndWhere[i] + " and ";
        }
     

        string OrWhere;
        for (int i = 0; i < this->vOrWhere.size(); i++)
        {
            OrWhere += this->vOrWhere[i] + " or ";
        }

        for (int i = 0; i < 4; i++)
        {
            OrWhere.pop_back();
        }
       

        if (andWhere == " and " || OrWhere == " or " )
        {

        for (int i = 0; i < 4; i++)
        {
            Where.pop_back();
        }

        for (int i = 0; i < 4; i++)
        {
            andWhere.pop_back();
        }
        }
        

        string resultBuildWhere;
        resultBuildWhere = Where + andWhere + OrWhere;
        return resultBuildWhere;
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

        sql = this->queryType + " " + fields + " FROM " + tableName + " " + buildWhereAndOr();

        return sql;
    }

    string buildInsert()
    {
        sql = "INSERT INTO " + this->tableName + " ( " + this->columnName + " ) " + " VALUES " + " ( " + this->fieldName + " )";

        return sql;
    }
    // дополнительный функционал

    void clear()
    {
        this->tableName.clear();
        this->queryType.clear();
        this->fieldName.clear();
        this->columnName.clear();
        this->resAddFields.clear();
        this->resWhere.clear();
        this->resWhereOr.clear();
        this->resWhereAnd.clear();
        this->sql.clear();
    }

    /////////////////////////////////

    // queryType queryType queryType queryType queryType queryType queryType

    querySQL *select()
    {
        this->queryType = "select";
        return this;
    }

    querySQL *insert()
    {
        this->queryType = "insert";
        return this;
    }

    querySQL *update()
    {
        this->queryType = "update";
        return this;
    }

    querySQL *remove() // remove = delete SQL
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

    querySQL *distinct()
    {
        this->queryType = "distinct";
        return this;
    }
    //------------------------------------
    // сбор информации

    querySQL *orWhere(string fieldName, string condition, string value)
    {
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

        this->resOrWhere = fieldName + " " + condition + " '" + value + "'";
        this->vOrWhere.push_back(resOrWhere);
        return this;
    }

    querySQL *andWhere(string fieldName, string condition, string value)
    {

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

        this->resWhereAnd = fieldName + " " + condition + " '" + value + "'";
        this->vAndWhere.push_back(resWhereAnd);
        return this;
    }

    querySQL *where(string fieldName, string condition, string value, string orAnd = " and ")
    {
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

        this->resOrWhere = fieldName + " " + condition + " '" + value + "'";
        this->vOrWhere.push_back(resOrWhere);
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

    querySQL *BetweenFields(string fields1, string fields2)
    {
        this->fields1 = fields1;
        this->fields2 = fields2;

        return this;
    }

    filterOperator *filterWhere(string fieldName, string condition, string value)
    {
        filterOperator *where = new filterOperator(fieldName, condition, value);

        return where;
    }

private:
    vector<filterOperator *> whereFilter;
    // исключения
    string conditionWhere[7] = {"=", "!=", "<>", ">", "<", "<=", ">="};

    // delete informatiom
    string strWhereDelete;

    //  update informatiom
    string strSetUpdate;
    string strWhereUpdate;

    // between informatiom
    string fields1;
    string fields2;

    // результаты сбора инф
    vector<string> vfields;
    vector<string> vWhere;
    vector<string> vAndWhere;
    vector<string> vOrWhere;
    string resOrWhere;
    string whereAnd;
    string tableName;
    string queryType;
    string fieldName;
    string columnName;
    string resWhere;
    string resWhereOr;
    string resWhereAnd;
    string resAddFields;

    // результаты билдеров
    string sql;
};