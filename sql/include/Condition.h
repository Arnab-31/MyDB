#pragma once
#include <string>

class Condition {
    std::string columnName;
    std::string conditionOperator;
    std::string value;

public:
    Condition();
    Condition(const std::string& col, const std::string& op, const std::string& val);

    void setColumnName(const std::string& col);
    void setConditionOperator(const std::string& op);
    void setValue(const std::string& val);

    const std::string& getColumnName() const;
    const std::string& getConditionOperator() const;
    const std::string& getValue() const;
};