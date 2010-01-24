#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <sys/time.h>

#define POPULATION 32
#define GENERATIONS 20

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

void printpart(vector<string> &p)
{
    for (vector<string>::iterator i = p.begin();
            i != p.end();
            ++i) 
        cout << *i << " ";
    cout << endl;
}

vector<string> randompartition(string in)
{
    vector<string> p;
    for (int i = 0; i < 8; i++)
        p.push_back("");

    while (in.size() > 0) {
        int pos = random() % in.size();
        int key = random() % 8;
        p[key].append(1, in[pos]);
        in.erase(pos, 1);
    }

    return p;
}

typedef pair<long long, vector<string> > pllvs;
bool lvscompare(pllvs a, pllvs b) { return a.first < b.first; }

vector<vector<string> > cull(vector<vector<string> > &pop)
{
    vector<pllvs> fitness;
    for (vector<vector<string> >::iterator i = pop.begin();
            i != pop.end();
            ++i) {
        fitness.push_back(pllvs(quality(*i), *i));
    }

    sort(fitness.begin(), fitness.end(), lvscompare);

    vector<vector<string> > newpop;
    for (int i = 0;
            i < fitness.size() / 4;
            ++i) {
        cout << fitness[i].first << " ";
        printpart(fitness[i].second);
        newpop.push_back(fitness[i].second);
    }

    return newpop;
}

vector<string> mutate(vector<string> in)
{
    for (int count = 0; count < 2; count++) {
        int i;
        do { i = random() % in.size(); } while (in[i].size() == 0);
        
        int c = random() % in[i].size();
        in[random() % in.size()].append(1, in[i][c]);
        in[i].erase(c, 1);
    }

    printpart(in);
    return in;
}

int main()
{
    ifstream win("words/wordlist");
    win >> total;

    string word;
    win >> word;

    int freq;
    while (win >> freq) {
        win >> word;
        words.push_back(pis(freq,word));
    }

    // Seed it
    timeval t1;
    gettimeofday(&t1, NULL);
    srandom(t1.tv_usec * t1.tv_sec);

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<vector<string> > population;
    for (int i=0; i < POPULATION; i++)
        population.push_back(randompartition(alphabet));

    for (int i=0; i < GENERATIONS; i++) {
        population = cull(population);
        while (population.size() < POPULATION) {
            population.push_back(mutate(population[random() % population.size()]));
        }
    }
    
    return 0;
}
