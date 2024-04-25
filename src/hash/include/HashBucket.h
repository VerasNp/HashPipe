#ifndef HASHBUCKET_H
#define HASHBUCKET_H
#include <bits/stl_pair.h>
#include <vector>
#include <string>

using namespace std;

class HashBucket
{
public:
    HashBucket(const string path, unsigned short int local_depth,
               vector<tuple<unsigned short int, unsigned short int>> entries);

    static bool create(
        const string path,
        unsigned short int local_depth,
        vector<tuple<unsigned short int, unsigned short int>> entries);

    static bool update_local_depth(
        const string path,
        unsigned short int local_depth
    );

    static bool insert(
        const string path,
        tuple<unsigned short int, unsigned short int> entry
    );

    static bool remove(
        const string path,
        tuple<unsigned short int, unsigned short int> entry
    );

    static tuple<unsigned short int, vector<tuple<unsigned short int, unsigned short int>>> read(
        const string path
    );

private:
    const string path_;
    unsigned short int local_depth_;
    vector<tuple<unsigned short int, unsigned short int>> entries_;
};


#endif //HASHBUCKET_H
