cmake_minimum_required(VERSION 3.0)

# project name
project(sokoban)

# create variable to store src and include dirs
set(SRC_DIR src)

set(INCLUDE_DIR include)

set(TEST_DIR test)

# create variable to store headers and modules that are not executable
set(HEADERS_COMMON
    ${INCLUDE_DIR}/MyClass.h
    ${INCLUDE_DIR}/MainMenu.h
    ${INCLUDE_DIR}/Game.h
    ${INCLUDE_DIR}/Map.h
    ${INCLUDE_DIR}/BlockType.h
    ${INCLUDE_DIR}/MoveType.h
    ${INCLUDE_DIR}/exceptions.h
    ${INCLUDE_DIR}/SokoParser.h
    ${INCLUDE_DIR}/NodeMap.h
    ${INCLUDE_DIR}/NodeMap.h
    ${INCLUDE_DIR}/Solver.h
)

set(HEADERS 
    ${HEADERS_COMMON}
    ${INCLUDE_DIR}/SokobanWindow.h
    ${INCLUDE_DIR}/ImportMapDialog.h
    ${INCLUDE_DIR}/MoveSequenceDialog.h
)

set(MODULES_COMMON
    ${SRC_DIR}/MyClass.cpp
    ${SRC_DIR}/MainMenu.cpp
    ${SRC_DIR}/Game.cpp
    ${SRC_DIR}/Map.cpp
    ${SRC_DIR}/SokoParser.cpp
    ${SRC_DIR}/NodeMap.cpp
    ${SRC_DIR}/Solver.cpp
)

set(MODULES
    ${MODULES_COMMON}
    ${SRC_DIR}/SokobanWindow.cpp
    ${SRC_DIR}/ImportMapDialog.cpp
    ${SRC_DIR}/MoveSequenceDialog.cpp
)

add_executable(sokobanCmdLine ${SRC_DIR}/sokobanCmdLine.cpp ${MODULES_COMMON} ${HEADERS_COMMON})
target_include_directories(sokobanCmdLine PRIVATE ${INCLUDE_DIR})

add_executable(sokoban ${SRC_DIR}/sokoban.cpp ${MODULES} ${HEADERS})
target_include_directories(sokoban PRIVATE ${INCLUDE_DIR})

add_executable(sokobanParser ${SRC_DIR}/sokobanParser.cpp ${MODULES_COMMON} ${HEADERS_COMMON})
target_include_directories(sokobanParser PRIVATE ${INCLUDE_DIR})

add_executable(sokobanSolver ${SRC_DIR}/sokobanSolver.cpp ${MODULES_COMMON} ${HEADERS_COMMON})
target_include_directories(sokobanSolver PRIVATE ${INCLUDE_DIR})

# link with gtk library
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-4.0)
target_include_directories(sokoban PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(sokoban ${GTKMM_LIBRARIES})

add_executable(test ${TEST_DIR}/test.cpp ${TEST_DIR}/test.h ${MODULES_COMMON} ${HEADERS_COMMON})
target_include_directories(test PRIVATE ${INCLUDE_DIR})
target_include_directories(test PRIVATE ${TEST_DIR})


