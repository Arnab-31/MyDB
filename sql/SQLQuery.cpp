#include "./include/SQLQuery.h"
#include "./include/Condition.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

void SQLQuery::setQueryType(const std::string &type) {
    queryType = type;
}

std::string SQLQuery::getQueryType() const {
    return queryType;
}

void SQLQuery::setTableName(const std::string &name) {
    tableName = name;
}

std::string SQLQuery::getTableName() const {
    return tableName;
}

void SQLQuery::addColumnDefinition(const std::string &colName, const std::string &colType) {
    columnDefinitions[colName] = colType;
}

const std::map<std::string, std::string>& SQLQuery::getColumnDefinitions() const {
    return columnDefinitions;
}

void SQLQuery::addInsertValue(const std::string &val) {
    insertValues.push_back(val);
}

const std::vector<std::string>& SQLQuery::getInsertValues() const {
    return insertValues;
}

void SQLQuery::addSelectValue(const std::string &val) {
    selectValues.push_back(val);
}

const std::vector<std::string>& SQLQuery::getSelectValues() const {
    return selectValues;
}

void SQLQuery::setWhereCondition(const Condition &cond) {
    whereCondition = cond;
}

const Condition& SQLQuery::getWhereCondition() const {
    return whereCondition;
}

void SQLQuery::addUpdateValue(const std::string &col, const std::string &val) {
    updateValues[col] = val;
}

const std::map<std::string, std::string>& SQLQuery::getUpdateValues() const {
    return updateValues;
}