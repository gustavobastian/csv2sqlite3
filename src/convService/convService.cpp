#include <convService.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

convService::convService(std::string dbName,std::string infoFile, std::string tableNameP, std::string dataFileP){
    std::cout<<"databaseName:"<<dbName<<"\n";

    this->outputFile=dbName;
    this->tableName=tableName;
    this->confFile=infoFile;
    this->dataFile=dataFileP;

    this->database = new databaseService(dbName);
    this->database->openDB();
    this->generateTable();
};


bool convService::checkColumnsTypes(){
    //columns types
    std::string lineConf,localConf;
    
    const std::vector<std::string> validConf{"NUMERIC",
    "DECIMAL","SMALLINT","INT","INTEGER","BIGINT","FLOAT",
    "REAL","DOUBLE PRECISION","BLOB","VARCHAR","TEXT","CLOB","DATE",
    "TIME","TIMESTAMP","BOOLEAN","INTERVAL"};

    std::fstream columnF{this->confFile,columnF.in};
    
    if(!columnF.is_open()){
        std::cout<<"Failed to open column configuration file.\n";
        columnF.close();
        return false;
    }
    else{
        std::getline(columnF,lineConf);        
        std::stringstream s(lineConf);
        while(getline(s,localConf,',')){
            std::transform(localConf.begin(),localConf.end(),localConf.begin(),toupper);
            this->vectorConf.push_back(localConf);
        }
    }
    //check
    for(auto i : vectorConf){
        if(std::find(validConf.begin(),validConf.end(),i)==std::end(validConf)){
            std::cout<<"Unrecongnized column type:"<<i<< " \n";
            columnF.close();
            return false;
        }
    }
    std::cout<<"Columns type checked.  \n";

    columnF.close();
    return true;

}
bool convService::checkColumnsNames(){
    std::string lineNames,localName;
    std::vector<std::string> vectorNames;
    
    //columns names
    std::fstream infoFile{this->dataFile,infoFile.in};
    
    if(!infoFile.is_open()){
        std::cout<<"Failed to open column Names file\n";
        return false;
    }
    else{
        std::getline(infoFile,lineNames);
    
        std::stringstream s2(lineNames);
        while(getline(s2,localName,',')){
            std::transform(localName.begin(),localName.end(),localName.begin(),toupper);
            this->vectorNames.push_back(localName);
        }
    }
    for(auto i:this->vectorNames)
        std::cout<<i<<"|";
    
    std::cout<<"\n";
    infoFile.close();
    return true;
}

bool convService::generateTable(){
    this->checkColumnsTypes();
    this->checkColumnsNames();
    return true;
}

convService::~convService(){
    delete this->database;
    std::cout<<"erasing pointer"<<std::endl;
}
