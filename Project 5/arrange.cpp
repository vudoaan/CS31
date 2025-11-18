#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>

using namespace std;

void clearString (char* arr, int length) {
    for (int i = 0; i < length; i++) {
        arr[i] = '\0';
    }
}

int arrange(int lineLength, std::istream& in, std::ostream& out) {
    //Returns 1 if the desired maximum line length is less than 1
    if (lineLength < 1) {
       return 1;
    }

    const int MAX = 120;
    int i, wordLength = 0, wordListIndex = 0, lineLengthIndex = 0, spacesNeeded = 0, returncode = 0;

    bool wordSplitted = false;

    char line[MAX] = "";

    char word[MAX] = "";

    char previousWord [MAX] = "";

    char listOfWords[MAX][MAX] = {""};
    
    while(in.getline(line, MAX)) {
        //std::cout << "This is the current line: " << line << std::endl;
        for (int j = 0; j < wordListIndex; j++) {
            strcpy(listOfWords[j], "");
        }
        wordListIndex = 0;
        clearString(word, wordLength);
        wordLength = 0;
        for (i = 0; i < strlen(line); i++) {
            if (line[i] == '-') {
                word[wordLength] = line[i];
                wordLength++;
                word[wordLength] = '\0'; 
                strcpy(listOfWords[wordListIndex], word);
                wordListIndex++;
                clearString(word, wordLength);
                wordLength = 0;
            } else if (!isspace(line[i])) {
                word[wordLength] = line[i];
                wordLength++;
            } else {
                word[wordLength] = '\0';
                if (wordLength > 0) {
                    strcpy(listOfWords[wordListIndex], word);
                    wordListIndex++;
                }
                clearString(word, wordLength);
                wordLength = 0;
            }
        }
        word[wordLength] = '\0';
        if (strlen(word) != 0 ) {
            strcpy(listOfWords[wordListIndex], word);
            wordListIndex++;
        }
        for (int j = 0; j < wordListIndex; j++) {
            if (j > 0) {
                strcpy(previousWord, listOfWords[j - 1]);
            }
            if (strcmp(listOfWords[j], "<P>") == 0) {
                if (strcmp(listOfWords[j], previousWord) == 0) {
                    continue;
                }  
                if (wordSplitted == true) { 
                    out << '\n'; 
                    lineLengthIndex = 0;
                } else {    
                    out << "\n\n";
                    lineLengthIndex = 0;
                }
            } else {
                if (strlen(listOfWords[j]) >= lineLength) {
                    if (strlen(listOfWords[j]) > lineLength) {
                        returncode = 2;
                    }
                    for (int k = 0; k < spacesNeeded && lineLengthIndex != 0 && strlen(previousWord) + strlen(listOfWords[j]) + spacesNeeded < lineLength; k++) {
                        out << " ";
                        lineLengthIndex++;
                    }
                    for (int k = 0; k < strlen(listOfWords[j]); k++) {
                        if (lineLengthIndex >= lineLength) {
                            out << '\n';
                            lineLengthIndex = 0;
                            clearString(previousWord, lineLength);
                            wordSplitted = true;
                        }
                        previousWord[k] = listOfWords[j][k];
                        out << listOfWords[j][k];
                        lineLengthIndex++;
                    }
                    if (strlen(previousWord) + strlen(listOfWords[j]) > lineLength) {
                        out << '\n';
                        lineLengthIndex = 0;
                    }
                } else {
                    if (previousWord[strlen(previousWord) - 1] == '-') {
                        spacesNeeded = 0;
                    } else if (previousWord[strlen(previousWord) - 1] == '.' || previousWord[strlen(previousWord) - 1] == '?' || previousWord[strlen(previousWord) - 1] == ':') {
                        spacesNeeded = 2;
                    } else {
                        spacesNeeded = 1;
                    }
                    
                    if (lineLengthIndex + spacesNeeded + strlen(listOfWords[j]) <= lineLength) {
                        for (int k = 0; k < spacesNeeded && lineLengthIndex != 0; k++) {
                            out << " ";
                            lineLengthIndex++;
                        }
                        out << listOfWords[j];
                        lineLengthIndex += strlen(listOfWords[j]);
                    } else {
                        out << '\n'; 
                        lineLengthIndex = 0;
                        for (int k = 0; k < spacesNeeded && lineLengthIndex != 0; k++) {
                            out << " ";
                            lineLengthIndex++;
                        }
                        out << listOfWords[j];
                        lineLengthIndex += strlen(listOfWords[j]);
                    }
                    wordSplitted = false;
                }
            }
            if (j == wordListIndex - 1) {
                strcpy(previousWord, listOfWords[j]);
            }
        }
    }
    if (lineLengthIndex > 0) {
        out << '\n';
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

/*
It always does seem to me that I am doing more work than
I should do. It is not that I object to the work, mind you;
I like work: it fascinates me.       I can sit and look at it for hours. oh-my-god-what-the-hell
I love to keep     it by me: the idea of getting
rid
of it nearly breaks my heart. <P> <P> <P> You cannot give me too
much work; to accumulate work has almost become


a passion with me: my study is so full of it now, that there is hardly
an inch of room for any more.
*/

