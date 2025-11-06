#include <iostream>
#include <cassert>
#include <string>

int repeat(std::string a[], int n) {
    if (n < 0) {
        return -1;
    }
    
    for (int i = 0; i < n; i++) {
        a[i] += a[i]; 
    }
    return n;
}

int detectMatch(const std::string a[], int n, std::string target) {
    if (n < 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] == target) {
            return i;
        }
    }
    return -1;
}

int detectMax(const std::string a[], int n) {
    if (n < 0) {
        return -1;
    }
    int j, latest = 0;
    for (int i = 0; i < n; i++) {
        if (a[i][0] > a[latest][0]) {
            latest = i;
        } else if (a[i][0] == a[latest][0]) {
            for (j = 0; j < a[i].length() && a[latest].length(); j++) {
                if (a[i][j] != a[latest][j]) {
                    break;
                }
            }
            if (j == a[i].length() || j == a[latest].length()) {
                if (a[i].length() > a[latest].length()) {
                    latest = i;
                }
            } else if (a[i][j] > a[latest][j]) {
                latest = i;
            }
        }
    }
    return latest;
}
//Questions
//What if pos is 1 and n is 4 but the array size is bigger than 4? Will we still have to change the rest of the array?
//Extra Credit Question (No extra array)
int circleLeft(std::string a[], int n, int pos) {
    if (n < 0 || pos >= n || pos < 0) {
        return -1;
    }
    std::string temp = a[pos];
    for (int i = 0; i < n; i++) { 
        if (i >= pos && i < n - 1) {
            a[i] = a[i + 1];
        }
    }
    a[n - 1] = temp;
    return pos;
}

int enumerateRuns(const std::string a[], int n) {
    if (n < 0) {
        return -1;
    }
    std::string currentString = a[0];
    int counter = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != currentString) {
            currentString = a[i];
            counter++;
        }
    }
    return counter;
}

//Extra Credit Question (No extra array)
int flip(std::string a[], int n) {
    if (n < 0) {
        return -1;
    }
    std::string temp;
    for (int i = 0; i < n/2; i++) {
        temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
    return n;
}

int detectDifference(const std::string a1[], int n1, const std::string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
        return -1;
    }
    for (int i = 0; i < n1 && i < n2; i++) {
        if (a1[i] != a2[i]) {
            return i;
        }
    }
    if (n1 <= n2) {
        return n1;
    } else {
        return n2;
    }  
}
//Questions
//Can n1 ever be smaller than n2?
//What does it mean to consider a sequence of 0 elements?
int subsequence(const std::string a1[], int n1, const std::string a2[], int n2) {
    if (n1 < 0 || n2 < 0 || n1 < n2) {
        return -1;
    } else if (n2 == 0) {
        return 0;
    }
    int j;
    for (int i = 0; i < n1; i++) {
        if (a2[0] == a1[i]) {
            for (j = 1; j < n2 && i + j < n1; j++) {
                if (a2[j] != a1[i+j]) {
                    break;
                }
            }
            if (j == n2) {
                return i;
            }
        }
    }
    return -1;
}
//Questions
//What if both strings have no elements?
int detectAny(const std::string a1[], int n1, const std::string a2[], int n2) {
    if (n1 < 0 || n2 < 0) {
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
//Do we need to account for the alphabetical after the first letter of splitter?
//Extra Credit Question (No extra array)
//Alphabetical Question
int split(std::string a[], int n, std::string splitter) {
    if (n < 0) {
        return -1;
    }
    std::string temp;
    int counter, k, l;
    //Sorts alphabetically
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][0] > a[j][0]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            } else if (a[i][0] == a[j][0]) {
                for (k = 1; k < a[i].length() && k < a[j].length(); k++) {
                    if (a[i][k] != a[j][k]) { 
                        break;
                    }
                }
                if (k == a[i].length() || k == a[j].length()){
                    if (a[i].length() > a[j].length()){
                        temp = a[i];
                        a[i] = a[j];
                        a[j] = temp;
                    }
                } else if (a[i][k] > a[j][k]) {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                } 
            }
        }
    }
    for (counter = 0; counter < n; counter++) {
        if (a[counter] == splitter) {
            break;
        } else if (a[counter][0] == splitter[0]){
            for (l = 0; l < a[counter].length() && splitter.length(); l++) {
                if(a[counter][l] != splitter[l]) {
                    break;
                }
            }
            if (l == a[counter].length() || l == splitter.length()){
                if (a[counter].length() > splitter.length()){
                    break;
                }
            } else if (a[counter][l] > splitter[l]) {
                break;
            } 
        } else if (a[counter][0] > splitter[0]) {
            break;
        }
    }
    return counter;
}
//Questions
//
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