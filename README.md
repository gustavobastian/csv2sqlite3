# Console app for importing data from table from a csv file to a sqlite3 database

## System requirements  for building

You must install a decompressed version of googletest 1.21.1 in a /lib folder.

<img alt="img" style="width:150px;" src="img/img.png">

## System requirements  for running

The system must have installed sqlite3, in Linux Systems:

```bash
sudo apt-get install sqlite3 sqlite3_analyzer 
```

## Example of use

```bash
csv2sqlite3 data.csv data.txt -o databaseName
```
