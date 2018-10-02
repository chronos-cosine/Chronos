gcov ./CMakeFiles/Pattern_Matcher_Unit_Tests.dir/TestRunner.gcno
lcov --capture --directory . --output-file ./CMakeFiles/Pattern_Matcher_Unit_Tests.dir/TestRunner.info
genhtml ./CMakeFiles/Pattern_Matcher_Unit_Tests.dir/TestRunner.info --output-directory CodeCoverage
firefox "./CMakeFiles/Pattern_Matcher_Unit_Tests.dir/CodeCoverage/index.html"