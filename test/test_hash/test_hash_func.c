#include "hash.h"
#include "unity.h"

void setUp (void)
{} /* Is run before every test, put unit init calls here. */
void tearDown (void)
{} /* Is run after every test, put unit clean-up calls here. */

void
test_HashFunc_should_ReturnLSBCorrect ()
{
  unsigned long output = hash_function (1995, 3);
  TEST_ASSERT_EQUAL(3, output);
}

void
test_HashFunc_should_ReturnLSBIncorrect ()
{
  unsigned long output = hash_function (3, 3);
  TEST_ASSERT_NOT_EQUAL(2, output);
}

int
main (void)
{
  UNITY_BEGIN();
  RUN_TEST(test_HashFunc_should_ReturnLSBCorrect);
  RUN_TEST(test_HashFunc_should_ReturnLSBIncorrect);
  return UNITY_END();
}