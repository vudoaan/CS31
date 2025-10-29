#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

//Function that checks if the character is a valid direction
bool isValidDirection(char direction) {
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
    //Loops the string until the dance is finished
    while (i < stringSize)  {
        //Checks if string at index i is a valid direction, digit, or beat, return false if it isn't
        if (!isValidDirection(dance.at(i)) && !isdigit(dance.at(i)) && dance.at(i) != '/') {
            return false;
        }
        //Checks if string at index i the empty beat, if yes then continue
        else if (dance.at(i) == '/') {
            i++;
        }
        //Checks if string at index i is a valid direction
        else if (isValidDirection(dance.at(i))) {
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
                if (i < stringSize - 2 && isValidDirection(dance.at(i + 2))) {
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
            else if (i < stringSize - 1 && isValidDirection(dance.at(i + 1))) {
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
    //This makes sure that all dances beyond this point is syntactically correct and has the ability to be translated
    if (isSyntacticallyCorrect(dance) == false) {
        instructions = originalInstructions;
        return 1;
    }    
    //Loops the string one section at a time
    while (i < stringSize) {
        //Resets the freeze counter and freeze amount every section is iterates through
        freezeCount = 0, freezeAmount = 0;
        //Checks if the chraracter at index i is a digit
        if (isdigit(dance.at(i))) {
            //Checks if the section at index i + 1 is a digit followed by another digit
            //Index i + 1 can not be out of range because if there is a digit it has to be followed by a direction and a beat or another digit, a direction, and a beat
            if (isdigit(dance.at(i + 1))) {
                //Turns string into int of 1st and 2nd digit
                freezeAmount = ((dance.at(i) - '0') * 10) + (dance.at(i + 1) - '0');
                //Sets direction to current direction to be able to translate it
                direction = dance.at(i + 2);
                //If the freeze is less than 2, return 2 and the bad beat index
                if (freezeAmount < 2) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 2;
                }
                //Adds 3 to index to iterate past the two digits and direction
                i += 3;
                //Loops for the set freeze amount
                //If there is a direction or digit instead of a beat it will return 3 and set the bad beat to that number
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
                //If there is not the correct amount of beats that is supposed to be there then return 4 and set the bad beat to one more than the number of beats in the string
                if (freezeCount != freezeAmount) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 4;
                } else {
                    i+= freezeAmount;
                }
            //If index i + 1 is not a digit it must be a direction followed by a beat
            } else {
                //Turns string into int of 1st digit
                freezeAmount = dance.at(i) - '0';
                //Sets direction to current direction to be able to translate it
                direction = dance.at(i + 1);
                //If the freeze is less than 2, return 2 and the bad beat index
                if (freezeAmount < 2) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 2;
                }
                //Adds 2 to index to iterate past the digit and direction
                i+= 2;
                //Loops for the set freeze amount
                //If there is a direction or digit instead of a beat it will return 3 and set the bad beat to that number
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
                //If there is not the correct amount of beats that is supposed to be there then return 4 and set the bad beat to one more than the number of beats in the string
                if (freezeCount != freezeAmount) {
                    instructions = originalInstructions;
                    badBeat = beatCount + 1;
                    return 4;
                } else {
                    i+= freezeAmount;
                }
            }
        //Checks if index at i is a direction
        } else if (isValidDirection(dance.at(i))) {
            //Adds the direction to the instructions
            instructions += tolower(dance.at(i));
            beatCount++;
            //Adds 2 to index to iterate past the direction and beat
            i += 2;
        //If the index at i is not a digit or a direction, it is a beat
        } else {
            //Adds the beat to the instructions
            instructions += '.';
            //Adds 1 to index to iterate past the beat
            i++;
        }
    }
    //The string dance is translateable and returns 0
    return 0;
}

int main()
    {
        assert(isSyntacticallyCorrect("d/u//"));
        assert(!isSyntacticallyCorrect("d/z//"));
        std::string ins;
        int bb;
        ins = "WOW";
        bb = -999;
        std::cerr << "Return Code: " << translateDance("u//d/3r///d/", ins, bb) << std::endl << "Instructions: " << ins << std::endl << "Bad Beat: " << bb << std::endl;
        ins = "WOW";  // so we can detect whether translateDance sets ins
        bb = -999;    // so we can detect whether translateDance sets bb
        assert(translateDance("u//d/3r///d/", ins, bb) == 0  &&  ins == "u.dRRRd"  &&  bb == -999);
        ins = "WOW";  // so we can detect whether translateDance sets ins
        bb = -999;    // so we can detect whether translateDance sets bb
        assert(translateDance("5r//", ins, bb) == 4  &&  ins == "WOW"  &&  bb == 3);
        ins = "WOW";
        bb = -999;
        assert(translateDance("d/3r//0d/", ins, bb) == 2 || translateDance("d/3r//0d/", ins, bb) == 3 && ins == "WOW" && bb == 4);
        ins = "WOW";
        bb = -999;
        assert(translateDance("d0d/", ins, bb) == 1 && ins == "WOW" && bb == -999);
        std::cerr << std::boolalpha << isSyntacticallyCorrect("d0d/") << std::endl;
        std::cerr <<"All tests succeeded" << std::endl;
    }