#ifndef EXCEPTIONFILE_H
#define EXCEPTIONFILE_H

#include <iostream>
#include <fstream>
using std::ifstream;
using std::getline;
#include <unordered_map>
using std::unordered_map;
#include <string>
using std::string;
#include <cstring>
/**
 * Makes an unordered map of word that can't be stemmed correctly and their correct replacements
 */
class ExceptionFile {
public:
ExceptionFile(ifstream& istr):in(istr){Read();}
void Read();
void Add(string&,string&);
unordered_map<string,string>& getExceptionList();

private:
ifstream& in;
unordered_map<string,string> except;
};
#endif
