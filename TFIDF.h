#ifndef TFIDF_H
#define TFIDF_H

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ws;
using std::string;
#include <fstream>
using std::ifstream;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <cctype>
using std::isupper;
using std::isalnum;
using std::isdigit;
#include <math.h>
#include <unordered_map>
using std::unordered_map;
#include <iomanip>
#include "Map.h"
/**
 * Overall class takes in a bunch of files and compares them to determine their similarity to one another
 */
class TFIDF {
public:
TFIDF():total(0),numOfMaps(0){}

bool isNotPunct(string str);
double addMap(ifstream& istr,unordered_map<string,string>& exceptMap);
double idfWord(string word);
double tfidfWordDoc(string word,unsigned indexOfMaps);
double tfidfWordDocTotal(unsigned indexOfMaps,unsigned indexOfMaps2);
double compareTFIDF(unsigned index);
void printMatrix();

private:
vector< unordered_map<std::string,int> > Maps;
vector<string> arrayOneStrings;
vector<int> arrayOneCounts;
double total;
double numOfMaps;
};
#endif
