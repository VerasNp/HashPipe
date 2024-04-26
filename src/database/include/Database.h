#ifndef HASHPIPE_DATABASE_H
#define HASHPIPE_DATABASE_H

#include <string>
#include "HashDirectory.h"

using namespace std;

class Database {
public:
    Database(const string &tablesDir);
    ~Database();
    HashDirectory* get_hashDirectory();
    void set_hashDirectory(HashDirectory *hashDirectory);
    void set_tablesDir(const string &tablesDir);
    string get_tablesDir();
    vector<tuple<unsigned short int, double, unsigned short int>>
    select(const string &tableName, unsigned short int column, unsigned short int key);
    bool init_hashIndex(string tableName, int column);

private:
    string tablesDir_;
    HashDirectory* hashDirectory_;
};


#endif //HASHPIPE_DATABASE_H
