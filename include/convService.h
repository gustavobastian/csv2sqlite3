#ifndef CONVSERV
#define CONVSERV
#include <string>
#include <databaseService.h>
#include<string>
#include<vector>


/**
 * @file convService.h
 * @author Gustavo Bastian (bastian.gustavo@gmail.com)
 * @brief Interface class that insert csv file data to a sqlite3 database
 * @version 0.1
 * @date 2024-4-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */

/**
 * @brief class used to import csv data to sqlite3 table
 * 
 */
class convService
{
    private:    
    databaseService* database;
    std::string outputFile;
    std::string tableName;
    std::string confFile;
    std::string dataFile;
    std::vector<std::string> vectorColumns;
    std::vector<std::string> vectorConf;
    std::vector<std::string> vectorNames;
        
    public:
        convService(std::string dbName,std::string infoFile, std::string tableName, std::string dataFile);
        bool generateTable();
        bool flushingData();
        bool checkColumnsTypes();
        bool checkColumnsNames();

        ~convService();
};


#endif //CONVSERV
