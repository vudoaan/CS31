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
    std::size_t i = 0;
    std:: size_t stringSize = dance.size();
    //Checks if string is empty
    if (dance.size() == 0)
        return true;
    while (i < dance.size())  {
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

/*int translateDance(std::string dance, std::string& instructions, int& badBeat) {
    int beatCount = 0;
    return 0;
    return 1;
    return 2;
    return 3;
    return 4;
} */

int main()
    {
        std::cerr << "Hello" << std::endl;
        std::cerr << std::boolalpha <<isSyntacticallyCorrect("u/3r///3d///") << std::endl;
    }