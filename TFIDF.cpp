#include "TFIDF.h"
/**
 * Checks to see if the string contains any chars other than letters
 * @param str string to check
 * @return returns true if chars are letters only, returns false if not
 */
bool TFIDF::isNotPunct(string str){
    for(unsigned i = 0; i<str.length();i++){
        if(isalnum(str.at(i))||str.at(i)=='\''){
            return true;
        }
    }
    return false;
}
/**
 * Adds file to unordered map while stemming all words (reading becomes read) calculates the reading level
 *of the document, get put into vector, the reading level of the file is passed back, and throw exception if
 * there is no punctuation in file
 * @param istr pass by reference of ifstream
 * @param exceptMap unordered map containing words that do not stem correctly
 * @return returns reading level of the file
 */
double TFIDF::addMap(ifstream& istr,unordered_map<string,string>& exceptMap){
	Map newMap;
	double readingLevelOfFile = newMap.makeMap(istr);
	newMap.stemMap(exceptMap);
	//newMap.printStemmedMap();
    ++numOfMaps;
    Maps.push_back(newMap.getMap());
    return readingLevelOfFile;
}
/**
 * Determines how often a word appears throughout all files provided, if the word is in every file then it is considered
 * a common word that won't help determine the similarity of the original file so a 0 is passed back
 * @param word string in the unordered maps to check
 * @return returns a value of word frequency throughout the files
 */
double TFIDF::idfWord(string word){
    double n=0;
    for(unsigned i = 0; i<Maps.size();i++){
         if(Maps.at(i).find(word)!=Maps.at(i).end()){
             ++n;
        }
    }
    //cout<< "idfWord: " << word << log10(numOfMaps/n) <<endl;
    return log10(numOfMaps/n);
}
/**
 * Checks to see if a word exists in a unordered map of a file, if it does it returns the frequency of the word in the
 * file, if it doesn't it retuns a 0
 * @param word string to check for
 * @param indexOfMaps index of the unordered map to use in the vector
 * @return returns the frequecy of the word in the document
 */
double TFIDF::tfidfWordDoc(string word,unsigned indexOfMaps){
    if(Maps.at(indexOfMaps).find(word)==Maps.at(indexOfMaps).end()) return 0;
    else{
		//cout<<"tfidfWordDoc: " << word << Maps.at(indexOfMaps).find(word)->second << endl;
        return Maps.at(indexOfMaps).find(word)->second*idfWord(word);
    }
}
/**
 * Determines a similarity value for the two files compared
 * @param indexOfMaps index of the first unordered map in the vector
 * @param indexOfMaps2 index of the second unordered map in the vector
 * @return double representation of the similarity value, the higher the value the more closely related they are
 */
double TFIDF::tfidfWordDocTotal(unsigned indexOfMaps,unsigned indexOfMaps2){
    double docTotal = 0;
    for(auto it = Maps.at(indexOfMaps).begin(); it!=Maps.at(indexOfMaps).end(); ++it){
            if(isNotPunct(it->first)){
                docTotal+=tfidfWordDoc(it->first,indexOfMaps)*tfidfWordDoc(it->first,indexOfMaps2);
            }
    }
    //cout<<"tfidfWordDocTotal: " << docTotal <<endl;
    return docTotal;
}
/**
 * Compares the similarity of the original file to one of the provided files
 * @param index the index of the unordered map of the provided file
 * @return returns the similarity value comparing files
 */
double TFIDF::compareTFIDF(unsigned index){
	//cout<<tfidfWordDocTotal(0,index+1)<<endl;
	return tfidfWordDocTotal(0,index+1);
}
/**
 * Prints out a similarity matrix of TFIDF values using pairing of files (1,2) for example
 * (0,0) (0,1) (0,n)
 * (1,0) (1,1) (1,n)
 * (m,0) (m,1) (m,n)
 */
void TFIDF::printMatrix(){
    for(unsigned i = 0; i<numOfMaps; i++){
        double out;
        for(unsigned j = 0; j<numOfMaps; j++){
            out=tfidfWordDocTotal(i,j);
            cout<<std::fixed;
			cout<<std::setprecision(3);
            cout<<out;
            cout<<" ";
        }
        cout<<endl;
    }
}
