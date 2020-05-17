# FirstPerson
# A small program for projecting a 3D world in a terminal emulator

project(FirstPerson)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra)

# Label the files which are required for the program
set(SOURCE_FILES
        src/main.c
        src/terminal.c
        src/utilities.c
        src/map.c
        src/input.c
        src/render.c
)

# The curses library is stored in various places depending on system
if(UNIX AND NOT APPLE)
        find_package(Curses REQUIRED)
elseif(APPLE)
        include_directories(/usr/local/opt/ncurses/include)
        link_directories(/usr/local/opt/ncurses/lib)
endif()

# Create the executable and link the libraries
add_executable(FirstPerson ${SOURCE_FILES})
target_link_libraries(FirstPerson m ncursesw)
