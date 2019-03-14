#ifndef MAP_H
#define MAP_H

#include <unordered_map>
using std::unordered_map;
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::istream;
using std::ostream;
#include <map>
#include "Seed.h"
#include "ReadingLevel.h"
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;

/**
 * Takes in a file and adds them to different unordered maps to keep word and word frequencies, will stem word to their
 * base word (running becomes run, darkness becomes dark)
 */
class Map {
public:
Map(){}
~Map(){}
inline unordered_map<std::string,int>& getMap(){return map2;}
bool isCapitalized(string &str);
bool doesntContainDigits(string &str);
bool isNotAcronym(string &str);
bool breakCondition(string &str, unsigned index);
void isAlphanumeric(string &str, unsigned index);
void isNotAlphanumeric(string &str, unsigned index);
void checkIfNeedsBreaks(string &str);
bool wordIsAmbiguous(string& str);
void resolveAmbiguousWords();
void printMap();
void printAmbiguousMap();
void printStemmedMap();
void putIntoMap(string str);
bool canBeStemmed(string str);
double makeMap(istream& istr);
void stemMap(unordered_map<string,string>& exceptMap);
private:
unordered_map<std::string,int> map1;
unordered_map<std::string,int> ambiguousMap;
unordered_map<std::string,int> map2;
string lastWord;
ReadingLevel readLvl;
};
#endif
