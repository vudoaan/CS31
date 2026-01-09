#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;

string c[6] = {
	"alpha", "beta", "beta", "delta", "gamma", "gamma"
};

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
    
    int eqPos = counter;
    for (int i = counter; i < n; i++) {
        if (a[i] == splitter) {
            temp = a[i];
            a[i] = a[eqPos];
            a[eqPos] = temp;
            eqPos++;
        }
    }
    //Return where the split started
    return counter;
}

bool splitcheck(const string a[], int n, int p, string splitter)
{
	for (int k = 0; k < p; k++)
		if (a[k] >= splitter)
			return false;
	for ( ; p < n  &&  a[p] == splitter; p++)
		;
	for (int k = p; k < n; k++)
		if (a[k] <= splitter)
			return false;
	string b[100];
	copy(a, a+n, b);
	sort(b, b+n);
	return equal(b, b+n, c);
}

void testone(int n)
{
	const int N = 6;

	string aa[1+N+1] = {
		"", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
	};
	string* a = &aa[1];
	string* z = aa;
	a[-1].string::~string();
	a[N].string::~string();
	fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
	fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);

	string b[N] = {
		"alpha", "beta", "gamma", "delta", "beta", "delta"
	};

	string d[9] = {
		"alpha", "beta",  "beta", "beta", "alpha",
		"alpha", "delta", "beta", "beta"
	};

	switch (n)
	{
			         case  1: {
		assert(repeat(z, -1) == -1 && a[0] == "alpha");
			} break; case  2: {
		assert(repeat(z, 0) == 0 && a[0] == "alpha");
			} break; case  3: {
		assert(repeat(a, 1) == 1 && a[0] == "alphaalpha" &&
							a[1] == "beta");
			} break; case  4: {
		a[4] = "";
		assert(repeat(a, 6) == 6 && a[0] == "alphaalpha" &&
			a[1] == "betabeta" && a[2] == "gammagamma" &&
			a[3] == "gammagamma" && a[4] == "" &&  a[5] == "deltadelta");
			} break; case  5: {
		assert(detectMatch(z, -1, "alpha") == -1);
			} break; case  6: {
		assert(detectMatch(z, 0, "alpha") == -1);
			} break; case  7: {
		assert(detectMatch(a, 1, "alpha") == 0);
			} break; case  8: {
		assert(detectMatch(a, 6, "delta") == 5);
			} break; case  9: {
		assert(detectMatch(a, 6, "beta") == 1);
			} break; case 10: {
		assert(detectMatch(a, 6, "zeta") == -1);
			} break; case 11: {
		assert(detectMax(z, -1) == -1);
			} break; case 12: {
		assert(detectMax(z, 0) == -1);
			} break; case 13: {
		assert(detectMax(a, 1) == 0);
			} break; case 14: {
		assert(detectMax(a, 3) == 2);
			} break; case 15: {
		assert(detectMax(a, 6) == 2);
			} break; case 16: {
		assert(detectMax(a+3, 3) == 0);
			} break; case 17: {
		a[0] = "";
		a[1] = " ";
		a[2] = "";
		assert(detectMax(a, 3) == 1);
			} break; case 18: {
		assert(circleLeft(z, -1, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 19: {
		assert(circleLeft(a, 6, -1) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 20: {
		assert(circleLeft(a, 6, 6) == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 21: {
		assert(circleLeft(z, 0, 0) == -1 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 22: {
		assert(circleLeft(a, 1, 0) == 0 &&
				a[0] == "alpha" && a[1] == "beta");
			} break; case 23: {
		assert(circleLeft(a, 6, 0) == 0 &&
			a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
			} break; case 24: {
		assert(circleLeft(a, 6, 5) == 5 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 25: {
		assert(circleLeft(a, 6, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
			} break; case 26: {
		assert(circleLeft(a, 5, 3) == 3 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
			} break; case 27: {
		assert(enumerateRuns(z, -1) == -1);
			} break; case 28: {
		assert(enumerateRuns(z, 0) == 0);
			} break; case 29: {
		assert(enumerateRuns(a, 1) == 1);
			} break; case 30: {
		assert(enumerateRuns(a, 3) == 3);
			} break; case 31: {
		assert(enumerateRuns(a, 4) == 3);
			} break; case 32: {
		assert(enumerateRuns(a+2, 4) == 3);
			} break; case 33: {
		assert(enumerateRuns(d, 9) == 5);
			} break; case 34: {
		assert(flip(z, -1) == -1 && a[0] == "alpha");
			} break; case 35: {
		assert(flip(z, 0) == 0 && a[0] == "alpha");
			} break; case 36: {
		assert(flip(a, 1) == 1 && a[0] == "alpha" &&
					a[1] == "beta");
			} break; case 37: {
		assert(flip(a, 2) == 2 && a[0] == "beta" &&
					a[1] == "alpha" && a[2] == "gamma");
			} break; case 38: {
		assert(flip(a, 5) == 5 && a[0] == "beta" &&
			a[1] == "gamma" && a[2] == "gamma" && a[3] == "beta" &&
			a[4] == "alpha" && a[5] == "delta");
			} break; case 39: {
		a[2] = "zeta";
		assert(flip(a,6) == 6 && a[0] == "delta" && a[1] == "beta" &&
			a[2] == "gamma" && a[3] == "zeta" && a[4] == "beta" &&
			a[5] == "alpha");
			} break; case 40: {
		assert(detectDifference(z, -1, b, 6) == -1);
			} break; case 41: {
		assert(detectDifference(a, 6, z, -1) == -1);
			} break; case 42: {
		assert(detectDifference(z, 0, b, 0) == 0);
			} break; case 43: {
		assert(detectDifference(a, 3, b, 3) == 3);
			} break; case 44: {
		assert(detectDifference(a, 3, b, 2) == 2);
			} break; case 45: {
		assert(detectDifference(a, 2, b, 3) == 2);
			} break; case 46: {
		assert(detectDifference(a, 6, b, 6) == 3);
			} break; case 47: {
		assert(subsequence(z, -1, b, 6) == -1);
			} break; case 48: {
		assert(subsequence(a, 6, z, -1) == -1);
			} break; case 49: {
		assert(subsequence(z, 0, b, 6) == -1);
			} break; case 50: {
		assert(subsequence(a, 6, z, 0) == 0);
			} break; case 51: {
		assert(subsequence(a, 6, b, 1) == 0);
			} break; case 52: {
		assert(subsequence(a, 6, b+4, 2) == 4);
			} break; case 53: {
		assert(subsequence(a, 6, b+3, 1) == 5);
			} break; case 54: {
		assert(subsequence(a, 6, b+3, 2) == -1);
			} break; case 55: {
		assert(subsequence(a, 6, b+2, 2) == -1);
			} break; case 56: {
		assert(subsequence(a, 6, a, 6) == 0);
			} break; case 57: {
		assert(detectAny(a, 6, z, -1) == -1);
			} break; case 58: {
		assert(detectAny(z, -1, b, 6) == -1);
			} break; case 59: {
		assert(detectAny(z, 0, b, 1) == -1);
			} break; case 60: {
		assert(detectAny(a, 6, z, 0) == -1);
			} break; case 61: {
		assert(detectAny(a, 1, b, 1) == 0);
			} break; case 62: {
		assert(detectAny(a, 6, b+3, 3) == 1);
			} break; case 63: {
		assert(detectAny(a, 4, b+3, 3) == 1);
			} break; case 64: {
		assert(detectAny(a, 2, b+2, 2) == -1);
			} break; case 65: {
		assert(split(z, -1, "beta") == -1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 66: {
		assert(split(z, 0, "beta") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 67: {
		assert(split(a, 1, "aaa") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 68: {
		assert(split(a, 1, "alpha") == 0 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 69: {
		assert(split(a, 1, "zeta") == 1 &&
			a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 70: {
		assert(split(a, 2, "aaa") == 0 &&
			splitcheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 71: {
		assert(split(a, 2, "alpha") == 0 &&
			splitcheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 72: {
		assert(split(a, 2, "beta") == 1 &&
			splitcheck(a, 2, 1, "beta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 73: {
		assert(split(a, 2, "zeta") == 2 &&
			splitcheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
			a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
			} break; case 74: {
		assert(split(a, 6, "aaa") == 0 && splitcheck(a, 6, 0, "aaa"));
			} break; case 75: {
		assert(split(a, 6, "alpha") == 0 && splitcheck(a, 6, 0, "alpha"));
			} break; case 76: {
		assert(split(a, 6, "beta") == 1 && splitcheck(a, 6, 1, "beta"));
			} break; case 77: {
		assert(split(a, 6, "delta") == 3 && splitcheck(a, 6, 3, "delta"));
			} break; case 78: {
		assert(split(a, 6, "gamma") == 4 && splitcheck(a, 6, 4, "gamma"));
			} break; case 79: {
		assert(split(a, 6, "zeta") == 6 && splitcheck(a, 6, 6, "zeta"));
			} break; case 80: {
		a[2] = "mu";
		c[5] = "mu";
		assert(split(a, 6, "mu") == 5 && splitcheck(a, 6, 5, "mu"));
			} break; case 81: {
		assert(split(a, 6, "chi") == 3 && splitcheck(a, 6, 3, "chi"));
			} break; case 82: {
		  // To earn the bonus point for circleLeft, this and all other
		  // circleLeft tests must pass, and that function must not
		  // create any additional arrays.
		const int BIG = 500;
		string h[BIG];
		for (int k = 0; k < BIG; k++)
			h[k] = (k % 2 == 0 ? "alpha" : "beta");
		h[BIG-2] = "gamma";
		h[BIG-1] = "delta";
		circleLeft(h, BIG, 0);
		assert(h[BIG-3] == "gamma"  &&  h[BIG-2] == "delta");
			} break; case 83: {
		  // To earn the bonus point for flip, this and all other
		  // flip tests must pass, and that function must not
		  // create any additional arrays.
		const int BIG = 500;
		std::string h[BIG];
		for (int k = 0; k < BIG; k++)
			h[k] = (k % 2 == 0 ? "alpha" : "beta");
		h[0] = "gamma";
		h[BIG-1] = "delta";
		flip(h, BIG);
		assert(h[0] == "delta"  &&  h[BIG-1] == "gamma");
			} break; case 84: {
		  // To earn the bonus point for split, this and all other
		  // split tests must pass, and that function must not
		  // create any additional arrays.
		const int BIG = 500;
		string h[BIG];
		string i[3] = { "alpha", "beta", "gamma" };
		for (int k = 0; k < BIG; k++)
			h[k] = i[k % 3];
		split(h, BIG, "beta");
		int m;
		for (m = 0; m < (BIG+2)/3; m++)
			assert(h[m] == "alpha");
		for ( ; m < 2*(BIG+1)/3; m++)
			assert(h[m] == "beta");
		for ( ; m < BIG; m++)
			assert(h[m] == "gamma");
			} break;
	}

	new (&a[-1]) string;
	new (&a[N]) string;
}

int main () {
    cout << "Enter a test number (1 to 84): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 84)
    {
	cout << "Bad test number" << endl;
	return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
}
