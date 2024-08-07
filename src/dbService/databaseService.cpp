#include <databaseService.h>
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

/**
 * @brief Construct a new database Service::database Service object
 * 
 * @param addressP string place and name of the database(ex "/opt/file.db")
 */
databaseService::databaseService(std::string addressP){
    this->address=addressP;    
    return;
}


/**
 * @brief This function open the database
 * 
 * @return int 0 if ok, -1 if error
 */
int databaseService::openDB(){
    this->rc = sqlite3_open((this->address).c_str(), &(this->db));    
    if (this->rc) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    else
    {
       // std::cout<<"database open"<<std::endl;
        return 0;
    }

}
/**
 * @brief create a simple table with id(int primary), name(string) and age(int)
 * 
 * @param tableName 
 * @return int -1: error, 0: success
 */
int databaseService::createTable(std::string tableName){
    if(tableName.size()==0) {
         std::cerr  << "Error creating table: no table name" << std::endl;
        return -1;
    }
      // create a table
    std::string sql = "CREATE TABLE IF NOT EXISTS "+ tableName +" (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
    rc = sqlite3_exec(db, sql.c_str()  , NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout  << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    return 0;
};

/**
 * @brief create a Table in the database
 * 
 * @param tableName name of the table
 * @param columns vector of string with columns names and characteristics 
 * Example:id INTEGER PRIMARY KEY,firstname TEXT
 * look at sqlite3 documentation for more characteristics.
 * @return int -1:error, 0:success
 */
int databaseService::createTable(std::string tableName, std::vector<std::string> columns){
    
    if((columns.size()==0)||(tableName.size()==0)) {
         std::cout  << "Error creating table: no columns o no table name" << std::endl;
        return -1;
    }

    // create a table with columns
    std::string sql2= " (";
    for (std::string column : columns){        
        sql2+= column +", ";
    }
    sql2.at(sql2.size()-2)=0x20;
    sql2+=");";
    
    std::string sql = "CREATE TABLE IF NOT EXISTS "+ tableName +sql2;//" (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
    rc = sqlite3_exec(db, sql.c_str()  , NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout  << "Error creating table: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    return 0;
};

/**
 * @brief Drop a table from the database
 * 
 * @param tableName name of the table
 * @return int -1: error, 0: success
 */

int databaseService::dropTable(std::string tableName){
    if((tableName.size()==0)) {
         std::cout  << "Error dropping table: no table name" << std::endl;
        return -1;
    }
      // create a table
    std::string sql = "drop TABLE "+ tableName ;
    rc = sqlite3_exec(db, sql.c_str()  , NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout  << "Error deleting table: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    return 0;
};

/**
 * @brief Inserting a row to a database table
 * 
 * @param Element string with values to insert into the table
 * @param tableName name of the table
 * @return int 0:success, -1:error
 */
int databaseService::insertElementTable(std::string Element,std::string tableName){
    
    std::string sql = "INSERT INTO " +tableName+" VALUES("+ Element +");";
    
    this->rc = sqlite3_exec(this->db, sql.c_str(), NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    return 0;
};

/**
 * @brief Inserting a multiple rows to a database table
 * 
 * @param Element string with values to insert into the table, example: (value1,value2,value3),(value12,value22,value32)
 * @param tableName name of the table and the columns, example: tablename (column1, column2, colum3)
 * @return int 0:success, -1:error
 */
int databaseService::insertChunkElementTable(std::string Element,std::string tableName){
    
    std::string sql = "INSERT INTO " +tableName+" VALUES "+ Element +";";
    
    this->rc = sqlite3_exec(this->db, sql.c_str(), NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    return 0;
};
/**
 * @brief updating a row to a database table
 * 
 * @param Element string with new values to insert into the table
 * @param tableName name of the table
 * @param index index of the row
 * @return int 0:success, -1:error
 */
int databaseService::updateElementTable(std::string Element,std::string tableName,int index){
    std::stringstream ss;
    ss<<index;
    std::string indexS;
    indexS=ss.str();
    
    std::string sql = "UPDATE " +tableName+" SET "+ Element +"WHERE id="+indexS+";";
    this->rc = sqlite3_exec(this->db, sql.c_str(), NULL, 0, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error updating table: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    return 0;
};


/**
 * @brief find elements by tag
 * 
 * @param tableName name of table
 * @param elementTag name of column
 * @param elementValue value of column
 * @return std::string with information of the row found
 */

std::string databaseService::findElement(std::string tableName, std::string elementTag, std::string elementValue){

    std::stringstream ss;    
    std::string output;
    
    std::string sql = "SELECT *  FROM "+tableName+" WHERE "+elementTag+" = "+ elementValue+";";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error querying table: " << sqlite3_errmsg(db) << std::endl;
        return "Error querying table: ";
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {

        for(unsigned int i=0;i<sqlite3_data_count(stmt);i++)
        {        
            ss<<  reinterpret_cast<const char *>(sqlite3_column_text(stmt, i))<< ",";
        }    
        ss<<(";");
        
    }
    output=ss.str();
   // output.at(output.size()-2)=0x20;
    sqlite3_finalize(stmt);
    
    return output;
};
/**
 * @brief returns all elements from a table
 * 
 * @param tableName Table name
 * @param limit maximum number of rows to return
 * @return std::string : string with table rows separated by ";" and columns by "," => value1,value2, ...; value11,value22,...; 
 */
std::string databaseService::getAllElement(std::string tableName, unsigned int limit){    

    if(tableName.size()==0){return "error";}
    if(limit ==0){return "error";}
    std::stringstream ss;
    ss<<limit;
    std::string limitS=ss.str();
    std::string output;
    ss.str("");
    std::string sql = "SELECT * FROM "+ tableName +" LIMIT " +limitS+";";    
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error querying table: " << sqlite3_errmsg(db) << std::endl;        
        return "Error querying table: ";
    }

    rc = sqlite3_step(stmt);

    while (rc == SQLITE_ROW) {

        for(unsigned int i=0;i<sqlite3_data_count(stmt);i++)
        {        
            ss<<  reinterpret_cast<const char *>(sqlite3_column_text(stmt, i))<< ",";
        }    
        ss<<(";");
        output+=ss.str();
        ss.str("");
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    
    return output;
};



long databaseService::getLastIndex(std::string tableName){
    long output;
    std::stringstream ss;
    if(tableName.size()==0){return 0;}
    std::string sql = "SELECT id FROM "+ tableName +" ORDER BY id DESC LIMIT 1;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        std::cout << "Error querying table: " << sqlite3_errmsg(db) << std::endl;        
        return 0;
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {

           
         ss<<  reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        
    }
    
    std::string data=ss.str();
    output=stoi(data);
   
    sqlite3_finalize(stmt);
    
    return output;
}

 /**
  * @brief Destroy the database Service::database Service object
  * 
  */
databaseService::~databaseService(){
    sqlite3_close(this->db);   
}
    