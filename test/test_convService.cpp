#include <gtest/gtest.h>
#include <databaseService.h>
#include <convService.h>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

TEST(CREATING_SERVICE, PASSING_PARAMETERS){
   auto myService = new convService("databaseTest1.db","here2","here3","here4");
   auto output= myService->checkColumnsTypes();
   EXPECT_EQ(output,false);
   delete myService;
   system("rm ./databaseTest1.db");
}

TEST(CREATING_SERVICE, PASSING_COL_PARAMETERS){
   std::fstream dataConf{"dataConf.txt",dataConf.out};
   if(!dataConf.is_open()){
        std::cout<<"Fail to generate  configuration file\n";        
    }
    else{
        dataConf<<"INTEGER,VARCHAR,DECIMAL,BLOB\n";
    }

   dataConf.close();
   auto myService = new convService("databaseTest1.db","dataConf.txt","here3","here4");

   auto output= myService->checkColumnsTypes();
   EXPECT_EQ(output,true);

   delete myService;
   system("rm ./databaseTest1.db");
   system("rm ./dataConf.txt");
 }

 TEST(CREATING_SERVICE, PASSING_FALSE_COL_PARAMETERS){
   std::fstream dataConf{"dataConf.txt",dataConf.out};
   if(!dataConf.is_open()){
        std::cout<<"Fail to generate  configuration file\n";        
    }
    else{
        dataConf<<"INTEGER,SALT,DECIMAL,BLOB\n";
    }

   dataConf.close();
   auto myService = new convService("databaseTest1.db","dataConf.txt","here3","here4");

   auto output= myService->checkColumnsTypes();
   EXPECT_EQ(output,false);

   delete myService;
   system("rm ./databaseTest1.db");
   system("rm ./dataConf.txt");
 }

 TEST(CREATING_SERVICE, PASSING_COL_NAMES){
   //using example data in {project}/data
   auto myService = new convService("databaseTest1.db","../../data/info.txt","Datos","../../data/data.csv");

   auto output= myService->checkColumnsNames();
   EXPECT_EQ(output,true);
   delete myService;
   system("rm ./databaseTest1.db");
 
 }
TEST(CREATING_SERVICE, INSERTING_DATA){
   auto myService = new convService("databaseTest1.db","../../data/info.txt","Datos","../../data/data.csv");
   myService->generateTable();
   delete myService;
   system("rm ./databaseTest1.db");
 
 }


int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}