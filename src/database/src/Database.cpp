#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

#include "Database.h"


Database::Database(const string &tablesDir) {
    set_tablesDir(tablesDir);
}

Database::~Database() {
    delete this;
}

void Database::set_tablesDir(const string &tablesDir) {
    this->tablesDir_ = tablesDir;
}

string Database::get_tablesDir() {
    return this->tablesDir_;
}

void Database::set_hashDirectory(HashDirectory *hashDirectory) {
    this->hashDirectory_ = hashDirectory;
}

HashDirectory *Database::get_hashDirectory() {
    return this->hashDirectory_;
}

vector<tuple<unsigned short int, double, unsigned short int>>
Database::select(
        const string &tableName,
        unsigned short int column,
        unsigned short int key
) {
    fstream file;
    file.open(this->get_tablesDir() + "/" + tableName + ".csv", ios::in);
    vector<string> row;
    string line, word, temp;
    vector<tuple<unsigned short int, double, unsigned short int>> fullTuple;
    unsigned short int aux = 0;
    while (file >> temp) {
        row.clear();
        stringstream s(temp);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        if (stoi(row[column]) == key) {
            tuple<unsigned short int, double, unsigned short int> data;
            get<0>(data) = stoi(row[0]);
            get<1>(data) = stoi(row[1]);
            get<2>(data) = stoi(row[2]);
            fullTuple.push_back(data);
            aux++;
        }
    }
    printf("Entrada de %d não foi encontrada no banco de dados.\n", key);
    return fullTuple;
}

bool
Database::init_hashIndex(string tableName, int column) {
    auto hashDirectory = new HashDirectory();
    this->set_hashDirectory(hashDirectory);
    return true;
}


