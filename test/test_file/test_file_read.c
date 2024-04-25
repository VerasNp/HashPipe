#include "unity.h"
#include "file.h"

void setUp(void) {} /* Is run before every test, put unit init calls here. */
void tearDown(void) {} /* Is run after every test, put unit clean-up calls here. */

void
test_ReadFile_should_ReturnLine() {
    byte *line = fileread("./data/in.txt");
    TEST_ASSERT_EQUAL_STRING("PG/2", line);
}

int
main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ReadFile_should_ReturnLine);
    return UNITY_END();
}