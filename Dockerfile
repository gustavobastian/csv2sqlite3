# Fetch ubuntu image
FROM ubuntu:25.04

# Install prerequisites

RUN \
    apt update && \
    apt install -y git python3 && \
    apt install -y binutils build-essential cmake libgtest-dev libsqlite3-0 libsqlite3-dev 

# Copy in our source files
COPY *.* /project/
COPY ./data/ /project/data
COPY ./src/convService /project/src/convService
COPY ./src/dbService /project/src/dbService
COPY ./src/main.cpp /project/src/main.cpp
COPY ./test /project/test
COPY ./include /project/include

# Build project
RUN \
    mkdir -p /project/build && \
    cd /project/build && \
    cmake .. && \
    make

# Command that will be invoked when the container starts
ENTRYPOINT ["/bin/bash"]