#include "HashDirectory.h"

#include <utility>
#include <string>
#include <vector>

using namespace std;

HashDirectory::HashDirectory(
    const unsigned short int global_depth,
    vector<string> directory) : global_depth_(global_depth), directory_(directory)
{
}


unsigned int HashDirectory::hash_function(const unsigned short int key, const unsigned short int depth)
{
    return key & ((1 << depth) - 1);
}
