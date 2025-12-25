#!/bin/sh

echo translate 1.0.0 release 1
echo translate test script - open systems environments
echo ================================================================================

if [ -d out ]; then
    rm -rf out
fi

mkdir out

echo
echo test case 1: comma-separated values to comma-separated values
echo --------------------------------------------------------------------------------
echo

./translate -i test.01 -o out/output1.dat -j csv -p csv -v -r -x

echo
echo test case 2: comma-separated values to tab-separated values
echo --------------------------------------------------------------------------------
echo

./translate -i test.01 -o out/output2.dat -j csv -p tsv -v -r -x

echo
echo test case 3: tab-separated values to comma-separated values
echo --------------------------------------------------------------------------------
echo

./translate -i test.02 -o out/output3.dat -j tsv -p csv -v -r -x

echo
echo test case 4: tab-separated values to tab-separated values
echo --------------------------------------------------------------------------------
echo

./translate -i test.02 -o out/output4.dat -j tsv -p tsv -v -r -x
