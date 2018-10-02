sudo rm -R ./CodeCoverage/
sudo rm ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info
sudo ../bin/Chronos_Unit_Tests
sudo gcov ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.gcno
sudo lcov --capture --directory . --output-file ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info
sudo lcov --remove ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info "*boost*" -o ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info
sudo lcov --remove ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info "*gtest*" -o ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info
sudo lcov --remove ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info "*c++/*" -o ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info
sudo lcov --remove ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info "*Chronos/tests*" -o ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info
sudo genhtml ./CMakeFiles/Chronos_Unit_Tests.dir/TestRunner.info --output-directory CodeCoverage
firefox "./CodeCoverage/index.html" &
