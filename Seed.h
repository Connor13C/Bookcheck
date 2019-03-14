#ifndef SEED_H
#define SEED_H

#include <string>
using std::string;
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ws;
/**
 * Converts a word into it's stem(reading becomes read, darkness becomes dark)
 */
class Seed {
public:
Seed(string word):seed(word),prefixToSeed(""){}
inline void setSeed(string &word){seed=word;}
inline string& getSeed(){return seed;}
inline void setPrefix(string word){prefixToSeed=word;}


int suffInRegion(string &word, string suffix);
void overwriteSeed(string &word);
bool isVowel(string &word, unsigned index);
bool containsVowel(string &word);
bool endsDouble(string &word);
bool isShortSyll(string &word);
bool isShort(string &word);
string& prefix(string &word, string prefix);
bool suffixMatches(string &word, string suffix);
string replaceSuffix(string &word, unsigned sizeToRemove, string suffix);
string replaceCond(string &word);
string liCond(string &word);
string stepOne(string &word);
string stepTwo(string &word);
string stepThree(string &word);
string stepFour(string &word);
string stepFive(string &word);
string stepSix(string &word);
string stepSeven(string &word);
string stepEight(string &word);
string convertToSeed();
private:
    string seed;
    string prefixToSeed;
};
#endif
