# csv-sqlite Importer 
Platforms: [![Ubuntu](https://github.com/gustavobastian/csv2sqlite3/actions/workflows/linux.yml/badge.svg)](https://github.com/gustavobastian/csv2sqlite3/actions/workflows/linux.yml)

Testing coverage: [![codecov](https://codecov.io/github/gustavobastian/csv2sqlite3/graph/badge.svg?token=LOXWSTKRJE)](https://codecov.io/github/gustavobastian/csv2sqlite3)

## Description

Simple console utility for importing data from table in a csv file to a sqlite3 database. It was tested in a Ubuntu 24.04 (dev Branch).

## Directory tree description

* /data : has some example files for using during tests.
* /cmake : has information for packaging the project.
* /docs : has information for generating the documentation with doxygen.
* /img: place for saving images(not used)
* /include: header files.
* /src : source files.
* /test : test files.

## Purpose 🤔

The objetive of this small project is import information from csvs files(from online sites, like [www.kaggle.com](www.kaggle.com)) to small databases in order to process or apply some machine learning algorithms to them.

## System requirements  for building 📝

This app is needs Cmake 3.15. For running the test files you must navigate to ./build/test, and the inside the directory run the programs.

## System requirements  for running 📝

The system must have installed sqlite3, in Linux Systems:

```bash
sudo apt-get install libsqlite3-0 sqlite3_analyzer 
```

## Documentation 📚

In order to build the documentation, you must have installed doxygen

```bash
sudo apt-get install doxygen
sudo apt-get install graphviz
```

## Building 🛠️

There are 2 ways for building the application.

* Local build:

```bash
mkdir build
cd build
cmake ..
cmake --build .
cpack -G DEB
```

The generated packages are stored in "./_packages".

* Using Docker container (you must have installed docker):

```bash
docker build -t csv2sqlite3-image .
docker create -i -t  --entrypoint="/bin/bash" --name cvs-container csv2sqlite3-image
```

Then, start the container:

```bash
docker start -i cvs-container
```

Exit and delete the container and the image:

```bash
exit
docker container rm cvs-container
docker rmi csv2sqlite3-image
```




## Example of use 💡

```bash
csv2sqlite3 -f data.csv -i data.txt -o databaseName -t tableName
```

Where 'data.csv' is the file with the data, 'data.txt' contains information of data type in each column, 'databaseName' is the name of the database, it will create a new one or update a previous. And 'tableName' is the name of the table.

<details summary>Example of the content of a 'data.txt' file🔍</summary>

```bash
INT,TEXT,TEXT,INT
```

</details>

## Result ⚙️

Tested importing 72274 registers (about 3.7 MB).

## Licence 📄

This project is under ([MIT](https://choosealicense.com/licenses/mit/)) license. You can read the file [LICENSE.md](LICENSE.md) in order to learn how to use the material.

## Special thanks and links recommendations

The CPACK management is very well explained in [https://decovar.dev/blog/2021/09/23/cmake-cpack-package-deb-apt/](https://decovar.dev/blog/2021/09/23/cmake-cpack-package-deb-apt/) (big thanks to retifrav).\
Another place to look at is CPACK itself [https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html)
