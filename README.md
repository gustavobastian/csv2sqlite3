# csv-sqlite Importer

Console app for importing data from table from a csv file to a sqlite3 database

## System requirements  for building

You must install a decompressed version of googletest 1.21.1 in a /lib folder.

<img alt="img" style="width:150px;" src="img/img.png">

## System requirements  for running

The system must have installed sqlite3, in Linux Systems:

```bash
sudo apt-get install sqlite3 sqlite3_analyzer 
```

## Documentation

In order to build the documentation, you must have installed doxygen

```bash
sudo apt-get install doxygen
sudo apt-get install graphviz
```

## Building

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Example of use

```bash
csv2sqlite3 -f data.csv -i data.txt -o databaseName -t tableName
```

## Result

Tested importing 72274 registers (about 3.7 MB). 
