
#pragma once
#include <string>
#include <map>
#include <vector>

class SQLQuery {
    std::string queryType;
    std::string tableName;
    std::map<std::string, std::string> columnDefinitions;
    std::vector<std::string> insertValues;

public:
    void setQueryType(const std::string &type);
    std::string getQueryType() const;

    void setTableName(const std::string &name);
    std::string getTableName() const;

    void addColumnDefinition(const std::string &colName, const std::string &colType);
    const std::map<std::string, std::string>& getColumnDefinitions() const;

    void addInsertValue(const std::string &val);
    const std::vector<std::string>& getInsertValues() const;
};