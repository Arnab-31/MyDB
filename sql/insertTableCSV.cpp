
#include <fstream>
#include <iostream>
#include "./include/SQLQuery.h"
#include "./include/insertTableCSV.h"

void insertIntoTableCSV(const SQLQuery &query) {
    std::string tableName = query.getTableName();
    std::string filePath = "data/" + tableName + ".csv";
    std::ifstream checkFile(filePath);
    if (!checkFile.is_open()) {
        std::cout << "Error: Table '" << tableName << "' does not exist." << std::endl;
        return;
    }
    checkFile.close();

    std::ofstream outFile(filePath, std::ios::app);
    if (!outFile.is_open()) {
        std::cout << "Error: Cannot open table file '" << tableName << "'." << std::endl;
        return;
    }

    const auto &values = query.getInsertValues();
    bool first = true;
    for (const auto &val : values) {
        if (!first) outFile << ",";
        outFile << val;
        first = false;
    }
    outFile << std::endl;
    outFile.close();
}