#include <iostream>
#include <string>
#include <vector>
#include <map>


enum class MyArgs{
    o,
    t,
    f,
    i
};

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


void printUsage(){
    std::cout << "Incorrect usage or bad parameters!\n";
    std::cout << "csv2sqlite3 -f [datafile.csv] -i [datacolumnstype.txt] -o [outputdb] -t [tablename]\n";
}

void printManual(){
    std::cout << "csv2sqlite3 csv to sqlite3 table conversor\n";    
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

int main(int argc, char* argv[]){
    std::string arg1{argv[1]};
    std::vector<std::string> argumentsVector;
    std::string dataFile;
    std::string dataConfigFile;
    std::string tableName;
    std::string dbName;

    if(argv[1]=="--m"){
        printManual();
        return 0;
    }
    
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

    int i=1;

    while (i<argc){     
        argumentsVector.push_back(std::string(argv[i]));
        i++;
    }
    for (unsigned int i=0;i<argumentsVector.size()-1;i++){
        MyArgs value= stringToMyArgs(argumentsVector[i]);
        switch (value){
            case MyArgs::t :                
                tableName=argumentsVector.at(i+1);
                i++;
                break;
            case MyArgs::o :                
                dbName=argumentsVector.at(i+1);
                i++;
                break;
            case MyArgs::f :                
                dataFile=argumentsVector.at(i+1);
                i++;
                break;
            case MyArgs::i :                
                dataConfigFile = argumentsVector.at(i+1);
                i++;
                break;
            default:
                i++;
                break;      
        }
    }
    
}
