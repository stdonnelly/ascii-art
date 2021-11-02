#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// Global variables
ofstream outputFile;

// Declaring the functions here
bool openOutput();
int generateWord(string);
char openChar(char);
void toUpper(string &);

int main()
{
    // Open the output file and print a timestamp
    if (!openOutput())
    {
        return 1;
    }

    // User instructions
    cout << "This is a tool to convert text into:\n"
            "            ___     ___   _____  _____                 ___    _____    \n"
            "    /\\     /   \\   /   \\    |      |           /\\     |   \\     |    |\n"
            "   /__\\    \\___   |         |      |          /__\\    |___/     |    |\n"
            "  /    \\       \\  |         |      |         /    \\   |   \\     |    |\n"
            " /      \\  \\___/   \\___/  __|__  __|__      /      \\  |    \\    |    .\n"
            "Instructions:\n"
            "Type the text that you wish to convert.\n"
            "If there is already an ASCII art.txt file,\n"
            "that file will be appended with new ASCII art\n"
            "(Note: Only works with monospaced fonts)\n"
            "Input is not case sensitive and the output will be all capital.\n"
            "Please type your text or type \"~save\" to finish.\n";

    // Loop until the user is finished
    bool dontExit = 1;
    while (dontExit)
    {
        string inStr;
        getline(cin, inStr);

        toUpper(inStr);

        // Only save if the first 5 characters are "~save" (case insensitive)
        if (inStr.substr(0, 5) == "~SAVE")
        {
            // Delete inStr so the outer loop breaks when this is finished
            inStr.clear();

            // Close the output file
            outputFile << endl
                       << endl;
            outputFile.close();
            cout << endl;
            cout << "Finished saving file\n";

            string ext;

            while (true)
            {
                // Ask the user if they would like to finish
                cout << "Would you like to exit?\n";
                cout << "Type \"yes\" or \"no\"\n";
                cin >> ext;
                toUpper(ext);

                if (ext == "YES")
                {
                    dontExit = 0;

                    break;
                }
                else if (ext == "NO")
                {
                    if (!openOutput())
                    {
                        return 1;
                    }
                    break;
                }
                else
                {
                    cout << "Invalid input\n";
                }
            }
        }
        else
        {
            generateWord(inStr);
        }
    }

    return 0;
}

// Returns 1 if file was successfully opened, 0 if failure
bool openOutput()
{
    // Open the output file
    outputFile.open("../output/ASCII art.txt", fstream::app);

    // Test if the output file opened correctly
    if (!outputFile.is_open())
    {
        cout << "Error: Could not open output file.\n";
        // Failure
        return 0;
    }

    // Get the current time as time_t now
    time_t now = time(nullptr);
    // A char[] to use for the formatted time string
    // The length of the string is always 19, and there is always a null value at the end
    char datetime[20];
    // Format string using ISO 8601 (space instead of T)
    strftime(datetime, 20, "%F %T", localtime(&now));

    // Output the date to the output file
    outputFile << datetime << endl;

    // Success
    return 1;
}

int generateWord(string inputWord)
{
    // Constants
    const unsigned int LINES_PER_CHAR = 5;
    const size_t numOfChars = inputWord.size();
    const string INVALID_CHAR[LINES_PER_CHAR] = {"", " Missing ", "Character", " Missing ", "Character"};

    // Variables
    ifstream inputFile;
    string fileToOpen;
    string line[LINES_PER_CHAR][numOfChars]; // Line number, column number, char number

    // Read data from all files
    for (int charNum = 0; charNum < numOfChars; charNum++)
    {
        // Test if the character is one of the invalid file names and use a new name
        switch (inputWord[charNum])
        {
        case '\\':
            fileToOpen = "SLS_BK";
            break;
        case '/':
            fileToOpen = "SLS_FW";
            break;
        case ':':
            fileToOpen = "_COLON";
            break;
        case '*':
            fileToOpen = "_STAR_";
            break;
        case '?':
            fileToOpen = "QS_MRK";
            break;
        case '\"':
            fileToOpen = "QT_MRK";
            break;
        case '<':
            fileToOpen = "ARW_LF";
            break;
        case '>':
            fileToOpen = "ARW_RT";
            break;
        case '|':
            fileToOpen = "VRT_BR";
            break;
        default:
            fileToOpen = inputWord[charNum];
        }

        inputFile.open("../resources/font/" + fileToOpen + ".txt"); // Attempt to open the file

        // Use "InvalidChar" if the current char is invalid,
        // But skip if the last char is a whitespace or another nonprintable character
        if (!inputFile.is_open())
        {
            for (int lineNum = 0; lineNum < LINES_PER_CHAR; lineNum++)
            {
                line[lineNum][charNum] = INVALID_CHAR[lineNum];
            }
        }
        else
        {
            for (int lineNum = 0; lineNum < LINES_PER_CHAR; lineNum++)
            {
                getline(inputFile, line[lineNum][charNum]);
            }

            inputFile.close();
        }
    }

    // Write all data to file
    for (int lineNum = 0; lineNum < LINES_PER_CHAR; lineNum++)
    {
        for (int charNum = 0; charNum < numOfChars; charNum++)
        {
            outputFile << ' ' << line[lineNum][charNum] << ' ';
        }
        outputFile << endl;
    }

    return 0;
}

// Makes sure the input string is in uppercase
void toUpper(string &str)
{
    // Loop through all the characters in the string and capitalize any lowercase letters
    for (int i = 0; i < str.size(); i++)
    {
        if ('a' <= str[i] && str[i] <= 'z')
        {
            str[i] = str[i] & (char)0x5f;
        }
    }
}
