#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool freqcompare(pair<char, long long> f, pair<char, long long> s) { return f.second > s.second; }

int main(int argc, char** argv)
{
    int tmp;
    ifstream win("words/wordlist");
    win >> tmp;

    string word;
    win >> word; // Eat the rest of the header

    map<char,long long> freq;
    freq['a'] = 0;
    freq['b'] = 0;
    freq['c'] = 0;
    freq['d'] = 0;
    freq['e'] = 0;
    freq['f'] = 0;
    freq['g'] = 0;
    freq['h'] = 0;
    freq['i'] = 0;
    freq['j'] = 0;
    freq['k'] = 0;
    freq['l'] = 0;
    freq['m'] = 0;
    freq['n'] = 0;
    freq['o'] = 0;
    freq['p'] = 0;
    freq['q'] = 0;
    freq['r'] = 0;
    freq['s'] = 0;
    freq['t'] = 0;
    freq['u'] = 0;
    freq['v'] = 0;
    freq['w'] = 0;
    freq['x'] = 0;
    freq['y'] = 0;
    freq['z'] = 0;

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
