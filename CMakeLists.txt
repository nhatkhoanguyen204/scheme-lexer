cmake_minimum_required(VERSION 3.15)
project(lexer CXX)

# Force the compiler to use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Tell CMake where your .hpp files are
include_directories(include)

# 2. List ALL your source files
add_executable(lexer 
    src/main.cpp
    src/LexerEngine.cpp
    src/BooleanProcessor.cpp
    src/CharacterProcessor.cpp
    src/CommentProcessor.cpp
    src/IdentifierProcessor.cpp
    src/NumberProcessor.cpp
    src/OperatorProcessor.cpp
)

# 3. Keep your install logic 
install(TARGETS lexer DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )