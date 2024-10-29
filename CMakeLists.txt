cmake_minimum_required(VERSION 3.23)
project(PEA1)

set(CMAKE_CXX_STANDARD 14)

add_executable(PEA1 main.cpp IO/FileReader.cpp structures/Matrix.cpp algorithms/BruteForce.cpp algorithms/BranchAndBound.cpp algorithms/DynamicProgramming.cpp algorithms/BnB.cpp measurements/Measurements.cpp IO/CSVWriter.cpp)
