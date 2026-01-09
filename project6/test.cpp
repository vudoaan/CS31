#include <iostream>
using namespace std;

void removeS (char* str) {
    //str acts as a writer 
    char* index = str; //Index is what character we are currently reading
    while (*index != 0) { //Loops through the whole c-string until we see a zero byte
        if (*index != 's' && *index != 'S') { //If it is not a s or S then we write the char and increment str
            *str = *index;
            str++;
        }
        index++; //we always increment index as we always want to read
    }
    //Make sure to end the string with a zero byte after we removed all the s and S
    *str = 0;
}


int main()
{
        char msg[50] = "She'll blossom like a massless princess.";
        removeS(msg);
        cout << msg;  // prints   he'll bloom like a male prince.
}