/**
 * @file 
 * @author your name (you@domain.com)
 * @brief 
 * @version 
 * @date YYYY-MM-DD
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_your_func)
{
    ck_assert(1 == 1);

} END_TEST

Suite * PROJECT_SUITE(void)
{
	Suite *suite;
	TCase *tc_func;

	suite = suite_create("test_driver");

	/* tests functions from spice_file_io.c */
	tc_func = tcase_create("test_funcs");
	tcase_add_test(tc_func, test_your_func);

	suite_add_tcase(suite, tc_func);

	return suite;
}


int main(void)
{
	Suite *suite = PROJECT_SUITE();	// ex: test_calculator_suite
	SRunner *runner = srunner_create(suite);

	// Prevents valigrind errors from appearing that could be mistakenly be
	// considered the programmers fault. Will run slower! For details, see:
	//
	// https://libcheck.github.io/check/doc/check_html/check_4.html#Finding-Memory-Leaks
	srunner_set_fork_status(runner, CK_NOFORK);

	// Actual Suite Runner command of execution with desired verbosity level
	srunner_run_all(runner, CK_VERBOSE);

	// Extract results for exit code handling
	int no_failed = srunner_ntests_failed(runner);

	// free() all resources used for execution of Suite Runner.
	srunner_free(runner);

	return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*** end of file ***/