# SimpleFP
# A small program for rendering a 3D world on the command line

project(SimpleFP)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wall -Wextra)

# Label the files which are required for the program
set(SOURCE_FILES
        src/Main.c
        src/Terminal.c
        src/Utilities.c
        src/Map.c
        src/Input.c
        src/Render.c
)

# The curses library is stored in various places depending on system
if(UNIX AND NOT APPLE)
        find_package(Curses REQUIRED)
elseif(APPLE)
        include_directories(/usr/local/opt/ncurses/include)
        link_directories(/usr/local/opt/ncurses/lib)
endif()

# Create the executable and link the libraries
add_executable(SimpleFP ${SOURCE_FILES})
target_link_libraries(SimpleFP m ncursesw)
