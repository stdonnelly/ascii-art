/*
stdonnelly
Version 1 Project start date:
8/30/2016
Version 2 Project start date:
11/18/2016
Last edit:
11/23/2016
*/
// EDIT: The above is not correct, last edit was 2021-10-26

#include <iostream>
#include <fstream>
// #include <windows.h>
// EDIT: I don't want to use windows.h if I can avoid it
#include <string>
#include <ctime>
// EDIT: There was some header file I made for myself here

using namespace std;

// Global variables
#define INVALID_CHAR_FILE "../resources/font/(InvalidChar).txt"
// EDIT: File location was changed
ofstream outputFile;
char inputWord[7];


int generateWord(unsigned short);// The heart of the program
char openChar(char);

// TODO: I can has English
bool inputFileNoExist() // Test for "(InvalidChar).txt"
{
    ifstream invalidCharOpenTest(INVALID_CHAR_FILE);

    if (!(invalidCharOpenTest)) // If "(InvalidChar).txt" does not exist
    {
        cout << "ERROR\n";
        cout << "The program couldn't find \"(InvalidChar).txt\" in the specified location:\n";
        cout << "\"" << INVALID_CHAR_FILE << "\".\n";
        cout << "The program will now exit.\n";
        // EDIT: There was a sleep function here
        return 1;
    }
    else
    {
        invalidCharOpenTest.close();
        return 0;
    }
}

void openOutput()
{
    outputFile.open("../output/ASCII art.txt", fstream::app); // Open the output file
    // EDIT: File location was changed
    
    // EDIT: The code to find the current datetime was something I probably copy/pasted instead of understanding
    // The following is much easier to use and uses a standard datetime format:
    
    // Get the current time as time_t
    time_t now = time(nullptr);
    // A char[] to use for the formatted time string
    // The length of the string is always 19, and there is always a null value at the end
    char datetime[20];
    // Format string using ISO 8601
    strftime(datetime, 20, "%F %T", localtime(&now));

    outputFile << datetime << endl; // Output the date to the output file
}

int main()
{
    // TODO Go through program and fix inconsistent comment style
    // SetConsoleTitle("ASCII art text generator"); //Change title of CMD window
    // EDIT: That was a windows.h function

    if (inputFileNoExist())
        return 0;

    bool dontExit = 1;
    unsigned short currentLetter;

    // EDIT: windows.h functions 
    // CreateDirectory("../Program outputs", NULL);
    // CreateDirectory("../Program outputs/ASCII art text generator", NULL); // Make sure that the directory exists

    openOutput();

    //User instructions
    // #include "../printLongText/ASCII art 01.txt.incl"
    // EDIT 2021-10-08: This is what that file contained:
    // TODO: This is unreadable
    puts("This is a tool to convert text into:\n            ___     ___   _____  _____                 ___    _____    \n    /\\     /   \\   /   \\    |      |           /\\     |   \\     |    |\n   /__\\    \\___   |         |      |          /__\\    |___/     |    |\n  /    \\       \\  |         |      |         /    \\   |   \\     |    |\n /      \\  \\___/   \\___/  __|__  __|__      /      \\  |    \\    |    .\nHow to use:\nType the text that you wish to convert.\nMax word size: 7\nAny higher and program will put the rest on the next line.\nIf you have already used this program,\nIt will put the ASCII art right after the last used session.\n(Note: Does not work for every font,\n\"Courier New\" or \"Consolas\" is recomended\nfor viewing output text. No others have been tested.)\nCommands (~save, yes, no) are case sensitive.\nHowever, input text is not case sensative.\nThis will always output capital letters.\nPlease type your text.\nType \"~save\" to finish.");

    do // This will loop until the user is finished
    {
        // TODO Why is there a dontExit2? I think I made spaghetti with this one
        bool dontExit2 = 1;

        currentLetter = 0; //Make sure that the letter starts out as 0

        // TODO There has to be a better way to do this. Perhaps string converted to char[]?
        cin >> noskipws;
        while ((currentLetter < 7) && (inputWord[(currentLetter - 1)] != ' ') && (inputWord[(currentLetter - 1)] != '\n'))
        {
            cin >> inputWord[currentLetter++]; //Recieve current letter, then increment it
        }
        cin >> skipws;

        if (!((inputWord[0] == '\n') || (inputWord[0] == ' ')))
        {
            // Find out if inputWord is "~save"
            if ((inputWord[0] == '~') &&
                (inputWord[1] == 's') &&
                (inputWord[2] == 'a') &&
                (inputWord[3] == 'v') &&
                (inputWord[4] == 'e'))
            {
                string ext;

                while (dontExit2) // TODO There has to be a better way to make an input loop
                {
                    outputFile << endl << endl;
                    outputFile.close(); // Close the output file

                    cout << endl;
                    cout << "Finished saving file\n";

                    cout << "Would you like to exit?\n"; // Ask the user if they would like to finish
                    cout << "Type \"yes\" for yes, or \"no\" for no\n";
                    cin >> ext;

                    if (ext == "yes")
                    {
                        dontExit = 0;
                        dontExit2 = 0;
                    }
                    else if (ext == "no")
                    {
                        dontExit2 = 0;
                        openOutput();
                    }
                    else
                    {
                        cout << "Invalid input\n";
                    }
                }
            }
            else
            {
                if ((inputWord[currentLetter - 1] == ' ') || (inputWord[currentLetter - 1] == '\n'))
                {
                    // Remove whitespace by telling the rest of the program not to go further
                    currentLetter--;
                }
                generateWord(currentLetter);
            }
        }
    }
    while (dontExit);

    // EDIT: There was some code here to call a function from a header and display program info.
    // No idea why I did that.

    //Pause the console window before exiting
    // EDIT: No, pausing here is stupid, there is no reason not to just termiate and write silently
    // EDIT: This was a bandaid for a broken sleep function: cin.ignore();
    // EDIT: There was a header function called sleep()
    return 0;
}

// EDIT: Based on how numOfChars is the only argument, I probably abused global variables
// EDIT: Added int
int generateWord(unsigned short numOfChars)
{
    ifstream inputFile;
    string fileToOpen;
    string line[5][7]; // Line number, column number, char number

    //Read data from all files
    for (unsigned short charNum; charNum < numOfChars; charNum++)
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
            // TODO: I could either make lowercase ASCII art, or I could make the file opening case-insensitive
            // Probably the latter
    }
        inputFile.open("../resources/font/"+fileToOpen+".txt"); // Attempt to open the file
        // EDIT: Changed file location

        //Use "InvalidChar" file if the current char is invalid,
        //But skip if the last char is a whitespace or another nonprintable character
        if (!inputFile.is_open())
        {
            inputFile.open(INVALID_CHAR_FILE);
        }

        for (unsigned short lineNum = 0; lineNum < 5; lineNum++)
        {
            getline(inputFile, line[lineNum][charNum]);
        }

        inputFile.close();
    }
    
    // Write all data to file
    // EDIT: Why did I have such an obsession with unsigned short. int would be fine here
    for (unsigned short lineNum = 0; lineNum < 5; lineNum++)
    {
        for (unsigned short charNum = 0; charNum < numOfChars; charNum++)
            {
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
