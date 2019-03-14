#include "ExceptionFile.h"
/**
 * Reads in the exception file of words that can't be stemmed correctly and their correct replacement
 */
void ExceptionFile::Read(){
	string line;
    while(getline(in,line)){
        if(line!=""){
	
            char theLine[line.length()];
            strcpy(theLine,line.c_str());
            char *token=strtok(theLine," ");
            if(token==NULL){
				std::cout<<"Bad Exception File Format"<<std::endl;
				exit(-1);
			}
            string first = token;
            token=strtok(NULL, " ");
            if(token==NULL){
				std::cout<<"Bad Exception File Format"<<std::endl;
				exit(-1);
			}
            string second = token;
            token=strtok(NULL, " ");
            if(token!=NULL){
				std::cout<<"Bad Exception File Format"<<std::endl;
				exit(-1);
			}
            except[first]=second;
		}
    }
    //return 0;
}
/**
 * Helper method to add each word and their replacement to unordered map of exceptions
 * @param first word to stem
 * @param second correct stemming of the word
 */
void ExceptionFile::Add(string& first,string& second){
	except[first]=second;
}
/**
 * Getter for the pass by reference of the unordered map of exceptions
 * @return unordered map of exceptions
 */
unordered_map<string,string>& ExceptionFile::getExceptionList(){
	return except;
}
