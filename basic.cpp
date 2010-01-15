#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool freqcompare(pair<char, long long> f, pair<char, long long> s) { return f.second > s.second; }

string alphabet = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char** argv)
{
    int tmp;
    ifstream win("words/wordlist");
    win >> tmp;

    string word;
    win >> word; // Eat the rest of the header

    map<char,long long> freq;
    for (string::iterator c = alphabet.begin();
            c != alphabet.end();
            ++c)
        freq[*c] = 0;

    long long count;
    while (win >> count) {
        win >> word;
        for (string::iterator i = word.begin(); i != word.end(); ++i)
            freq[*i] += count;
    }

    vector<pair<char,long long> > ordered;
    for (map<char,long long>::iterator i = freq.begin();
            i != freq.end();
            ++i)
        ordered.push_back(*i);
    sort(ordered.begin(), ordered.end(), freqcompare);

    for (vector<pair<char,long long> >::iterator i = ordered.begin();
            i != ordered.end();
            i++)
        cout << "(" << i->first << ", " << i->second << ") ";
    cout << endl;

    count = 0;
    int level = 0;
    int levelcount = 0;
    for (vector<pair<char,long long> >::iterator i = ordered.begin();
            i != ordered.end();
            i++, levelcount++) {
        if (levelcount % 8 == 0) {
            cout << endl << "Level " << ++level << ": ";
        }

        cout << "(" << i->first << ", " << i->second << ") ";
        count += i->second * level;
    }
    cout << endl;
    cout << count << " button presses" << endl;

    return 0;
}
