add_test([=[VectorTest.VectorAddition]=]  /home/slinky/Slinky2D/build/HelloTest [==[--gtest_filter=VectorTest.VectorAddition]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VectorTest.VectorAddition]=]  PROPERTIES WORKING_DIRECTORY /home/slinky/Slinky2D/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  HelloTest_TESTS VectorTest.VectorAddition)
