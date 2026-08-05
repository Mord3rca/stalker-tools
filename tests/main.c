#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "main.h"

CU_SuiteInfo suites[] = {
	{"STCore FS Path", fs_path_init, fs_path_cleanup, NULL, NULL, fs_path_tests},
	CU_SUITE_INFO_NULL,
};

int main(void)
{
	if (CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();

	if (CU_register_suites(suites) != CUE_SUCCESS)
		return CU_get_error();

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();

	CU_basic_show_failures(CU_get_failure_list());

	CU_cleanup_registry();
	return CU_get_error();
}
