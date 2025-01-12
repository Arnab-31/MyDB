#pragma once
#include <string>
#include <map>
#include <vector>
#include "Condition.h"

class SQLQuery {
    std::string queryType;
    std::string tableName;
    std::map<std::string, std::string> columnDefinitions;
    std::vector<std::string> insertValues;
    std::vector<std::string> selectValues;
    Condition whereCondition;

public:
    void setQueryType(const std::string &type);
    std::string getQueryType() const;

    void setTableName(const std::string &name);
    std::string getTableName() const;

    void addColumnDefinition(const std::string &colName, const std::string &colType);
    const std::map<std::string, std::string>& getColumnDefinitions() const;

    void addInsertValue(const std::string &val);
    const std::vector<std::string>& getInsertValues() const;

    void addSelectValue(const std::string &val);
    const std::vector<std::string>& getSelectValues() const;

    void setWhereCondition(const Condition &cond);
    const Condition& getWhereCondition() const;
};