#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <convService.h>
#include <databaseService.h>
#include <thread>
#include <memory>
#include <string.h>


enum class MyArgs{
    o,
    t,
    f,
    i
};

/**
* @brief return the kind of argument present, output database file(-o), path to file containing type of each column (-i),
* table name(-t), path to input data csv file(-f)  
* @param str string with the specification
* @return object type myArgs
*/
MyArgs stringToMyArgs(const std::string& str){
    if(str=="-o"){
        return MyArgs::o;
    }
    if(str=="-i"){
        return MyArgs::i;
    }
    if(str=="-f"){
        return MyArgs::f;
    }
    if(str=="-t"){
        return MyArgs::t;
    }
        return MyArgs::t;
}

/**
 * @brief prints to console the correct way of usage of the program
 * 
 */
void printUsage(){
    std::cout << "Incorrect usage or bad parameters!\n";
    std::cout << "csv2sqlite3 -f [datafile.csv] -i [datacolumnstype.txt] -o [outputdb] -t [tablename]\n";
}
/**
 * @brief prints information about the program and how to correct use it
 * 
 */
void printManual(){
    std::cout << "csv2sqlite3 csv to sqlite3 table conversor\n";    
    std::cout << "V0.1.1\n";    
    std::cout << "by Gustavo Bastian(2024)\n";    
    std::cout << "bastian.gustavo@gmail.com\n";    
    std::cout << "\n";    
    std::cout << "This is a simple program that imports data from a csv file to a sqlite3 database.\n";    
    std::cout << "\n";    
    std::cout << "You must have installed sqlite3 in your linux distribution: \n";
    std::cout << "\n";    
    std::cout << "ubuntu: sudo apt-get install sqlite3 sqlitebrowser sqlite3-analyzer \n";
    std::cout << "\n";    
    std::cout << "The command sintaxis is:\n";    
    
    std::cout << "csv2sqlite3 -f [datafile.csv] -i [datacolumnstype.txt] -o [outputdb] -t [tablename]\n";
    std::cout << "\n";    
    std::cout << "datafile.csv: file with the information (comma delimited and first row column names).\n";    
    std::cout << "\n";    
    std::cout << "datacolumnstype.txt: file with the information of the type of data in the columns.\n";    
    std::cout << "\n";    
    std::cout << "outputdb: name of the output db(if it doesnt exist it will be created).\n";    
    std::cout << "\n";    
    std::cout << "tablename: the name of the table.\n";    
    std::cout << "\n";    
    std::cout << "For help: csv2sqlite3 --h\n";    
    std::cout << "For this manual: csv2sqlite3 --m\n";    
    std::cout << "\n";    
}

/**
 * @brief main funcion
 * 
 * @param argc number of arguments
 * @param argv list of arguments
 * @return int 
 */
int main(int argc, char* argv[]){
    
    if(argc==0 ||  argc<2){
        printManual();
        return 0;
    }
    if(strcmp(argv[1],"--m")){
        printManual();
        return 0;
    }


    std::string arg1{argv[1]};
    std::vector<std::string> argumentsVector;
    std::string dataFile;
    std::string dataConfigFile;
    std::string tableName;
    std::string dbName;

    
    
    if(arg1=="--h"){
        printManual();
        return 0;
    }

    if(arg1=="--m"){
        printManual();
        return 0;
        }

    if(argc>1 && argc<8){
        printUsage();
        return 0;
    }

    int index_arguments=1;

    while (index_arguments<argc){     
        argumentsVector.push_back(std::string(argv[index_arguments]));
        index_arguments++;
    }
    for (unsigned int index_vector_arguments=0;index_vector_arguments<argumentsVector.size()-1;index_vector_arguments++){
        MyArgs value= stringToMyArgs(argumentsVector[index_vector_arguments]);
        switch (value){
            case MyArgs::t :                
                tableName=argumentsVector.at(index_vector_arguments+1);
                index_vector_arguments++;
                break;
            case MyArgs::o :                
                dbName=argumentsVector.at(index_vector_arguments+1);
                index_vector_arguments++;
                break;
            case MyArgs::f :                
                dataFile=argumentsVector.at(index_vector_arguments+1);
                index_vector_arguments++;
                break;
            case MyArgs::i :                
                dataConfigFile = argumentsVector.at(index_vector_arguments+1);
                index_vector_arguments++;
                break;
            default:
                index_vector_arguments++;
                break;      
        }
    }
    auto myService = std::make_shared<convService>(dbName,dataConfigFile,tableName,dataFile);//new convService(dbName,dataConfigFile,tableName,dataFile);

}

