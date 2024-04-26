#ifndef CONVSERV
#define CONVSERV
#include <string>
#include <databaseService.h>
#include<string>
#include<vector>


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
