#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
    int tmp;
    ifstream win("words/wordlist");
    win >> tmp;

    string word;
    win >> word; // Eat the rest of the header

    map<char,int> presses;
    presses['a'] = 1;
    presses['b'] = 2;
    presses['c'] = 3;
    presses['d'] = 1;
    presses['e'] = 2;
    presses['f'] = 3;
    presses['g'] = 1;
    presses['h'] = 2;
    presses['i'] = 3;
    presses['j'] = 1;
    presses['k'] = 2;
    presses['l'] = 3;
    presses['m'] = 1;
    presses['n'] = 2;
    presses['o'] = 3;
    presses['p'] = 4;
    presses['q'] = 3;
    presses['r'] = 2;
    presses['s'] = 1;
    presses['t'] = 1;
    presses['u'] = 2;
    presses['v'] = 3;
    presses['w'] = 1;
    presses['x'] = 2;
    presses['y'] = 3;
    presses['z'] = 4;

    long long total = 0;
    int freq;
    while (win >> freq) {
        win >> word;
        for (string::iterator i = word.begin(); i != word.end(); ++i)
            total += freq * presses[*i];
    }

    cout << total << endl;

    return 0;
}
