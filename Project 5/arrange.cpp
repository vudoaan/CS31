#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

void clearString (char* arr, int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = '\0';
    }
}

bool seperateHyphen (char* arr, int ) {



    return true;
}

int arrange(int lineLength, std::istream& in, std::ostream& out) {
    //Returns 1 if the desired maximum line length is less than 1
    if (lineLength < 1) {
       return 1;
    }

    const int MAX = 120;
    int i, wordLength = 0, wordListIndex = 0, lineLengthIndex = 0, spacesNeeded = 0, returncode = 0;

    bool haveOutput = false; 

    char line[MAX] = "";

    char word[MAX] = "";

    char previousWord [MAX] = "";

    char listOfWords[MAX][MAX] = {""};

    char seperatedHyphen[MAX][MAX] = {""};
    
    while(in.getline(line, MAX)) {
        //std::cout << "This is the current line: " << line << std::endl;
        for (int j = 0; j < wordListIndex; j++) {
            strcpy(listOfWords[j], "");
        }
        wordListIndex = 0;
        clearString(word, wordLength);
        wordLength = 0;
        for (i = 0; i < strlen(line); i++) {
            if (!isspace(line[i])) {
                word[wordLength] = line[i];
                wordLength++;
            }
            if (isspace(line[i])) {
                word[wordLength] = '\0';
                if (wordLength > 0) {
                    strcpy(listOfWords[wordListIndex], word);
                    wordListIndex++;
                }
                //out << word << "\n";
                clearString(word, wordLength);
                wordLength = 0;
            }
        }
        //out << word << "\n";
        word[wordLength] = '\0';
        strcpy(listOfWords[wordListIndex], word);
        wordListIndex++;
        //out << wordListIndex;
        for (int j = 0; j < wordListIndex; j++) {
            if (j > 0 && (strcmp(listOfWords[j - 1], "") != 0 && strcmp(listOfWords[j - 1], " ") != 0 && strcmp(listOfWords[j - 1], "\n") != 0)) {
                strcpy(previousWord, listOfWords[j - 1]);
            }
            if (false) {

            } else if (strcmp(listOfWords[j], "<P>") == 0) {
                if (lineLengthIndex > 0) {
                    out << '\n';
                    lineLengthIndex = 0;
                    haveOutput = true;
                }
                
                if (haveOutput) {
                    out << "\n";
                    haveOutput = false;
                }
                lineLengthIndex = 0;
                clearString(previousWord, strlen(listOfWords[j]));
                continue;
            } else {
                if (strlen(listOfWords[j]) > lineLength) {
                    returncode = 2;
                    for (int k = 0; k < spacesNeeded && lineLengthIndex != 0 && strlen(previousWord) + strlen(listOfWords[j]) + spacesNeeded < lineLength; k++) {
                        out << "*";
                        lineLengthIndex++;
                    }
                    if (strlen(previousWord) + strlen(listOfWords[j]) > lineLength) {
                        out << '\n';
                        lineLengthIndex = 0;
                    }
                    for (int k = 0; k < strlen(listOfWords[j]); k++) {
                        if (lineLengthIndex >= lineLength) {
                            out << '\n';
                            lineLengthIndex = 0;
                            clearString(previousWord, lineLength);
                        }
                        previousWord[k] = listOfWords[j][k];
                        out << listOfWords[j][k];
                        haveOutput = true;
                        lineLengthIndex++;
                    }
                } else { 
                    if (previousWord[strlen(previousWord) - 1] == '.' || previousWord[strlen(previousWord) - 1] == '?' || previousWord[strlen(previousWord) - 1] == ':') {
                        spacesNeeded = 2;
                    } else {
                        spacesNeeded = 1;
                    }
                    
                    if (lineLengthIndex + spacesNeeded + strlen(listOfWords[j]) <= lineLength) {
                        for (int k = 0; k < spacesNeeded && lineLengthIndex != 0; k++) {
                            out << "*";
                            lineLengthIndex++;
                        }
                        out << listOfWords[j];
                        haveOutput = true;
                        lineLengthIndex += strlen(listOfWords[j]);
                        //out << lineLengthIndex;
                    } else {
                        out << '\n';
                        returncode = 2;
                        lineLengthIndex = 0;
                        for (int k = 0; k < spacesNeeded && lineLengthIndex != 0; k++) {
                            out << "*";
                            lineLengthIndex++;
                        }
                        out << listOfWords[j];
                        haveOutput = true;
                        lineLengthIndex += strlen(listOfWords[j]);
                        //out << lineLengthIndex;
                    }
                }
                if (j == wordListIndex - 1) {
                    strcpy(previousWord, listOfWords[j]);
                }
            }
            if (j > 0 && (strcmp(listOfWords[j - 1], "") != 0 && strcmp(listOfWords[j - 1], " ") != 0 && strcmp(listOfWords[j - 1], "\n") != 0) && strcmp(listOfWords[j], "<P>") != 0) {
                    strcpy(previousWord, listOfWords[j - 1]);
            }
        }
    }
    return returncode;
}

int main () {
    const int MAX_FILENAME_LENGTH = 100;
        std::cout << "Enter input file name (or q to quit): ";
        char filename[MAX_FILENAME_LENGTH];
        std::cin.getline(filename, MAX_FILENAME_LENGTH);
        std::ifstream infile(filename);
        if (!infile)
        {
            std::cerr << "Cannot open " << filename << "!" << std::endl;
            return 1;
        }
        std::cout << "Enter maximum line length: ";
        int len;
        std::cin >> len;
        std::cin.ignore(10000, '\n');
        int returnCode = arrange(len, infile, std::cout);
        std::cout << "Return code is " << returnCode << std::endl;
}