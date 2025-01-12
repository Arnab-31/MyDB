
#include "include/Condition.h"

Condition::Condition() = default;

Condition::Condition(const std::string& col, const std::string& op, const std::string& val)
    : columnName(col), conditionOperator(op), value(val) {}

void Condition::setColumnName(const std::string& col) {
    columnName = col;
}

void Condition::setConditionOperator(const std::string& op) {
    conditionOperator = op;
}  

void Condition::setValue(const std::string& val) {
    value = val;
}

const std::string& Condition::getColumnName() const {
    return columnName;
}

const std::string& Condition::getConditionOperator() const {
    return conditionOperator;
}

const std::string& Condition::getValue() const {
    return value;
}