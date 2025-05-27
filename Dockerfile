# Fetch ubuntu image
FROM ubuntu:25.04

# Install prerequisites

RUN apt update && \
    apt install -y git python3 && \
    apt install -y binutils build-essential cmake libgtest-dev libsqlite3-0 libsqlite3-dev 

# For security adding a new user and directory
RUN useradd -ms /bin/bash csvUser

RUN mkdir /dockerCSV  


# Copy in our source files

COPY *.* /dockerCSV/project/
COPY ./test /dockerCSV/project/test
COPY ./data/ /dockerCSV/project/data
COPY ./src/convService /dockerCSV/project/src/convService
COPY ./src/dbService /dockerCSV/project/src/dbService
COPY ./src/main.cpp /dockerCSV/project/src/main.cpp
COPY ./include /dockerCSV/project/include

WORKDIR /dockerCSV/project/

RUN chown -R csvUser /dockerCSV && ls -l && sleep 10

USER csvUser

# Build project
RUN \
    mkdir -p /dockerCSV/project/build && \
    cd /dockerCSV/project/build && \
    cmake .. && \
    make

# Command that will be invoked when the container starts
ENTRYPOINT ["/bin/bash"]