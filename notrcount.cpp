#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef pair<int, string> pis;
vector<pis> words;
long long total;

bool piscompare(pis a, pis b) { return a.first > b.first; }

long long quality(vector<string> &partition)
{
    map<char,string> rmap;
    int i = 0;
    string buttons = "23456789";
    for (vector<string>::iterator s = partition.begin();
            s != partition.end();
            ++s, ++i) {
        for (string::iterator c = s->begin(); c != s->end(); ++c) {
            rmap[*c] = buttons[i];
        }
    }

    map<string, vector<pis> > typing;
    for (vector<pis>::iterator fw = words.begin();
            fw != words.end();
            ++fw) {
        int freq = fw->first;
        string word = fw->second;
        string presses = "";
        for (string::iterator c = word.begin(); c != word.end(); ++c) {
            presses += rmap[*c];
        }

        if (typing.count(presses) == 0)
            typing[presses] = vector<pis>();
        typing[presses].push_back(*fw);
    }

    for (map<string, vector<pis> >::iterator w = typing.begin();
            w != typing.end();
            ++w) {
        sort(w->second.begin(), w->second.end(), piscompare);
    }

    long long totalpresses = 0;
    for (map<string, vector<pis> >::iterator w = typing.begin();
            w != typing.end();
            ++w) {
        int wordsize = w->first.size();
        for (int i = 0; i < w->second.size(); i++) {
            totalpresses += (wordsize + i) * w->second[i].first;
        }
    }
    return totalpresses;
}

int start = 0;
int end = -1;
void genallpartitions(string &s, int count, int index, 
        vector<string> &part)
{
    if (count == 0) {
        if (--start > 0) {
            --end;
        } else {
            // Analyze it
            cout << quality(part) << " ";
            for (vector<string>::iterator i = part.begin();
                    i != part.end();
                    ++i)
                cout << *i << " ";
            cout << endl;
            if (--end == 0) exit(0);
        }
    } else if (count == 1) {
        part.push_back(s.substr(index, s.size()-index));
        genallpartitions(s, count-1, s.size(), part);
        part.pop_back();
    } else {
        for (int size = 1; size < s.size() - index - count + 2; size++) {
            part.push_back(s.substr(index, size));
            genallpartitions(s, count-1, index+size, part);
            part.pop_back();
        }
    }
}

int main(int argc, char** argv)
{
    if (argc == 3) {
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    }

    ifstream win("words/wordlist");
    win >> total;

    string word;
    win >> word;

    int freq;
    while (win >> freq) {
        win >> word;
        words.push_back(pis(freq,word));
    }

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<string> partition;
    genallpartitions(alphabet, 8, 0, partition);
    return 0;
}
