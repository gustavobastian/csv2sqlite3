#include <convService.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

convService::convService(std::string dbName,std::string infoFile, std::string tableNameP, std::string dataFileP){
    
    this->outputFile=dbName;
    this->tableName=tableNameP;
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
    
    infoFile.close();
    return true;
}

bool convService::generateTable(){
    
    if (this->checkColumnsTypes()==false){
        return false;
    }
        
    
    if(this->checkColumnsNames()==false){
        return false;
    }
        
    //creating tables
    std::vector<std::string> sentenceVector;

    std::string localString;
    for (int i=0;i<this->vectorConf.size()-1;i++){
        localString+=vectorNames[i]+" "+vectorConf[i]+",";
    }
       localString+=vectorNames[vectorNames.size()-1]+" "+vectorConf[vectorConf.size()-1];
    
    std::cout<<"localstring: "<<localString<<"\n";

    sentenceVector.push_back(localString);

    
    
    if(this->database->createTable(this->tableName,sentenceVector)==-1){
        return false;
    };

    //inserting elements
    std::string tableNameLocal{this->tableName};
    tableNameLocal+=" (";
    for (auto i=0;i<this->vectorNames.size()-1;i++ ){
        tableNameLocal+= vectorNames[i] +",";
    }
    tableNameLocal+=vectorNames[vectorNames.size()-1]+")";
    
    std::fstream infoFile{this->dataFile,infoFile.in};
    std::string line;
    if(!infoFile.is_open()){
        std::cout<<"Failed to open column Names file\n";
        return false;
    }
    else{
        unsigned int i=0;
        std::getline(infoFile,line);                    
        while(getline(infoFile,line)){  
            std::stringstream s{line};
            std::string local;
            std::vector<std::string> vLocal;
            std::string sqlLocal;
            
            
            while(getline(s,local,',')){
                vLocal.push_back("'"+local+"'");
            }
            for(unsigned int i=0;i<vLocal.size()-1;i++){
                sqlLocal+=vLocal[i]+",";
            }
            sqlLocal+=vLocal[vLocal.size()-1];            
            this->database->insertElementTable(sqlLocal,tableNameLocal);
        }
    }
    
    infoFile.close();
    return true;
}



convService::~convService(){
    delete this->database;
   
}
