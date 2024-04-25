#ifndef HASH_H
#define HASH_H
#include <HashBucket.h>
#include <string>

using namespace std;

class HashDirectory
{
public:
    static unsigned int hash_function(unsigned short int key, unsigned short int depth);
    HashDirectory(unsigned short int global_depth, vector<string> directory);

    /* 
    will check if this key is present in data.csv, 
    then manipulate buckets to insert the new key 
    and log on out.txt 
    */
    bool hash_insert(unsigned short int key);

    /* Will remove the key from a bucket and log on out.txt. */
    bool hash_remove(unsigned short int key);

    /* Will search a key inside a bucket and log on out.txt*/
    bool hash_search(unsigned short int key);

private:
    unsigned short int global_depth_;
    vector<string> directory_;

    bool hash_split_bucket(string original_bucket); // can call hash_duplicate_directory if needed.
    bool hash_merge_bucket(string bucket1, string bucket2); // maybe we need to merge buckets. Can trigger hash_shrink_directory.
    
    bool hash_duplicate_directory(void); // just duplicate directory, new indexes points to sibling buckets path.
    bool hash_shrink_directory(void); // just shrink directory by half.
};

#endif //HASH_H
