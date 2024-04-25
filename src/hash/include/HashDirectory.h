#ifndef HASH_H
#define HASH_H
#include <HashBucket.h>
#include <string>

using namespace std;

class HashDirectory
{
public:
    static unsigned int hash_function(unsigned short int key, unsigned short int depth);
    HashDirectory(unsigned short int global_depth, std::vector<HashBucket*> directory);

private:
    unsigned short int global_depth_;
    std::vector<string> directory_;
};

#endif //HASH_H
