cmake_minimum_required(VERSION 3.15)
project(PnLCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable lots of warnings for safer code
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(pnl_calculator
  src/main.cpp
  src/calculator.cpp
)

target_include_directories(pnl_calculator PRIVATE ${CMAKE_SOURCE_DIR}/src)
