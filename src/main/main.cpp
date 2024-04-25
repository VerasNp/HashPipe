// C++ program to read from a file
#include <fstream>
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
        // Open the input file named "input.txt"
        ifstream inputFile(argv[1]);

        // Check if the file is successfully opened
        if (!inputFile.is_open())
        {
            cerr << "Error opening the file!" << endl;
            return 1;
        }

        string line; // Declare a string variable to store each
        // line of the file

        // Read each line of the file and print it to the
        // standard output stream
        cout << "File Content: " << endl;
        while (getline(inputFile, line))
        {
            cout << line << endl; // Print the current line
        }

        // Close the file
        inputFile.close();

        return 0;
    }
}
