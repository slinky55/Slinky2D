add_test([=[AABBTest.Intersection]=]  /home/slinky/Slinky2D/build/AABBTest [==[--gtest_filter=AABBTest.Intersection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AABBTest.Intersection]=]  PROPERTIES WORKING_DIRECTORY /home/slinky/Slinky2D/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  AABBTest_TESTS AABBTest.Intersection)
