#include <iostream>
#include <cassert>
#include <string>

int repeat(std::string a[], int n) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size
    if (n < 0) {
        return -1;
    }
    //Loops through array and appends the element to itself to get a twice repeated string
    for (int i = 0; i < n; i++) {
        a[i] += a[i]; 
    }
    //Returns the amount of indicies affected
    return n;
}

int detectMatch(const std::string a[], int n, std::string target) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size
    if (n <= 0) {
        return -1;
    }
    //Loops through the array and checks if target is an index in it
    //If found then return the index of the first occuring instance
    //If not found then return -1
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    //Returns -1 if it can't find a match for target in the array
    return -1;
}

int detectMax(const std::string a[], int n) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size or examines no elements in the array
    if (n <= 0) {
        return -1;
    }
    //Sets the starting string comparison to the first string
    int latest = 0;
    //Loops through array
    for (int i = 1; i < n; i++) {
        //If string of array[i] is bigger array[latest] then set i to latest
        if (a[i] > a[latest]) {
            latest = i;
        }
    }
    //Return the biggest string alphabetically
    return latest;
}

//Extra Credit Question (No extra array)
int circleLeft(std::string a[], int n, int pos) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size or examines no elements in the array
    //Checks if passed argument position than array size
    //Checks if passed arguement positiion is negative
    if (n <= 0 || pos >= n || pos < 0) {
        return -1;
    }
    //Creates the temporary string at array[pos] so that it can be inserted later after everything is circled left
    std::string temp = a[pos];
    //Loops through the array and when it hits the position that was eliminated, start moving eveything to the left
    //Stops moving left at i - 1 to leave room for the eliminated string at array[pos]
    for (int i = pos; i < n - 1; i++) { 
        a[i] = a[i + 1];
    }
    //After everything is moved, replace the last index with string at array[pos]
    a[n - 1] = temp;
    //Return the position where string at array[pos] was elimnated
    return pos;
}

int enumerateRuns(const std::string a[], int n) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size
    if (n < 0) {
        return -1;
    //Checks if no elements are examined in the array, if so return so because no runs are in an empty sequence
    } else if (n == 0) {
        return 0;
    }
    //Makes the first sequence the first index of the string
    std::string currentString = a[0];
    //Counter for sequences in the array
    int counter = 1;
    //Loops through the array and checks if the next string is identical
    //If not identical then make the new sequence the stirng at array[i] and add one the counter as there is a new sequence
    for (int i = 1; i < n; i++) {
        if (a[i] != currentString) {
            currentString = a[i];
            counter++;
        }
    }
    //Returns the count of sequences in the array
    return counter;
}

//Extra Credit Question (No extra array)
int flip(std::string a[], int n) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size
    if (n < 0) {
        return -1;
    }
    std::string temp;
    //Loops through array and flips elements
    //Store current string to temp, set the current string to opposing indexed string, and then set the flipped string to the stored string
    //Stops at n/2 because you only need to half of the array for it to be flipped and if odd indexed, middle string doesn't need to be flipped
    for (int i = 0; i < n/2; i++) {
        temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
    //Returns the number of elements flipped
    return n;
}

int detectDifference(const std::string a1[], int n1, const std::string a2[], int n2) {
    //Bad Argument Checks returns -1
    //Checks if passed arguements n1 or n2 are negative array sizes
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    //Loops through the array and checks if the theres a difference between the the indicies
    //If there is return i because that's where the difference starts
    for (int i = 0; i < n1 && i < n2; i++) {
        if (a1[i] != a2[i]) {
            return i;
        }
    }
    //Checks which array ends first and returns the shorter array size
    //If n1 ended first return n1 or both ended at the same time return n1
    //If n2 ended first return n2
    if (n1 <= n2) {
        return n1;
    } else {
        return n2;
    }  
}

int subsequence(const std::string a1[], int n1, const std::string a2[], int n2) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n1 and n2 are negative array sizes
    //Checks if n2 is bigger than n1 because thats not possible
    if (n1 < 0 || n2 < 0 || n1 < n2) {
        return -1;
    //If n2 == 0 then the subsequence starts at the first element so return 0
    } else if (n2 == 0) {
        return 0;
    }
    int j;
    //Loops through the array and checks if all elements in n2 appear in n1
    for (int i = 0; i < n1; i++) {
        //Checks for the starting element of n2 in n1
        //If there is continue
        if (a2[0] == a1[i]) {
            //Checks for the rest of the elements of n2 in n1
            //Bounds of the length of n1 and n2, whichever comes first
            //If there is a different element break from the loop
            for (j = 1; j < n2 && i + j < n1; j++) {
                if (a2[j] != a1[i+j]) {
                    break;
                }
            }
            //Checks if the amount of elements in n2 is in n1
            //If so return the index where ti starts
            if (j == n2) {
                return i;
            }
        }
    }
    //Returns -1 if it doesn't find a subsequence
    return -1;
}

int detectAny(const std::string a1[], int n1, const std::string a2[], int n2) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n1 and n2 are negative array sizes
    if (n1 < 0 || n2 <= 0) {
        return -1;
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (a1[i] == a2[j]) {
                return i;
            }
        }
    }
    return -1;
}
//Questions
//Extra Credit Question (No extra array)
//Alphabetical Question
int split(std::string a[], int n, std::string splitter) {
    //Bad Argument Checks returns -1
    //Checks if passed arguement n is a negative array size
    //Checks if passed argument n is 0, you split 0 strings so the split starts at 0
    if (n < 0) {
        return -1;
    } else if (n == 0) {
        return 0;
    }
    //Temp variable to swap
    std::string temp;
    //counter keeps track of the index at which the split starts
    int counter = 0;
    //Loops through the array and sees the first index that is not < splitter
    for (int i = 0; i < n ;i++) {
        if (a[i] < splitter) {
            temp = a[i];
            a[i] = a[counter];
            a[counter] = temp;
            counter++;
        }
    }
    //Return where the split started
    return counter;
}

int main () {
    //Test for function repeat
    std::cerr << '\n' << "Test for function repeat\n---\n";
    std::string stuff[6] = { "mahi", "bon", "cous", "", "tar", "mur" };
    int aa = repeat(stuff, 6);
    std::cerr << aa << '\n' << stuff[4] << '\n' << "\nTest for function dectectMatch\n---\n";

    //Test for function dectectMatch
    std::string guys[9] = {"teoscar", "tyler", "max", "max", "will", "will", "will", "max", "max"};
    int bb = detectMatch(guys, 7, "will"); // returns 4
    std::cerr << bb << '\n'; 
    int cc = detectMatch(guys, 4, "miguel"); // returns -1 (no "miguel" in first 4)
    std::cerr << cc << '\n' << "\nTest for function detectMax\n---\n";

    //Test for detectMax
    std::string people[5] = { "freddie", "will", "shohei", "yoshi", "mookie" };
    int dd = detectMax(people, 5);  // returns 3, since  yoshi  is latest
    std::cerr << dd << '\n' << "\nTest for function circleLeft\n---\n";

    //Test for function circleLeft
    std::string folks[5] = { "will", "shohei", "freddie", "miguel", "max" };
    int ee = circleLeft(folks, 5, 1);  // returns 1 // folks now contains:  "will", "freddie", "miguel", "max", "shohei"
    for (int i = 0; i < 5; i++) {
        std::cerr << folks[i] << ' ';
    }
    std::cerr << '\n' << ee << '\n' << "\nTest for function enumerateRuns\n---\n";

    //Test for function enumerateRuns
    int ff = enumerateRuns(guys, 9);  //  returns 5
           //  The five sequences of consecutive identical items are
           //    "teoscar"
           //    "tyler"
           //    "max", "max"
           //    "will", "will", "will"
           //    "max", "max"
    std::cerr << ff << '\n' << "\nTest for function flip\n---\n";

    //Test for function flip
    std::string blue[6] = { "tyler", "andy", "", "blake", "max", "enrique"};
    int gg = flip(blue, 4);  // returns 4 // blue now contains:  "blake"  ""  "andy"  "tyler"  "max"  "enrique"
    for (int i = 0; i < 6; i++) {
        std::cerr << blue[i] << ' ';
    }
    std::cerr << '\n' << gg << '\n' << "\nTest for function detectDifference\n---\n";

    //Test for function dectectDifference
    std::string players[6] = { "freddie", "will", "blake", "yoshi", "mookie", "shohei" };
    int hh = detectDifference(people, 5, players, 6);  //  returns 2
    int ii = detectDifference(people, 2, players, 1);  //  returns 1
    std::cerr << hh << '\n' << ii << '\n' << "\nTest for function subsequence\n---\n";

    //Test for function subsequence
    std::string dodgers[10] = { "alex", "shohei", "andy", "mookie", "enrique", "tommy" };
    std::string dodgers1[10] = { "shohei", "andy", "mookie" };
    int jj = subsequence(dodgers, 6, dodgers1, 3);  // returns 1
    std::string dodgers2[10] = { "alex", "mookie" };
    int kk = subsequence(dodgers, 5, dodgers2, 2);  // returns -1
    std::cerr << jj << '\n' << kk << '\n' << "\nTest for function detectAny\n---\n";
    
    //Test for function detectAny
    std::string set1[10] = { "enrique", "emmet", "mookie", "shohei"};
    int ll = detectAny(dodgers, 6, set1, 4);  // returns 1 (a1 has "shohei" there)
    std::string set2[10] = { "clayton", "justin" };
    int mm = detectAny(dodgers, 6, set2, 2);  // returns -1 (a1 has none)
    std::cerr << ll << '\n' << mm << '\n' << "\nTest for function split\n---\n";

    //Test for function split
    std::string champs[9] = { "blakaee", "shohei", "blake", "will", "freddie", "yoshi", "max", "blakee", "well" };
    int nn = split(champs, 9, "miguel");  //  returns 5
    for (int i = 0; i < 9; i++) {
        std::cerr << champs[i] << ' ';
    }
    std::cerr << '\n';
    std::string champs1[3] = { "blake", "blakaee", "blakee"};
    int oo = split(champs1, 3, "blakaeee"); // returns 1
    for (int i = 0; i < 3; i++) {
        std::cerr << champs1[i] << ' ';
    }
    // champs must now be
    //      "max"  "blake"  "freddie"  "yoshi"  "will"  "shohei"
    // or   "blake"  "freddie"  "max"  "shohei"  "yoshi"  "will"
    // or one of several other orderings.
    // All elements < "miguel" (i.e., "blake", "freddie", and "max")
    //   come before all others
    // All elements > "miguel" (i.e., "will"  "yoshi", and "shohei")
    //   come after all others
    std::string champs2[4] = { "max", "yoshi", "blake", "shohei" };
    int pp = split(champs2, 4, "shohei");  //  returns 2
    // champs2 must now be either
    //      "max"  "blake"  "shohei"  "yoshi"
    // or   "blake"  "max"  "shohei"  "yoshi"
    // All elements < "shohei" (i.e., "blake" and "max") come before all
    // others.
    // All elements > "shohei" (i.e., "yoshi") come after all others.
    //Incomplete Test from spec
    std::cerr << '\n' << nn << '\n' << oo << '\n' << pp;
    std::string a[4] = { "ma", "can", "tu", "do" };
    assert(repeat(a, 4) == 4 && a[0] == "mama" && a[3] == "dodo");

    std::string b[7] = { "will", "yoshi", "shohei", "freddie", "", "max", "shohei" };
    assert(detectMatch(b, 7, "shohei") == 2);
    assert(detectMatch(b, 2, "shohei") == -1);
    assert(detectMax(b, 7) == 1);

    std::string c[3] = { "max", "shohei", "tommy" };
    assert(detectAny(b, 7, c, 3) == 2);
    assert(flip(c, 3) == 3 && c[0] == "tommy" && c[2] == "max");

    std::string d[4] = { "will", "yoshi", "freddie", "max" };
    assert(detectDifference(b, 4, d, 4) == 2);
    assert(circleLeft(d, 4, 1) == 1 && d[1] == "freddie" && d[3] == "yoshi");

    std::string e[4] = { "shohei", "freddie", "", "max" };
    assert(subsequence(b, 7, e, 4) == 2);

    std::string f[5] = { "max", "max", "max", "yoshi", "yoshi" };
    assert(enumerateRuns(f, 5) == 2);

    assert(split(b, 7, "shohei") == 3);

    std::cerr << "\nAll tests succeeded" << std::endl;
    return 0; 
}
