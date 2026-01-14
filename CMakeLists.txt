cmake_minimum_required(VERSION 3.0)

# project name
project(sokoban)

# create variable to store src and include dirs
set(SRC_DIR src)

set(INCLUDE_DIR include)

set(TEST_DIR test)

# create variable to store headers and modules that are not executable
set(HEADERS 
    ${INCLUDE_DIR}/MyClass.h
    ${INCLUDE_DIR}/MainMenu.h
    ${INCLUDE_DIR}/Game.h
    ${INCLUDE_DIR}/Map.h
    ${INCLUDE_DIR}/BlockType.h
    ${INCLUDE_DIR}/MoveType.h
    ${INCLUDE_DIR}/SokobanWindow.h
)

set(MODULES 
    ${SRC_DIR}/MyClass.cpp
    ${SRC_DIR}/MainMenu.cpp
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/Map.cpp
    ${SRC_DIR}/SokobanWindow.cpp
)

add_executable(sokoban ${SRC_DIR}/sokoban.cpp ${MODULES} ${HEADERS})
target_include_directories(sokoban PRIVATE ${INCLUDE_DIR})

# link with gtk library
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-4.0)
target_include_directories(sokoban PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(sokoban ${GTKMM_LIBRARIES})

add_executable(test ${TEST_DIR}/test.cpp ${TEST_DIR}/test.h ${MODULES} ${HEADERS})
target_include_directories(test PRIVATE ${INCLUDE_DIR})
target_include_directories(test PRIVATE ${TEST_DIR})

target_include_directories(test PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(test ${GTKMM_LIBRARIES})

