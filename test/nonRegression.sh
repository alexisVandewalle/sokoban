#!/bin/bash

BUILD_PATH=$1
SEPARATOR="--------"
REPORT=""
TEST_LIST="testSokoban testSokobn"

for TEST_NAME in $TEST_LIST
do
    echo "${SEPARATOR}"
    ${BUILD_PATH}/test $TEST_NAME
    TEST_STATUS=$?
    REPORT="${REPORT}\n${TEST_NAME}: ${TEST_STATUS}"
    echo "${SEPARATOR}"
done


echo "==========================="
echo "        TEST REPORT        "
echo "==========================="
printf "${REPORT}\n"

