FROM ubuntu:18.04

RUN apt update

RUN apt -y install apt-utils

RUN apt -y install gcc g++ cmake libboost-dev libboost-system-dev libboost-filesystem-dev

RUN gcc --version

RUN g++ --version

RUN mkdir /tmp/build/ && cd /tmp/build/ && cmake -DENABLE_TESTS=ON /mnt/AppFramework/code/ && make -j3 && ./Core/sample/sample_sinewaverunner ./plugin/
