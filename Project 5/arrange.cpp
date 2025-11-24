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

    //Max input count
    const int MAX = 120;
    //i = tracks the index in the inputline
    //wordLength = tracks the word length in each word
    //wordListIndexs = tracks the number of words in the index
    //spacesNeeded = tracks the amount of spaces needed between words
    //returncode = the returncode that needs to be returned
    int i, wordLength = 0, wordListIndex = 0, lineLengthIndex = 0, spacesNeeded = 0, returncode = 0;

    //Checks if the word is splitted
    bool wordSplitted = false;

    //Input line
    char line[MAX] = "";

    //Word buffer to put in list of words
    char word[MAX] = "";

    //Previous word
    char previousWord [MAX] = "";

    //List of C-strings
    char listOfWords[MAX][MAX] = {""};
    //Checks if the the word portion is part of a bigger word
    bool isContinuation[MAX] = {false};
    
    //Loops through the whole input
    while(in.getline(line, MAX)) {
        //Clears the wordListIndex and isContinuiations of any C Strings and word portions of bigger words
        for (int j = 0; j < wordListIndex; j++) {
            strcpy(listOfWords[j], "");
            isContinuation[j] = false;
        }
        //Clears the word buffer, makes sure everything is reset
        wordListIndex = 0;
        clearString(word, MAX);
        wordLength = 0;
        //inWord makes sure if we're in a word
        //hadPortion checks if we've outputted part of the word already
        bool inWord = false;        
        bool hadPortion = false;    

        //Loops through the input
        for (i = 0; i < strlen(line); i++) {
            //Checks if its a hyphen
            if (line[i] == '-') {
                //If we're not in a word, we're gonna be in a word and we haven't outputted part of the word already
                if (!inWord) {
                    inWord = true;
                    hadPortion = false;
                }
                //Adds the hyphen to the word buffer, increment to the next letter input, and make sure its a null character in case we don't have another hyphen 
                word[wordLength] = line[i];
                wordLength++;
                word[wordLength] = '\0';

                //Sets the first hyphen as not continued as we don't have anything before the hyphen
                isContinuation[wordListIndex] = hadPortion;
                strcpy(listOfWords[wordListIndex], word);
                wordListIndex++;

                //Clears the word buffer and since we've outputted the - to the word list, then set had portion to true
                clearString(word, MAX);
                wordLength = 0;
                hadPortion = true;
            }
            //Checks if the letter is not a space
            else if (!isspace(line[i])) {
                //If we're not in a word, we're gonna be in a word and we haven't outputted part of the word already
                if (!inWord) {
                    inWord = true;
                    hadPortion = false;
                }
                //Adds the letter or puncuation to the word buffer, increment to the next letter input
                word[wordLength] = line[i];
                wordLength++;
            }
            //This means the word is a new line or a space
            else {
                //Checks if we're in a word, and makes sure its not a new line or space
                //hadPortion makes sure that if a word is supposed to be connected, it will later during spacing
                //Copys the word to the word list
                if (inWord && wordLength > 0) {
                    word[wordLength] = '\0';
                    isContinuation[wordListIndex] = hadPortion;
                    strcpy(listOfWords[wordListIndex], word);
                    wordListIndex++;
                    clearString(word, MAX);
                    wordLength = 0;
                }
                //Resets inWord and hadPortion since we flushed the word string
                inWord = false;
                hadPortion = false;
            }
        }

        //The same as in the loop we had
        //Takes care of the edge case of the last word because it doesn't loop through the last letter of the line
        if (inWord && wordLength > 0) {
            word[wordLength] = '\0';
            isContinuation[wordListIndex] = hadPortion;
            strcpy(listOfWords[wordListIndex], word);
            wordListIndex++;
            clearString(word, MAX);
            wordLength = 0;
        }
        //We're done with the word list now loop through the word list
        for (int j = 0; j < wordListIndex; j++) {
            //Sets the previous word to listOfWords[j - 1] but also makes sure that it's not 0
            if (j > 0) {
                strcpy(previousWord, listOfWords[j - 1]);
            }
            //If theres a paragraph header, make a new paragraph, any continuous pargraph headers, will be counted as one pargraph so just iterate to the next loop
            if (strcmp(listOfWords[j], "<P>") == 0) {
                if (strcmp(listOfWords[j], previousWord) == 0) {
                    continue;
                }
                //If the word is already splitted then only add one newline
                if (wordSplitted == true) { 
                    out << '\n'; 
                    lineLengthIndex = 0;
                //If its a whole word then new line twice.
                } else {    
                    out << "\n\n";
                    lineLengthIndex = 0;
                }
            //This means the word is not a paragraph header
            } else {
                //If the word is more than the line length then go into this if statement
                if (strlen(listOfWords[j]) >= lineLength) {
                    //Returns 2 since the word is more than the line length
                    if (strlen(listOfWords[j]) > lineLength) {
                        returncode = 2;
                    }
                    //If the long word is bigger than the line length and theres already a word
                    //Go to the next line
                    if (lineLengthIndex > 0) {
                        out << '\n';
                        lineLengthIndex = 0;
                        clearString(previousWord, MAX);
                    }   
                    //Adds the spaces needed based on 
                    //if the its not the start of the line
                    //and if the previous word, the current word, and the spaces added are less than the line length
                    for (int k = 0; k < spacesNeeded && lineLengthIndex != 0 && strlen(previousWord) + strlen(listOfWords[j]) + spacesNeeded < lineLength; k++) {
                        out << " ";
                        lineLengthIndex++;
                    }
                    //Loops through the overflowing word
                    //Outputs the letters until it hits the line length
                    //When its htis the line length, it goes to the next line, clears the previous word, and the wordSplitted is true now
                    //Resets wordLength so you can track the length of the previousWord
                    wordLength = 0;
                    for (int k = 0; k < strlen(listOfWords[j]); k++) {
                        if (lineLengthIndex >= lineLength) {
                            out << '\n';
                            lineLengthIndex = 0;
                            clearString(previousWord, MAX);
                            wordLength = 0;
                            wordSplitted = true;
                        }
                        previousWord[wordLength] = listOfWords[j][k];
                        wordLength++;
                        out << listOfWords[j][k];
                        lineLengthIndex++;
                    }
                    previousWord[wordLength] = '\0';
                //The word is less than the line length
                } else {
                    /*Spacing Guide
                        - no spaces at start of line
                        - no spaces within a word (continuations)
                        - 2 spaces after . ? :
                        - 1 space otherwise 
                    */
                    //Checks if the the starting of the line or if its a continuation of a word, if it is no spaces are needed
                    if (lineLengthIndex == 0 || isContinuation[j]) {
                        spacesNeeded = 0;
                    //Then this means that we're in the middle of the line length and we're at a completely new word
                    } else {
                        //If its a ., ?, or : then you need 2 spaces and the previous word is not nothing
                        if (strlen(previousWord) > 0 && (previousWord[strlen(previousWord) - 1] == '.' || previousWord[strlen(previousWord) - 1] == '?' || previousWord[strlen(previousWord) - 1] == ':')) {
                            spacesNeeded = 2;
                        //Other than that you have one space only
                        } else {
                            spacesNeeded = 1;
                        }
                    }

                    //Checks if the line length index + the spaces needed + the current word length is less than the line length
                    //If so add the spaces because it's a valid combnations
                    if (lineLengthIndex + spacesNeeded + strlen(listOfWords[j]) <= lineLength) {
                        for (int k = 0; k < spacesNeeded && lineLengthIndex != 0; k++) {
                            out << " ";
                            lineLengthIndex++;
                        }
                        out << listOfWords[j];
                        lineLengthIndex += strlen(listOfWords[j]);
                    //Otherwise start a new line and then output the word
                    } else {
                        out << '\n'; 
                        lineLengthIndex = 0;
                        out << listOfWords[j];
                        lineLengthIndex += strlen(listOfWords[j]);
                    }
                    //Resets the word splitted 
                    wordSplitted = false;
                }
            }
            //When theres a new line seperating the previous word and the current word
            //This makes sure that the last word in the last line is captured in the previousWord string so that we can use it to see how many spaces we need
            if (j == wordListIndex - 1) {
                strcpy(previousWord, listOfWords[j]);
            }
        }
    }
    //If there isn't a new line already then add a new line
    if (lineLengthIndex > 0) {
        out << '\n';
    }
    //Returns the code number
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
