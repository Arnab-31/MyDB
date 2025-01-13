#include <fstream>
#include <iostream>
#include "./include/SQLQuery.h"
#include "./include/createTableCSV.h"

void createTableCSV(const SQLQuery &query) {
    std::string tableName = query.getTableName();
    std::string filePath = "data/" + tableName + ".csv";
    std::ifstream checkFile(filePath);
    if (checkFile.is_open()) {
        std::cout << "Error: Table '" << tableName << "' already exists." << std::endl;
        checkFile.close();
        return;
    }
    checkFile.close();
    const auto &cols = query.getColumnDefinitions();
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        bool first = true;
        for (auto &col : cols) {
            if (!first) outFile << ",";
            outFile << col.first;
            first = false;
        }
        outFile << std::endl;
        outFile.close();
    }
}