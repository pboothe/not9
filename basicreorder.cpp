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

    vector<string> keys;
    keys.push_back("abc");
    keys.push_back("def");
    keys.push_back("ghi");
    keys.push_back("jkl");
    keys.push_back("mno");
    keys.push_back("pqrs");
    keys.push_back("tuv");
    keys.push_back("wxyz");


    count = 0;
    int key = 2;
    for (vector<string>::iterator s = keys.begin();
            s != keys.end();
            ++s, ++key) {
        cout << key << "\\to [";
        vector<pair<char,long long> > ordered;
        for (string::iterator c = s->begin();
                c != s->end();
                ++c)
            ordered.push_back(pair<char,long long>(*c, freq[*c]));
        sort(ordered.begin(), ordered.end(), freqcompare);

        int j = 1;
        for (vector<pair<char,long long> >::iterator i = ordered.begin();
                i != ordered.end();
                i++, j++) {
            cout << i->first;
            count += j*(i->second);
        }
        cout << "]," << endl;

    }

    cout << count << " button presses" << endl;

    return 0;
}
