cmake_minimum_required(VERSION 3.15)
project(lexer CXX)



add_executable(lexer src/lexer.cpp src/main.cpp)



install(TARGETS lexer DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
