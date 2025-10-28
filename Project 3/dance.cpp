#include <iostream>
#include <string>
#include <cassert>

bool isvalidDirection(char direction) {
    switch (direction) {
            case 'u':
            case 'U':
            case 'd':
            case 'D':
            case 'l':
            case 'L':
            case 'r':
            case 'R':
                break;
            default:
                return false;
    }
    return true;
}


bool isSyntacticallyCorrect(std::string dance) {
    //Count for the index where we're at in the string
    std::size_t i = 0, stringSize = dance.size();
    //Checks if string is empty
    if (stringSize == 0)
        return true;
    while (i < stringSize)  {
        //Checks if string at index i is a valid direction, digit, or beat, return false if it isn't
        if (!isvalidDirection(dance.at(i)) && !isdigit(dance.at(i)) && dance.at(i) != '/') {
            return false;
        }
        //Checks if string at index i the empty beat, if yes then continue
        else if (dance.at(i) == '/') {
            i++;
        }
        //Checks if string at index i is a valid direction
        else if (isvalidDirection(dance.at(i))) {
            //Checks if string at index i + 1 is a valid direction followed by a beat, if yes then continue
            if (i < stringSize - 1 && dance.at(i + 1) == '/') {
                i += 2;
            //If string at index i + 1 is a direction but not followed by a beat, return false because it is wrong syntactically
            } else {
                return false;
            } 
        }
        //Checks if string at index i is a digit
        else if (isdigit(dance.at(i))) {
            //Checks if string at index i + 1 is a digit followed by another digit
            if (i < stringSize - 1 && isdigit(dance.at(i + 1))) {
                //Checks if string at index i + 2 is a digit followed by another digit followed by a valid direction
                if (i < stringSize - 2 && isvalidDirection(dance.at(i + 2))) {
                    //Checks if string at index i + 3 is a digit followed by another digit followed by a valid direction followed by a beat, if yes then continue
                    if (i < stringSize - 3 && dance.at(i + 3) == '/') {
                        i+=4;
                    //If string at index i + 3 is a digit followed by another digit followed by valide direction but not followed by a beat, return false because it is wrong syntactically
                    } else {
                        return false;
                    }
                //If string at index i + 2 is a digit followed by another digit but not followed by a valid direction, return false because its wrong syntactically
                } else {
                    return false;
                }
            }
            //Checks if string at index i + 1 is a digit followed by a direction
            else if (i < stringSize - 1 && isvalidDirection(dance.at(i + 1))) {
                //Checks if string at index i + 2 is a digit followed by a direciton followed by a beat, if yes then continue
                if (i < stringSize - 2 && dance.at(i + 2) == '/') {
                    i += 3;
                //If string at index i + 2 is a digit followed by a direction but not followed by a beat, return false because its wrong syntactically
                } else {
                    return false;
                }
            //If string at index i + 1 is a digit but not followed by another digit or a valid direction, return false because its wrong syntactically
            } else {
                return false;
            }
        }
    }
    //Only true if everything is syntactically correct
    return true;
}

int translateDance(std::string dance, std::string& instructions, int& badBeat) {
    std::string originalInstructions = instructions;
    instructions = "";
    std::size_t i = 0, stringSize = dance.size();
    int freezeCount = 0, freezeAmount = 0, beatCount = 0;
    char direction;
     
    //Checks if the dance is syntactically correct using the isSyntacticallyCorrect() function, if false, return 1
    if (isSyntacticallyCorrect(dance) == false)
        return 1;
    while (i < stringSize) {
        freezeCount = 0, freezeAmount = 0;
        std::cerr << "In loop" << std::endl;
        if (isdigit(dance.at(i))) {
            std::cerr << "1st digit" << std::endl;
            if (isdigit(dance.at(i + 1))) {
                std::cerr << "2nd digit" << std::endl;
                freezeAmount = ((dance.at(i) - '0') * 10) + (dance.at(i + 1) - '0');
                direction = dance.at(i + 2);
                if (freezeAmount < 2) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 2;
                }
                i += 3;
                for (int j = i; j < freezeAmount + i && j < stringSize; j++) {
                    std::cerr << j << ":" << dance.at(j) << std::endl;
                    instructions += toupper(direction);
                    if (dance.at(j) != '/') {
                        instructions = originalInstructions;
                        badBeat = beatCount + 1; 
                        return 3;
                    }
                    beatCount++;
                    freezeCount++;
                }
                std::cerr << i << std::endl;
                std::cerr << freezeCount << freezeAmount << std::endl;
                if (freezeCount != freezeAmount) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 4;
                } else if(i != stringSize) {
                    i+= freezeAmount;
                }
            } else {
                std::cerr << "Only one digit" << std::endl;
                freezeAmount = dance.at(i) - '0';
                direction = dance.at(i + 1);
                if (freezeAmount < 2) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 2;
                }
                i+= 2;
                for (int j = i; j < freezeAmount + i && j < stringSize; j++) {
                    instructions += toupper(direction);
                    if (dance.at(j) != '/') {
                        instructions = originalInstructions;
                        badBeat = beatCount + 1; 
                        return 3;
                    }
                    beatCount++;
                    freezeCount++;
                }
                if (freezeCount != freezeAmount) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 4;
                } else if(i != stringSize) {
                    i+= freezeAmount;
                }
            }
        } else if (isvalidDirection(dance.at(i))) {
            instructions += tolower(dance.at(i));
            beatCount++;
            i += 2;
        } else {
            instructions += '.';
            i++;
        }
        std::cerr << "Index at end: " << i << std::endl;
    }
    //The string dance is translateable and returns 0
    return 0;
}

int main()
    {
        std::string instructions = "errorrrrrr";
        int badBeat = -999;
        int returnCode = translateDance("d/3r//u/0d//2u/", instructions, badBeat);
        //std::cerr << std::boolalpha << isSyntacticallyCorrect("10r//////////") << std::endl;
        std::cerr << "Return Code: " << returnCode << std::endl << "Instructions: " << instructions << std::endl << "Bad Beat: " << badBeat << std::endl;
        //std::cerr << ('3' - '0') * 10 + ('3' - '0') << std::endl;
        return 0;
    }