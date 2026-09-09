#ifndef HEADER_MAIN
#define HEADER_MAIN

// dynarray
int test_dynarray_init(void);
int test_dynarray_cleanup(void);
extern CU_TestInfo dynarray_tests[];

// STcore FS Path
int fs_path_init(void);
int fs_path_cleanup(void);
extern CU_TestInfo fs_path_tests[];

#endif  // HEADER_MAIN
