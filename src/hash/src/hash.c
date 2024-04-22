#include "hash.h"

unsigned long
hash_function (unsigned short int key, unsigned short int depth)
{
  return key & ((1 << depth) - 1);
}