#ifndef HASHBUCKET_H
#define HASHBUCKET_H
#include <bits/stl_pair.h>
#include <vector>
#include <string>

using namespace std;

class HashBucket
{
public:
    HashBucket(const std::string path, unsigned short int local_depth,
               std::vector<std::tuple<unsigned short int, unsigned short int>> entries);

    static bool create(
        const std::string path,
        unsigned short int local_depth,
        std::vector<std::pair<unsigned short int, unsigned short int>> entries);

    static bool update_local_depth(
        const std::string path,
        unsigned short int local_depth
    );

    static bool insert(
        const std::string path,
        std::pair<unsigned short int, unsigned short int> entry
    );

    static bool remove(
        const std::string path,
        std::pair<unsigned short int, unsigned short int> entry
    );

    static std::pair<unsigned short int, std::vector<std::pair<unsigned short int, unsigned short int>>> read(
        const std::string path
    );

private:
    const char* path_;
    unsigned short int local_depth_;
    std::vector<std::tuple<unsigned short int, unsigned short int>> entries_;
};


#endif //HASHBUCKET_H
