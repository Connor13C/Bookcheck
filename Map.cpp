#include "Map.h"


/**
 * Checks if the string starts with a capitalized letter
 * @param str string to check
 * @return True if str is capitalized, False if not
 */
bool Map::isCapitalized(string &str){//checks if start of string is capitalized
	//cout<<"isCapitalized"<<endl;
    return isupper(str.at(0));
}
/**
 * Checks if the string contains a digit
 * @param str the string to check
 * @return True if string contains a digit, False if not
 */
bool Map::doesntContainDigits(string &str){//checks if string doesn't have any numbers 0-9
	//cout<<"doesntContainDigits"<<endl;
    for(unsigned i =0; i<str.length();i++){
        if(isdigit(str.at(i))){
        return false;
        }
    }
    return true;
}
/**
 * Checks if the string is an acronym like iPhone
 * @param str string to check
 * @return True if str is an acronym, False if not
 */
bool Map::isNotAcronym(string &str){//checks if string proper name for something aka iPhone
	//cout<<"isNotAcronym"<<endl;
    for(unsigned i =1; i<str.length();i++){
        if(isupper(str.at(i))){
            return false;
        }
    }
    return true;
}
/**
 * Checks for certain conditions to see if the word needs to broken into 2 strings like there is no space between
 * a period and the next word (end.He was..)
 * @param str the string to check
 * @param index the index of the string that may need to be substringed
 * @return True if string needs to be made into 2 strings, False if not
 */
bool Map::breakCondition(string &str, unsigned index){ //check if string s/b substring at special char
    
    if(str.at(index)=='.'){//if string is only "."
        if((index-1<0)&&(str.length()-1)==index){
            return true;
        }
        if(str.length()>index+1){//if index+1 isn't out of bounds check for digit
            if(isdigit(str.at(index+1))){
                if(index-1>=0){//if index-1 isn't out of bounds check for digit
                    if(isdigit(str.at(index-1))){
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
        }


    }
    if(str.at(index)==','){
        if((index-1<0)||(str.length()<3)||(str.length()-1)==index){
            return true;
    }
        if(isdigit(str.at(index-1))&&isdigit(str.at(index+1))){
            return false;
        }
    }
    return true; 
}
/**
 * Checks if the char at the index is alphanumeric including ' char
 * @param str string to check
 * @param index is the index of string that the char is at
 */
void Map::isAlphanumeric(string &str, unsigned index){
    for(unsigned i=index; i<str.length();i++){
        if(!(isalnum(str.at(i))||(str.at(i)=='\''))){
            if(breakCondition(str, i)){
                putIntoMap(str.substr(0,i));
                string line = str.substr(i,string::npos);
                    checkIfNeedsBreaks(line);
                    break;
            }
        }
        if((i+1)>=str.length()){
            putIntoMap(str);
        }
    }
}
/**
 * Checks if the char at the index is non-alphanumeric
 * @param str the string to check
 * @param index is the index of string that the char is at
 */
void Map::isNotAlphanumeric(string &str, unsigned index){
    for(unsigned i=index; i<str.length();i++){
        if(str.at(i)=='.'){//special case if string starts with '.' or with non alnum and encounters '.'
                if(str.length()>index+1){//if index+1 isn't out of bounds check for digit
                    if(isdigit(str.at(index+1))){
                        isAlphanumeric(str, index+1);
                    break;
                    }
                }
        }
        if(isalnum(str.at(i))||(str.at(i)=='\'')){
            if(breakCondition(str, i)){
                putIntoMap(str.substr(0,i));
                    string line = str.substr(i,string::npos);
                    checkIfNeedsBreaks(line);
                break;
            }
        }
        if((i+1)>=str.length()){
            putIntoMap(str);
        }
    }
}
/**
 * Checks for alphanumeric chars or non-alphanumeric chars at index 0 of the string and send them to be parsed
 * @param str the string to check
 */
void Map::checkIfNeedsBreaks(string &str){// divides alphanumeric chars from non alphanumeric chars in a string 
    if(str==""){
    }
    else{
        if(isalnum(str.at(0))||(str.at(0)=='\'')){
            isAlphanumeric(str,0);
        }
       else{ 
            isNotAlphanumeric(str,0);
        }
    }
}
/**
 * Checks to see that the word can be broken down so not acronyms proper names etc.
 * @param str the string to check
 * @return True if the word can be stemmed, False if not
 */
bool Map::canBeStemmed(string str){
	if(str.length()>2){
        if((str.at(0)=='\'')||(isalnum(str.at(0)))){
            if(!(isCapitalized(str))){
                if(isNotAcronym(str)){
                    if(doesntContainDigits(str)) return true;
				}
			}
		}
	}
	return false;
}
/**
 * Checks to be if the word is capitilized but it is unknown if it should be because it follows punctuation
 * @param str string to check
 * @return True if word is ambiguous, False if not
 */
bool Map::wordIsAmbiguous(string& str){
	//cout<<"wordIsAmbiguous"<<str<<endl;
	if(isCapitalized(str)&&doesntContainDigits(str)&&isNotAcronym(str)){
		if(map1.size()==0){
			  return true;
		 }
			for(unsigned i = 0; i<lastWord.length(); i++){
				if(lastWord.at(i)=='.'||lastWord.at(i)=='!'||lastWord.at(i)=='?') return true;
		}
	} 
    return false;
}
/**
 * Checks to see if ambiguous words are in non-ambiguous map, if they are then add them still capitalized to map otherwise
 * make them lowercase and add them to map
 */
void Map::resolveAmbiguousWords(){
	for(auto it = ambiguousMap.begin();it != ambiguousMap.end();++it){
		if(map1.find(it->first)!=map1.end()){
			map1[it->first]+=it->second;
		}
		else{
			string str=it->first;
			char one = tolower(str.at(0));
			str=one+str.substr(1,string::npos);
			map1[str]+=it->second;
		}	
	}
}
/**
 * prints out the map of all the words in alphabetical order that are non-ambiguous in the file that aren't stemmed yet
 */
void Map::printMap(){
	vector<string> strVec;
	for(auto it =map1.begin(); it!=map1.end(); ++it){
		strVec.push_back(it->first);
	}
	sort(strVec.begin(),strVec.end());
	for(unsigned i =0; i<strVec.size();i++){
		cout<<strVec.at(i)<<" "<<map1.find(strVec.at(i))->second<<endl;
	}
}
/**
 * prints out the map of all the words in alphabetical order that are ambiguous in the file that aren't stemmed yet
 */
void Map::printAmbiguousMap(){
		vector<string> strVec;
	for(auto it =ambiguousMap.begin(); it!=ambiguousMap.end(); ++it){
		strVec.push_back(it->first);
	}
	sort(strVec.begin(),strVec.end());
	for(unsigned i =0; i<strVec.size();i++){
		cout<<strVec.at(i)<<" "<<ambiguousMap.find(strVec.at(i))->second<<endl;
	}
}
/**
 * prints out the map of all the words in alphabetical order that are non-ambiguous in the file that have been stemmed
 */
void Map::printStemmedMap(){
	vector<string> strVec;
	for(auto it =map2.begin(); it!=map2.end(); ++it){
		strVec.push_back(it->first);
	}
	sort(strVec.begin(),strVec.end());
	for(unsigned i =0; i<strVec.size();i++){
		cout<<strVec.at(i)<<" "<<map2.find(strVec.at(i))->second<<endl;
	}
}
/**
 * Reads in the file and converts all word into their stemmed versions and adds them to add unordered map while determining
 * the reading level of the file
 * @param istr pass by reference of the ifstream of the file
 * @return value of the reading level of the file
 */
double Map::makeMap(istream& istr){
    string fromFile;
    while(istr>>fromFile){
        checkIfNeedsBreaks(fromFile);
    }
    resolveAmbiguousWords();
    return readLvl.clDoc();
}
/**
 * Places the word into either the ambiguous words map or the non-ambiguous words map
 * @param str the string to place in a map
 */
void Map::putIntoMap(string str){//checks if string is uniquely identified
	readLvl.add(str);
    if(wordIsAmbiguous(str)){
		lastWord=str;
		++ambiguousMap[str];
    }
    else{
		lastWord=str;
		++map1[str];
	}
}
/**
 * Stems all words and places them into an unordered map
 * @param exceptMap unordered map that includes all word that don't stem correctly and what they should be stemmed to
 */
void Map::stemMap(unordered_map<string,string>& exceptMap){
	for(auto it = map1.begin();it != map1.end();++it){
		if(canBeStemmed(it->first)){
			if(exceptMap.find(it->first)!=exceptMap.end()){
			map2[exceptMap[it->first]]+=it->second;
			}
			else{
			Seed newSeed(it->first);
			string theSeed =newSeed.convertToSeed();
			exceptMap[it->first]=theSeed;
			map2[theSeed]+=it->second;
		}
		}
		else{
			map2[it->first]+=it->second;
		}
	}
}

