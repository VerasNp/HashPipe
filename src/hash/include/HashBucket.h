#ifndef HASHBUCKET_H
#define HASHBUCKET_H

#include <bits/stl_pair.h>
#include <vector>
#include <string>

using namespace std;

class HashBucket {
public:
    HashBucket(
            string path);

    ~HashBucket();

    void set_path(string path);

    string get_path();

    void set_local_depth(unsigned short int local_depth);

    unsigned short int get_local_depth();

    void set_entries(vector<pair<unsigned short int, unsigned short int>> entries);

    vector<pair<unsigned short int, unsigned short int>> get_entries();

    bool save(void);

    bool insert(pair<unsigned short, unsigned short> entry);

    static bool create(
            const string& file,
            unsigned short int local_depth,
            const vector<pair<unsigned short int, unsigned short int>>& entries);

private:
    const string path_;
    unsigned short int local_depth_;
    vector<pair<unsigned short int, unsigned short int>> entries_;
};


#endif //HASHBUCKET_H
