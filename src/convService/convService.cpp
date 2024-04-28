#include <convService.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>


/**
 * @brief constructor of the class
 * 
 * @param dbName Name of the database
 * @param infoFile Path to the file that contains information of type of each colum
 * @param tabNameP Table Name
 * @param dataFileP Path to the csv file that contains the information 
 */

convService::convService(std::string dbName,std::string infoFile, std::string tableNameP, std::string dataFileP){
    
    this->outputFile=dbName;
    this->tableName=tableNameP;
    this->confFile=infoFile;
    this->dataFile=dataFileP;

    this->database = new databaseService(dbName);
    this->database->openDB();
    this->generateTable();
};

/**
/// @brief Check correctnes in the columns type specifications
/// @return true is they are correct, false if there is a problem
*/
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


/**
* @brief imports from the columns type file the types and stores them in a vector
* @return false if there was a problem 
*/
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
/**
* @brief after check that all the information needed is present, generates the table and populate it with the data
* @return false if there was a problem when inserting or generating the table 
*/
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
    unsigned int i=0;
    unsigned int j=0;
    if(!infoFile.is_open()){
        std::cout<<"Failed to open column Names file\n";
        return false;
    }
    else{
        
        std::string progression=".";
        std::string sqlLocal;
        std::getline(infoFile,line);                    
        while(getline(infoFile,line)){  
            std::stringstream s{line};
            std::string local;
            std::vector<std::string> vLocal;
            sqlLocal+="(";
            while(getline(s,local,',')){
                vLocal.push_back("'"+local+"'");
            }
            for(unsigned int i=0;i<vLocal.size()-1;i++){
                sqlLocal+=vLocal[i]+",";
            }
            sqlLocal+=vLocal[vLocal.size()-1];   
            sqlLocal+="),";         
            i++;
            if(i==500)
                {
                    sqlLocal.at(sqlLocal.size()-1)=' '; 
                    this->database->insertChunkElementTable(sqlLocal,tableNameLocal);
                    sqlLocal="";
                    i=0;
                    j++;
                    std::cout<<progression<<"\n";
                    progression+=".";
                    };                    
        }
        
        sqlLocal.at(sqlLocal.size()-1)=' ';
        this->database->insertChunkElementTable(sqlLocal,tableNameLocal);
        std::cout<<"\ninserted:"<<j*500+i<<" registers\n";
    }    
    infoFile.close();
    return true;
}



convService::~convService(){
    delete this->database;
   
}
