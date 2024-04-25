#include "HashDirectory.h"

#include <utility>

HashDirectory::HashDirectory(
    const unsigned short int global_depth,
    std::vector<HashBucket*> directory) : global_depth_(global_depth), directory_(std::move(directory))
{
}


unsigned int HashDirectory::hash_function(const unsigned short int key, const unsigned short int depth)
{
    return key & ((1 << depth) - 1);
}
