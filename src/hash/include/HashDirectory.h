#ifndef HASH_H
#define HASH_H
#include <HashBucket.h>
#include <vector>
#include <string>

using namespace std;

class HashDirectory
{
public:
    HashDirectory();

    bool create(unsigned short int global_depth);

    static unsigned int hash_function(unsigned short int key, unsigned short int depth);

    /* 
    will check if this key is present in data.csv, 
    then manipulate buckets to insert the new key 
    and log on out.txt 
    */
    bool hash_insert(pair<unsigned short int, unsigned short int> key,  bool log);

    /* Will remove the key from a bucket and log on out.txt. */
    bool hash_remove(unsigned short int key);

    /* Will search a key inside a bucket and log on out.txt*/
    bool hash_search(unsigned short int entry);

    unsigned short int get_global_depth();

    void set_global_depth(unsigned short int global_depth);

    vector<string> get_directory();

    void set_directory(vector<string> directory);

    void log_operations(string path, string operation);

private:
    unsigned short int global_depth_;
    vector<string> directory_;
//    Database* database_;

    bool hash_split_bucket(string original_bucket, pair<unsigned short, unsigned short> entry_to_add); // can call hash_duplicate_directory if needed.

    bool hash_duplicate_directory(void); // just duplicate directory, new indexes points to sibling buckets path.
};

#endif //HASH_H
