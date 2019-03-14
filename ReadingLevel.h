
#ifndef READINGLVL_H
#define READINGLVL_H


#include <string>
using std::string;
#include <cctype>
using std::isupper;
using std::isalnum;
using std::isdigit;
#include <stdexcept>
/**
 * Tallies all word senctence and punctuation counts and gets a reading level of a file
 */
class ReadingLevel {
public:
ReadingLevel():readingLevel(-15.8),letterCount(0),sentenceCount(0),wordCount(0){
}
void add(string& word);
void countLetters(string& word);
void checkForPunct(string& word);
bool containsAlphaNum(string& word);
double lDoc();
double sDoc();
double clDoc();

inline double getLetterCount(){return letterCount;}
inline double getSentenceCount(){return sentenceCount;}

private:
double readingLevel;
double letterCount;
double sentenceCount;
double wordCount;


};
#endif
