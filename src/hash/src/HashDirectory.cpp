#include "HashDirectory.h"
#include "HashBucket.h"
#include "Database.h"

#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

using namespace std;

HashDirectory::HashDirectory() = default;

bool HashDirectory::create(
        const unsigned short int global_depth) {
    set_global_depth(global_depth);
    vector<string> buckets;
    for (int i = 0; i < std::pow(2, global_depth); i++) {
        string path = std::to_string(i) + ".txt";
        buckets.push_back(path);
        vector<pair<unsigned short int, unsigned short int>> entries;
        if (HashBucket::create(path, global_depth, entries)) {
            printf("Bucket %d criado com sucesso.\n", i);
        } else {
            printf("Não foi possível criar o bucket %s.\n", path.c_str());
        }
    }
    set_directory(buckets);
    return true;
}

bool
HashDirectory::hash_insert(pair<unsigned short int, unsigned short int> entry, bool log=false) {
    unsigned int bucket_hash =
            HashDirectory::hash_function(entry.second, this->global_depth_);
    string bucket_path = this->get_directory()[bucket_hash];
    auto bucket = new HashBucket(bucket_path);
    bool bucket_inserted_successfully = bucket->insert(entry);

    bool hash_duplicated = false;
    // bucket is full
    if (!bucket_inserted_successfully) {
        // check if hash_directory has to be duplicated

        if (bucket->get_local_depth() == this->get_global_depth()) {
            hash_duplicated = this->hash_duplicate_directory();
            if (!hash_duplicated) {
                printf("Error while trying to duplicate hash directory.\n");
                exit(1);
            }
        }
        bool bucket_splited = this->hash_split_bucket(bucket_path, entry);
        if (!bucket_splited) {
            printf("Error while trying to split bucket %s", bucket_path.c_str());
            exit(1);
        }


    }

    if (log) {
        free(bucket);
        auto bucket = new HashBucket(bucket_path);
        this->log_operations(
                "./out",
                "INC:" + to_string(entry.second) + "/" + to_string(this->get_global_depth()) + "," +
                to_string(bucket->get_local_depth()));
    }
    if (hash_duplicated) {
        free(bucket);
        auto bucket = new HashBucket(bucket_path);
        this->log_operations(
                "./out",
                "DUP_DIR:/" + to_string(this->get_global_depth()) + "," + to_string(bucket->get_local_depth()));
    }

    free(bucket);
    return true;
}

bool HashDirectory::hash_duplicate_directory() {
    this->set_global_depth(this->get_global_depth() + 1);
    auto directory = this->get_directory();
    auto aux = directory;
    for (auto const i: directory) {
        aux.push_back(i);
    }
    this->set_directory(aux);
    return true;
}

bool
HashDirectory::hash_split_bucket(std::string original_bucket_path, pair<unsigned short, unsigned short> entry_to_add) {
    size_t dotPosition = original_bucket_path.find('.'); // Find the position of the dot

    //  Does not have a . in bucket path.
    if (dotPosition == std::string::npos) {
        printf("Erro: caminho do bucket está inválido. Bucket passado: %s\n", original_bucket_path.c_str());
        exit(1);
    }
    unsigned short original_hash = stoi(original_bucket_path.substr(0, dotPosition));
    auto original_bucket = new HashBucket(original_bucket_path);

    unsigned short new_hash = original_hash + std::pow(2, original_bucket->get_local_depth());
    string new_bucket_path = std::to_string(new_hash) + ".txt";
    original_bucket->set_local_depth(original_bucket->get_local_depth() + 1);

    vector<pair<unsigned short int, unsigned short int>> new_entries;
    HashBucket::create(new_bucket_path, original_bucket->get_local_depth(), new_entries);
    this->directory_[new_hash] = new_bucket_path;

    // distribute elements along the buckets
    vector<pair<unsigned short, unsigned short>> original_entries = original_bucket->get_entries();
    int i = 0;
    auto aux = original_entries;
    for (auto const &entry: original_entries) {
        unsigned short hash = HashDirectory::hash_function(entry.second, original_bucket->get_local_depth());
        if (hash != original_hash) {
            new_entries.push_back(entry);
            aux.erase(aux.begin() + i);
        } else {
            i++;
        }
    }
    original_bucket->set_entries(aux);
    original_bucket->save();
    free(original_bucket);

    auto new_bucket = new HashBucket(new_bucket_path);
    new_bucket->set_entries(new_entries);
    new_bucket->save();

    // entry to add will go to one of the buckets.
    unsigned int entry_to_add_hash = HashDirectory::hash_function(entry_to_add.second,
                                                                  original_bucket->get_local_depth());
    if (entry_to_add_hash != original_hash) {
        bool entry_added = new_bucket->insert(entry_to_add);
        if (!entry_added) {
            bool directory_duplicated = this->hash_duplicate_directory();
            if (!directory_duplicated) {
                printf("Erro ao duplicar diretório.\n");
                exit(1);
            }

            bool bucket_duplicated = this->hash_split_bucket(new_bucket_path, entry_to_add);
            if (!bucket_duplicated) {
                printf("Erro ao dividir bucket.\n");
                exit(1);
            }

        }
    } else {
        free(new_bucket);
        auto original_bucket = new HashBucket(original_bucket_path);

        bool entry_added = original_bucket->insert(entry_to_add);
        if (!entry_added) {
            bool directory_duplicated = this->hash_duplicate_directory();
            if (!directory_duplicated) {
                printf("Erro ao duplicar diretório.\n");
                exit(1);
            }

            bool bucket_duplicated = this->hash_split_bucket(original_bucket_path, entry_to_add);
            if (!bucket_duplicated) {
                printf("Erro ao dividir bucket.\n");
                exit(1);
            }
        }
    }

    return true;
}

bool HashDirectory::hash_remove(unsigned short key) {
    auto hash = this->hash_function(key, this->get_global_depth());
    auto bucket_path = this->get_directory()[hash];
    auto bucket = new HashBucket(bucket_path);
    int removed = 0;

    auto entries = bucket->get_entries();
    auto aux = entries;
    int i = 0;
    for (auto const entry: entries) {
        if (entry.second == key) {
            aux.erase(aux.begin() + i);
            removed++;
            i--;
        }
        i++;
    }
    if (removed != 0) {
        log_operations("./out",
                       "REM:" + to_string(key) + "/" + to_string(removed) + "," + to_string(this->get_global_depth()) +
                       "," +
                       to_string(bucket->get_local_depth()));
        bucket->set_entries(aux);
        bucket->save();
        free(bucket);
        return true;
    }
    printf("Não foi possível remover %d, pois não existe.\n", key);
    free(bucket);
    return false;
}

bool HashDirectory::hash_search(unsigned short int key) {
    unsigned int bucket_hash =
            HashDirectory::hash_function(key, this->global_depth_);
    string bucket_path = this->get_directory()[bucket_hash];
    auto bucket = new HashBucket(bucket_path);
    unsigned short int count = 0;
    for (const auto bucket_entry: bucket->get_entries()) {
        if (key == bucket_entry.second) {
            count++;
        }
    }
    this->log_operations(
            "./out",
            "BUS:" + to_string(key) + "/" + to_string(count));
    free(bucket);
    return true;
}

unsigned short int HashDirectory::get_global_depth() {
    return this->global_depth_;
}

void HashDirectory::set_global_depth(unsigned short int global_depth) {
    this->global_depth_ = global_depth;
}

void HashDirectory::set_directory(vector<std::string> directory) {
    this->directory_ = std::move(directory);
}

vector<string> HashDirectory::get_directory() {
    return this->directory_;
}

unsigned int HashDirectory::hash_function(const unsigned short int key, const unsigned short int depth) {
    return key & ((1 << depth) - 1);
}

void
HashDirectory::log_operations(string path, string data) {
    if (!filesystem::exists(path)) {
        filesystem::create_directories(path);
    }
    ofstream log_file;
    log_file.open(path + "/out.txt", std::ios_base::app);
    if (!log_file.is_open())
        cout << "Erro ao registrar operação!" << endl;
    log_file << data << endl;
    cout << "Registrada operação em " << path << endl;
    log_file.close();
}

//void HashDirectory::set_database(Database* database) {
//    this->database_ = database;
//}
//
//Database *HashDirectory::get_database() {
//    return this->database_;
//}
