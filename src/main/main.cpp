#include <fstream>
#include <HashDirectory.h>
#include <iostream>
#include <string>

using namespace std;

int main(const int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("\nInforme o arquivo de entrada!");
        exit(EXIT_FAILURE);
    }
    else
    {
        ifstream inputFile(argv[1]);
        if (!inputFile.is_open())
        {
            cerr << "Error opening the file!" << endl;
            return 1;
        }

        string line;

        while (getline(inputFile, line))
        {
            if (line.rfind("PG/", 0) == 0)
            {
                const unsigned short int data =
                    stoi(line.substr(line.rfind('/') + 1, line.length()));
                for ()
                new HashDirectory(data, );
            }
            else if (line.rfind("INC:", 0) == 0)
            {
                cout << line.substr(line.rfind(':') + 1, line.length()) << endl;
            }
            else if (line.rfind("REM:", 0) == 0)
            {
                cout << line.substr(line.rfind(':') + 1, line.length()) << endl;
            }
            else if (line.rfind("BUS:", 0) == 0)
            {
                cout << line.substr(line.rfind(':') + 1, line.length()) << endl;
            }
            else
            {
                cout << line << " Comando desconhecido!" << endl;
            }
        }

        inputFile.close();

        return 0;
    }
}
