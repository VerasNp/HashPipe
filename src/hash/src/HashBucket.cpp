#include "HashBucket.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

using namespace std;
using namespace filesystem;

HashBucket::HashBucket(
        string path
) : path_(path) {
    fstream bucket;
    const string BUCKET_BASE_DIR = "hash_dir";
    bucket.open(BUCKET_BASE_DIR + "/" + path, ios::in);
    if (!bucket.is_open()) {
        printf("Erro ao abrir bucket %s.\n", path.c_str());
        exit(1);
    }
    vector<string> row;
    string line, word, temp;
    bucket >> temp;

    this->local_depth_ = stoi(temp);
    vector<pair<unsigned short int, unsigned short int>> entries;

    while (bucket >> temp) {
        row.clear();
        stringstream s(temp);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }
        auto entry = pair(stoi(row[0]), stoi(row[1]));
        entries.push_back(entry);
    }
    this->set_entries(entries);
}

bool
HashBucket::create(
        const string &file,
        unsigned short int local_depth,
        const vector<pair<unsigned short int, unsigned short int>> &entries
) {
    const string BUCKET_BASE_DIR = "hash_dir";
    if (!filesystem::exists(BUCKET_BASE_DIR)) {
        filesystem::create_directories(BUCKET_BASE_DIR);
    }
    ofstream bucket_file;
    bucket_file.open(BUCKET_BASE_DIR + "/" + file);
    if (!bucket_file.is_open()) return false;
    bucket_file << local_depth;
    cout << "Registrada profundidade local em " << file << endl;
    for (const auto entry: entries) {
        bucket_file << entry.first << "," << entry.second;
        cout << "Registrada entrada de dados em " << file << endl;
    }
    bucket_file.close();
    return true;
}

string HashBucket::get_path() {
    return this->path_;
}

void HashBucket::set_local_depth(unsigned short local_depth) {
    this->local_depth_ = local_depth;
}

unsigned short int HashBucket::get_local_depth() {
    return this->local_depth_;
}

void HashBucket::set_entries(vector<pair<unsigned short, unsigned short>> entries) {
    this->entries_ = entries;
}

vector<pair<unsigned short int, unsigned short int>> HashBucket::get_entries() {
    return this->entries_;
}


bool HashBucket::save() {
    const string BUCKET_BASE_DIR = "hash_dir";
    filesystem::remove(BUCKET_BASE_DIR + "/" + this->get_path());
    ofstream bucket;
    bucket.open(BUCKET_BASE_DIR + "/" + this->get_path(), std::ios_base::app);
    if (!bucket.is_open()) {
        printf("Erro ao abrir bucket %s.\n", this->get_path().c_str());
        exit(1);
    }

    stringstream ss;
    ss << this->get_local_depth();
    bucket << ss.str();

    for (auto const &entry : this->get_entries()) {
        ss.str("");
        ss << '\n' << entry.first << "," << entry.second;
        bucket << ss.str();
    }

    bucket.close();
    return true;
}

bool HashBucket::insert(pair<unsigned short, unsigned short> entry) {
    ofstream bucket;
    const string BUCKET_BASE_DIR = "hash_dir";
    auto size = this->get_entries().size();
    if (this->get_entries().size() == 3) {
        return false;
    }

    bucket.open(BUCKET_BASE_DIR + "/" + this->path_, std::ios_base::app); // append instead of overwrite
    stringstream ss;
    ss << '\n' << entry.first << "," << entry.second;

    bucket << ss.str();
    bucket.close();
    return true;
}

HashBucket::~HashBucket() = default;
