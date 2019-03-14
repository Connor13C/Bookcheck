#include "ReadingLevel.h"
/**
 * Checks whether string is punctuation or a word, and increments the appropriate count for word letter or sentence
 * @param word the string to check
 */
void ReadingLevel::add(string& word){
    if(containsAlphaNum(word)){
        //countLetters(word);
        letterCount+=word.length();
        ++wordCount;
    }
    else{
        checkForPunct(word);
    }
}
/**
 * Counts the number of letters in a word
 * @param word the string to check
 */
void ReadingLevel::countLetters(string& word){//implement
    for(unsigned i= 0; i<word.length();i++){
        if(isalpha(word.at(i))||word.at(i)=='\''){
            ++letterCount;
        }
    }
}
/**
 * Checks if the non-alphanumic string contains a . ! ?
 * @param word the string to check
 */
void ReadingLevel::checkForPunct(string& word){//implement
    if((word.find('.')!=string::npos)||(word.find('!')!=string::npos)||(word.find('?')!=string::npos)){
        ++sentenceCount;
    }
}
/**
 * Checks if the word contains an alphanumeric char
 * @param word the string to check
 * @return return true if contains alphanumeric char, false if not
 */
bool ReadingLevel::containsAlphaNum(string& word){
    for(unsigned i= 0; i<word.length();i++){
        if(isalnum(word.at(i))||word.at(i)=='\''){
            return true;
        }
    }
    return false;
}
/**
 * Determines the average word size of the file, if file has no words will cause divide by zero error
 * @return value depending on size of word
 */
double ReadingLevel::lDoc(){
	return (letterCount/wordCount)*100;
}
/**
 * Determines the average sentence length, if file has no words will cause divide by zero error
 * @return value depending on the sentence length
 */
double ReadingLevel::sDoc(){
	return (sentenceCount/wordCount)*100;
}
/**
 * Determines the reading level of the file and passes it back
 * @return value of the reading level of the file
 */
double ReadingLevel::clDoc(){
	if(wordCount==0){
		exit(-1);
	}
	else{
	return 0.0588*lDoc()-0.296*sDoc()-15.8;
	}
}
