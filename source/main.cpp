/**
 * @file main.cpp
 * @brief Entry point of the K-Means clustering program.
 *
 * This program performs K-Means clustering on a dataset
 * provided in CSV format.
 *
 * @author Maryia Pilipchuk
 * @date 2025
 */

#include <iostream>
#include <string>
#include "kmeans.h"

using namespace std;

/**
 * @brief Prints program usage instructions.
 */
void printManual() {
    cout << "Simple K-Means Program\n\n";
    cout << "Usage:\n Project_1.exe -i Iris.csv -o out.txt -k 3\n\n";
}

/**
 * @brief Main function of the program.
 *
 * Parses command-line arguments and runs the K-Means algorithm.
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line arguments
 * @return int Exit status code
 */
int main(int argc, char* argv[]) {

    if (argc == 1) {
        printManual();
        return 0;
    }

    string inputFile, outputFile;
    int k = 0;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-i" && i + 1 < argc) {
            inputFile = argv[++i];
        }
        else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        }
        else if (arg == "-k" && i + 1 < argc) {
            k = stoi(argv[++i]);
        }
        else {
            cout << "Unknown argument: " << arg << "\n";
            printManual();
            return 1;
        }
    }

    if (inputFile.empty() || outputFile.empty() || k <= 0) {
        printManual();
        return 1;
    }

    KMeans model(k);
    model.loadData(inputFile);
    model.run();
    model.saveResults(outputFile);

    return 0;
}

