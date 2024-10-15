/*
 Name: Hayden Lane
 Date: 2/11/2024
 Description: This program counts the number of non-white-space characters in an input text file.
    The program takes the name of the input file and optional flags (-f or -s) as command-line arguments.
    The -f flag specifies that the output should be written to a file, and -s specifies standard output.
 Limitations: The program does not support input files with non-ASCII characters properly.
    It also assumes that the command-line arguments are correctly formatted.
 */

#include <iostream>
#include <fstream>
#include <cctype> // For isspace
#include <string>

int main(int argc, char* argv[]) {
    // Check for minimum number of arguments
    if (argc < 2) {
        std::cout << "Forgot the file name. Please run the program like this:\n";
        std::cout << argv[0] << " <inputfile> [-f <outputfile> | -s]\n";
        return 1; // Return an error code
    }

    // Initialize variables
    std::string inputFileName = argv[1];
    std::string outputFileName = "";
    bool writeToFile = false;

    // Parsing command line arguments
    if (argc > 2) {
        std::string option = argv[2];
        if (option == "-f" && argc == 4) {
            writeToFile = true;
            outputFileName = argv[3];
        }
        else if (option != "-s") {
            std::cout << "Invalid option. Please use -f for file output or -s for console output.\n";
            return 1;
        }
    }

    // Attempting to open the input file
    std::ifstream inputFile(inputFileName.c_str()); // Using c_str() for compatibility
    if (!inputFile) {
        std::cerr << "File can not be opened " << inputFileName << ". Please check if the file exists.\n";
        return 1;
    }

    int nonWhiteSpaceCount = 0; // This will store our character count
    char ch;
    while (inputFile.get(ch)) { // Read character by character
        if (!std::isspace(static_cast<unsigned char>(ch))) { // Check if it's not a whitespace
            nonWhiteSpaceCount++;
        }
    }

    // Closing the input file as we're done with it
    inputFile.close();

    // Based on the user's choice, write to a file or output to console
    if (writeToFile) {
        std::ofstream outputFile(outputFileName.c_str());
        if (!outputFile) {
            std::cerr << "Can't write to file " << outputFileName << ". Please check if you have permission to write there.\n";
            return 1;
        }
        outputFile << "Found " << nonWhiteSpaceCount << " non-white-space characters.\n";
        outputFile.close(); // Don't forget to close the file
        std::cout << "The count has been saved to " << outputFileName << ".\n";
    }
    else {
        std::cout << "Found " << nonWhiteSpaceCount << " non-white-space characters.\n";
    }

    return 0; // Indicating everything went well
}
