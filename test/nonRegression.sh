#!/bin/bash

BUILD_PATH="build"
SEPARATOR="--------"
REPORT=""

TEST_NAME=testMapLoadSave
echo "${SEPARATOR}"
${BUILD_PATH}/test $TEST_NAME ./test/testMap1.soko ${BUILD_PATH}/tmpMap.soko 
TEST_STATUS=$?
REPORT="${REPORT}\n${TEST_NAME}: ${TEST_STATUS}"
echo "${SEPARATOR}"


TEST_NAME=testMapMove
MOVES="H J K L"
for MOVE in ${MOVES}
do
    echo "${SEPARATOR}"
    ${BUILD_PATH}/test $TEST_NAME $MOVE
    TEST_STATUS=$?
    REPORT="${REPORT}\n${TEST_NAME}: ${TEST_STATUS} move=${MOVE}"
    echo "${SEPARATOR}"
done

TEST_NAME=testSokoParser
echo "${SEPARATOR}"
${BUILD_PATH}/test $TEST_NAME test/listSokoMaps.txt ${BUILD_PATH}/sokoSet1 sokoSet1
TEST_STATUS=$?
REPORT="${REPORT}\n${TEST_NAME}: ${TEST_STATUS}"
echo "${SEPARATOR}"

echo "==========================="
echo "        TEST REPORT        "
echo "==========================="
printf "${REPORT}\n"

