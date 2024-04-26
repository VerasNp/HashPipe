#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

#include "Database.h"

using namespace std;

int main(const int argc, char *argv[]) {
    if (argc < 3 || argc > 3) {
        printf("\nQuantidade de entradas errada!\n"
               "Informe o arquivo de entrada e local onde estão as tabelas do banco!\"");
        exit(EXIT_FAILURE);
    } else {
        ifstream inputFile(argv[1]);
        if (!inputFile.is_open()) {
            cerr << "Error opening the file!" << endl;
            return 1;
        }
        string line;
        auto database = new Database(argv[2]);
        database->init_hashIndex("compras", 3);
        auto hashDirectory = database->get_hashDirectory();
        while (getline(inputFile, line)) {
            if (line.rfind("PG/", 0) == 0) {
                const unsigned short int data =
                        stoi(line.substr(line.rfind('/') + 1, line.length()));
                if (hashDirectory->create(data)) {
                    cout << "Criação de diretório finalizado!" << endl;
                    hashDirectory->log_operations("./out", "PG/" + to_string(hashDirectory->get_global_depth()));
                } else {
                    cout << "Erro na criação do diretório" << endl;
                    exit(EXIT_FAILURE);
                }
            } else if (line.rfind("INC:", 0) == 0) {
                const unsigned short int data =
                        stoi(line.substr(line.rfind(':') + 1, line.length()));
                auto tuples = database->select("compras", 2, data);

                int i=0;
                int size = tuples.size();
                for (const auto tuple: tuples) {
                    pair<unsigned short int, unsigned short int> dataToInsert;
                    dataToInsert.first = get<0>(tuple);
                    dataToInsert.second = get<2>(tuple);
                    hashDirectory->hash_insert(dataToInsert, i == (size - 1));
                    i++;
                }
            } else if (line.rfind("REM:", 0) == 0) {
                const unsigned short int data =
                        stoi(line.substr(line.rfind(':') + 1, line.length()));
                hashDirectory->hash_remove(data);
            } else if (line.rfind("BUS=:", 0) == 0) {
                const unsigned short int data =
                        stoi(line.substr(line.rfind(':') + 1, line.length()));
                hashDirectory->hash_search(data);
            } else {
                cout << line << " Comando desconhecido!" << endl;
            }
        }
        hashDirectory->log_operations(
                "./out",
                "P:/" + to_string(hashDirectory->get_global_depth()));
        free(database);
        return 0;
    }
}
