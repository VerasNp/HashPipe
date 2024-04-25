#ifndef HASHBUCKET_H
#define HASHBUCKET_H
#include <bits/stl_pair.h>
#include <vector>

using namespace std;

class HashBucket
{
public:
    static bool create(
        const char* path,
        unsigned short int local_depth,
        std::vector<std::pair<unsigned short int, unsigned short int>> entries);
    HashBucket(const char* path, unsigned short int local_depth,
               std::vector<std::tuple<unsigned short int, unsigned short int>> entries);

private:
    const char* path_;
    unsigned short int local_depth_;
    std::vector<std::tuple<unsigned short int, unsigned short int>> entries_;
};


#endif //HASHBUCKET_H
