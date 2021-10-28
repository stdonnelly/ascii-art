#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// Global variables
ofstream outputFile;
char inputWord[7];

// Declaring the functions here
void openOutput();
int generateWord(unsigned short);
char openChar(char);

int main() {

    // Variables
    bool dontExit = 1;
    unsigned short currentLetter;

    // Open the output file and print a timestamp
    openOutput();

    // User instructions
    cout << "This is a tool to convert text into:\n"
    "            ___     ___   _____  _____                 ___    _____    \n"
    "    /\\     /   \\   /   \\    |      |           /\\     |   \\     |    |\n"
    "   /__\\    \\___   |         |      |          /__\\    |___/     |    |\n"
    "  /    \\       \\  |         |      |         /    \\   |   \\     |    |\n"
    " /      \\  \\___/   \\___/  __|__  __|__      /      \\  |    \\    |    .\n"
    "How to use:\n"
    "Type the text that you wish to convert.\n"
    "Max word size: 7\n"
    "Any higher and program will put the rest on the next line.\n"
    "If you have already used this program,\n"
    "It will put the ASCII art right after the last used session.\n"
    "(Note: Does not work for every font,\n"
    "\"Courier New\" or \"Consolas\" is recomended for viewing output text.\n"
    "No others have been tested.)\nCommands (~save, yes, no) are case sensitive.\n"
    "However, input text is not case sensative.\n"
    "This will always output capital letters.\n"
    "Please type your text.\n"
    "Type \"~save\" to finish.\n";
    
    // Loop until the user is finished
    do {
        
        // TODO Why is there a dontExit2? I think I made spaghetti with this one
        bool dontExit2 = 1;

        // Make sure that the letter starts out as 0
        currentLetter = 0;

        // TODO There has to be a better way to do this. Perhaps string converted to char[]?
        cin >> noskipws;
        while ((currentLetter < 7) && (inputWord[(currentLetter - 1)] != ' ') && (inputWord[(currentLetter - 1)] != '\n')) {
            cin >> inputWord[currentLetter];
            
            // Make sure it is uppercase
            if ('a' <= inputWord[currentLetter] && inputWord[currentLetter] <= 'z') {
                inputWord[currentLetter] = inputWord[currentLetter] & 0x5f;
            }
            
            currentLetter++;
        }
        cin >> skipws;

        if (!((inputWord[0] == '\n') || (inputWord[0] == ' '))) {
            // Find out if inputWord is "~save"
            if ((inputWord[0] == '~') &&
                (inputWord[1] == 'S') &&
                (inputWord[2] == 'A') &&
                (inputWord[3] == 'V') &&
                (inputWord[4] == 'E')) {
                
                // Close the output file
                outputFile << endl << endl;
                outputFile.close();
                cout << endl;
                cout << "Finished saving file\n";
                
                string ext;

                while (dontExit2) { // TODO There has to be a better way to make an input loop
                    
                    // Ask the user if they would like to finish
                    cout << "Would you like to exit?\n"; 
                    cout << "Type \"yes\" for yes, or \"no\" for no\n";
                    cin >> ext;

                    if (ext == "yes") {
                        dontExit = 0;
                        dontExit2 = 0;
                    } else if (ext == "no") {
                        dontExit2 = 0;
                        openOutput();
                    } else {
                        cout << "Invalid input\n";
                    }
                }
            } else {
                if ((inputWord[currentLetter - 1] == ' ') || (inputWord[currentLetter - 1] == '\n')) {
                    // Remove whitespace by telling the rest of the program not to go further
                    currentLetter--;
                }
                generateWord(currentLetter);
            }
        }
    } while (dontExit);

    return 0;
}

void openOutput() {
    // Open the output file
    outputFile.open("../output/ASCII art.txt", fstream::app);
    
    // Get the current time as time_t
    time_t now = time(nullptr);
    // A char[] to use for the formatted time string
    // The length of the string is always 19, and there is always a null value at the end
    char datetime[20];
    // Format string using ISO 8601
    strftime(datetime, 20, "%F %T", localtime(&now));
    
    // Output the date to the output file
    outputFile << datetime << endl;
}

int generateWord(unsigned short numOfChars) {
    ifstream inputFile;
    string fileToOpen;
    string line[5][7]; // Line number, column number, char number
    const string INVALID_CHAR[5] = {"", " Missing ", "Character", " Missing ", "Character"};

    // Read data from all files
    for (int charNum = 0; charNum < numOfChars; charNum++) {
        // Test if the character is one of the invalid file names and use a new name
        switch (inputWord[charNum]) {
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
    
        inputFile.open("../resources/font/"+fileToOpen+".txt"); // Attempt to open the file
        
        // Use "InvalidChar" if the current char is invalid,
        // But skip if the last char is a whitespace or another nonprintable character
        if (!inputFile.is_open()) {
            for (int lineNum = 0; lineNum < 5; lineNum++) {
                line[lineNum][charNum] = INVALID_CHAR[lineNum];
            }
        } else {
            for (int lineNum = 0; lineNum < 5; lineNum++) {
                getline(inputFile, line[lineNum][charNum]);
            }

            inputFile.close();
        }
    }
    
    // Write all data to file
    for (int lineNum = 0; lineNum < 5; lineNum++) {
        for (int charNum = 0; charNum < numOfChars; charNum++) {
                    outputFile << ' ' << line[lineNum][charNum] << ' ';
            }
        outputFile << endl;
    }
    
//     for (int i = 0; i < 5; i++)
//     {
//         cout << 1 << line[i][1] << flush;
//     }
    return 0;
}
