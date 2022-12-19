class querySQL
{
public:
    // ОСНОВНОЙ БИЛДЕР
    string SQL()
    {
        // обработка всех запросов
        //queryType
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
            //operatorType
        else if(this->operatorType == "IN")
            return this->buildOperatorIN();
        else if(this->operatorType == "NOT IN")
            return this->buildOperatorNOTIN();
        else if(this->operatorType == "BETWEEN")
            return this->buildOperatorBetween();
        else if(this->operatorType == "NOT BETWEEN")
            return this->buildOperatorNotBetween();
        else if(this->operatorType == "LIKE")
            return this->buildOperatorLIKE();
        else if(this->operatorType == "GLOB")
            return this->buildOperatorGLOB();


        return "error";
    }
    // билдеры для operatorType ___________
    string buildOperatorGLOB()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " GLOB "  + this->fieldName + ";";

        return sql;
    }



    string buildOperatorLIKE()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " LIKE "  + this->fieldName + ";";

        return sql;
    }


    string buildOperatorIN()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " IN " + " ( " + this->fieldName + " ) " + ";";

        return sql;
    }

       string buildOperatorNOTIN()
    {
        sql = "SELECT * FROM "+ this->tableName + "\n" + "WHERE " + this->columnName + " NOT IN " + " ( " + this->fieldName + " ) " + ";";

        return sql;
    }

    string buildOperatorBetween()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " BETWEEN " + fields1 + " AND " + fields2 +  ";";

        return sql;
    }

    string buildOperatorNotBetween()
    {
        sql = "SELECT * FROM " + this->tableName + "\n" + "WHERE " + this->columnName + " NOT BETWEEN " + fields1 + " AND " + fields2 +  ";";

        return sql;
    }
    // билдеры для queryType _______________
    string buildDistinct()
    {
        // выборка уникальных значений из колонки!
        sql = "SELECT DISTINCT " + columnName + " FROM " + this->tableName  + ";";

        return sql;
    }

    string buildReplace()
    {
        sql = "INSERT OR REPLACE INTO " + this->tableName + " ( " + columnName + " ) " + "\n" + "VALUES " + " ( " + fieldName + " ) ";

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
        sql = this->queryType + " " + fields + " FROM " + tableName + " " + resWhere + " " + resWhereAnd + " " + resWhereOr;

        return sql;
    }

    string buildInsert()
    {
        sql = "INSERT INTO " + this->tableName + " ( " + columnName + " ) " + " VALUES " + " ( " + fieldName + " )";

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
    //filter operators
    querySQL *operatorIN()
    {
        this->operatorType = "IN";

        return this;
    }

    querySQL *operatorNOTIN()
    {
        this->operatorType = "NOT IN";

        return this;
    }

    querySQL *operatorBetween()
    {
        this->operatorType = "BETWEEN";

        return this;
    }

    querySQL *operatorNotBetween()
    {
        this->operatorType = "NOT BETWEEN";

        return this;
    }

    querySQL *operatorLIKE()
    {
        this->operatorType = "LIKE";

        return this;
    }

    querySQL *operatorGLOB()
    {
        this->operatorType = "GLOB";

        return this;
    }
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

    querySQL *BetweenFields(string fields1, string fields2)
    {
        this->fields1 = fields1;
        this->fields2 = fields2;

        return this;
    }

private:
    // исключения
    string conditionWhere[7] = {"=", "!=", "<>", ">", "<", "<=", ">="};

    // delete informatiom
    string strWhereDelete;

    //  update informatiom
    string strSetUpdate;
    string strWhereUpdate;

    //between informatiom
    string fields1;
    string fields2;

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
    string sql;
    string operatorType;
};