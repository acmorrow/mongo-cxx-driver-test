mongo-cxx-driver-test
=====================

Temporary independent repo for tests of the legacy mongo-cxx-driver repo

This repo pulls down GTest and the independent mongo "legacy" driver and builds them
then builds and runs unit tests against the built driver.

Written in CMake for expediency due to awesome power of ExternalProject_add.

Instructions:

    git clone git@github.com:acmorrow/mongo-cxx-driver-test.git
    cd mongo-cxx-driver-test
    mkdir build
    cd build
    cmake ..
    make all test

