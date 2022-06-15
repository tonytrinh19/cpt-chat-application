A concurrent chat server program that implements a custom application layer protocol.

Details:

Implements an original application layer chat protocol called CPT

CPT protocol and full API documentation can be found in the CPT-documentation/ folder at the project root

Application must be run on POSIX compliant machines. To run, build to folder called "cmake-build-debug", then use (example):

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Pre Setup](#pre-setup)
- [Setup](#setup)
- [Source Code Additions](#source-code-additions)
- [Build](#build)

## Pre Setup

This program will run using DC libraries. DC libraries provide error handling, and error reporting for your POSIX application.

So clone this repository -> [dc_scripts](https://github.com/bcitcstdatacomm/dc_scripts). After that, `cd` into dc_scripts folder and run
`./dc-update work gcc g++` This will install all dc libraries in your folder called work. If you'd like to update your libraries, simply go to dc_scripts folder and run `./dc-update work` to update the libraries.

## Setup
```
mkdir cmake-build-debug
```

## Source Code Additions
Add your source files to the CMakeLists.txt:

```
set(HEADER_LIST [files])
set(SOURCE_LIST [files])
```

```
cmake -DCMAKE_C_COMPILER="gcc" -DCMAKE_CXX_COMPILER="g++" -S . -B cmake-build-debug
```
or:

```
cmake -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -S . -B cmake-build-debug
```

## Build 
Examples:
```
cmake --build cmake-build-debug
cmake --build cmake-build-debug --clean-first
cmake --build cmake-build-debug --target docs
cmake --build cmake-build-debug --target format
```
