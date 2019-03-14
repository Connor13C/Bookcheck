
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ws;
using std::string;
#include <fstream>
using std::ifstream;
#include "ExceptionFile.h"
#include "TFIDF.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <sstream> 

void checkFile(ifstream& istr, string nameOfFile){
	if (istr.fail()) {
		cout << "Can't Read File: " << nameOfFile << endl; 
		exit(-1);//if unreadable exit
	}
	if ((istr>>ws).eof()){
		cout << "Empty File: " << nameOfFile << endl; 
		exit(-1);//if empty exit
	}
}

int main(int argc, char* argv[]){//main is a switch case and different #s of args will trigger different mains
	switch(argc){
		case 2:{//The Program will print out every word used the document and the number of times the word is used followed by the reading level of the file. (Will break puctuation and numbers into words) If document has no puctuation it will exit with warning message.
			ifstream exceptFile("Exceptions.txt");//loads in exception file
		    checkFile(exceptFile,"Exceptions.txt");//checks for file errors
		    ExceptionFile Except(exceptFile);//builds exception file map to correctly stem words
		    ifstream istr(argv[1]);//loads in file to stem 
			checkFile(istr,argv[1]);//checks for file errors
		    Map newMap;//makes new unordered map for file
			double readingLevelOfFile = newMap.makeMap(istr);//loads file into make and returns the reading level of the file
			newMap.stemMap(Except.getExceptionList());//stems all words
			newMap.printStemmedMap();//prints in alphabetical order with word counts
			cout<<argv[1]<<" has a "<<readingLevelOfFile<<" grade reading level."<<endl;//prints reading level
			break;//ends case
		}
		case 3:{//The Program will print out the file in your list that is most like the 1st argument text file and its' reading level
			ifstream exceptFile("Exceptions.txt");//loads in exception file
		    checkFile(exceptFile,"Exceptions.txt");//checks for file errors
		    ExceptionFile Except(exceptFile);//builds exception file map to correctly stem words
		    TFIDF theDocs;//creates a vector for comparing each file's words to one another
		    vector<double> readLevels; //creates vector for storing reading levels
		    vector<string> fileToReturn;//file that is most silimar to 1st file
			string file;//placeholder for ifstream to be read
			ifstream fileToCompare(argv[1]);//loads in first file from first argument to find a similar document
			checkFile(fileToCompare,argv[1]);//checks for file errors
			
			ifstream istrFiles(argv[2]);//loads in file with file names
			checkFile(istrFiles, argv[2]);//checks for file errors
			
			theDocs.addMap(fileToCompare,Except.getExceptionList());//add file to compare to index 0 of TFIDF
			
			while(istrFiles>>file){//loads all files to compare
				ifstream istrIn(file);//loads in file
				checkFile(istrIn,file);//checks for file errors
				fileToReturn.push_back(file);//adds name of file to vector
				readLevels.push_back(theDocs.addMap(istrIn,Except.getExceptionList()));//stores reading levels while adding files to TFIDF starting at index 0
			}
			unsigned indexOfCorrectMatch=0;
			double highestMatch=-1;
			double currentMatch=-1;
			for(unsigned i = 0; i<readLevels.size(); i++){//runs through TFIDF to determine most similar file to 1st file
				currentMatch=theDocs.compareTFIDF(i);
				if(currentMatch>highestMatch){
					highestMatch=currentMatch;
					indexOfCorrectMatch=i;
				}
			}
			cout<<fileToReturn.at(indexOfCorrectMatch)<<" is the most similar to "<< argv[1] <<endl;//prints most similar file
			cout<<fileToReturn.at(indexOfCorrectMatch)<<" has a "<<readLevels.at(indexOfCorrectMatch)<<" grade reading level"<<endl;//prints most similar files' reading level
			break;
		}
		case 5:{//The Program will print out the file in your list that is most like the 1st argument text file within the reading level desired and its' reading level
		    double readLevel1, readLevel2;
		    std::stringstream r1(argv[3]);
		    r1>>readLevel1;//loads in double that is lower bound of reading array
		    std::stringstream r2(argv[4]);
		    r2>>readLevel2;//loads in double that is upper bound of reading array
		    if(r1.fail()){//checks for error
				cout<<"First reading level is not correct input"<<endl;
				return -1;
			}
			if(r2.fail()){//checks for error
				cout<<"Second reading level is not correct input"<<endl;
				return -1;
			}
		
		    if(readLevel1>readLevel2){//checks that lower bound <= upper bound
				cout<<"Reading level range is not correctly defined"<<endl;
				return -1;
			}
			
			ifstream exceptFile("Exceptions.txt");//loads in exception file
			checkFile(exceptFile,"Exceptions.txt");//checks for file errors
		    ExceptionFile Except(exceptFile);//builds exception file map to correctly stem words
		    TFIDF theDocs;//creates a vector for comparing each file's words to one another
			vector<double> readLevels; //creates vector for storing reading levels
			vector<string> fileToReturn;//file that is most silimar to 1st file
			string file;//placeholder for ifstream to be read
			
			ifstream fileToCompare(argv[1]);//loads in first file from first argument to find a similar document
			checkFile(fileToCompare,argv[1]);//checks for file errors
			
			ifstream istrFiles(argv[2]);//loads in file with file names
			checkFile(istrFiles,argv[2]);//checks for file errors
			
			theDocs.addMap(fileToCompare,Except.getExceptionList());//add file to compare to index 0 of TFIDF
			
			while(istrFiles>>file){//loads all files to compare
				ifstream istrIn(file);//loads in file
				checkFile(istrIn,file);//checks for file errors
				fileToReturn.push_back(file);//adds name of file to vector
				readLevels.push_back(theDocs.addMap(istrIn,Except.getExceptionList()));//stores reading levels while adding files to TFIDF starting at index 0
			}
			
			unsigned indexOfCorrectMatch=100000;
			double highestMatch=-1;
			double currentMatch=-1;
			for(unsigned i = 0; i<readLevels.size(); i++){//runs through TFIDF to determine most similar file to 1st file
				if((readLevels.at(i)>=readLevel1)&&(readLevels.at(i)<=readLevel2)){
					currentMatch=theDocs.compareTFIDF(i);
					if(currentMatch>highestMatch){
						highestMatch=currentMatch;
						indexOfCorrectMatch=i;
					}
				}
			}
			if(indexOfCorrectMatch==100000){//if no file in reading level returns error
				cout<<"no matches"<<endl;
				return -1;
			}
			else{
				cout<<fileToReturn.at(indexOfCorrectMatch)<<" is the most similar to "<< argv[1] <<endl;//prints most similar file
				cout<<fileToReturn.at(indexOfCorrectMatch)<<" has a "<<readLevels.at(indexOfCorrectMatch)<<" grade reading level"<<endl;//prints most similar files' reading level
			}
			break;
		}
		default://print out how to use program for user on incorrect number of args
			cout<<"Usage for this program:\n"<<endl;
			cout<<"Option 1:\n"<< endl;
			cout<<"	Command line argument example: ./BookCheck textfileExample.txt"<<endl;
			cout<<"	textfileExample.txt is the name of the file to check\n"<<endl;
			cout<<"	The Program will print out every word used the document and the number of times the word is used followed by the reading level of the file. Punctuation and Symbols are considered words.\n"<<endl;
			cout<<"Option 2:\n"<<endl;
			cout<<"	Command line argument: ./BookCheck textfileExample.txt filesToCompare.txt"<<endl; 
			cout<<"	textfileExample.txt is the name of the file to check"<<endl;
			cout<<"	filesToCompare is the text file containing the names of the files to compare against\n"<<endl;
			cout<<" The Program will print out the file in your list that is most like the 1st argument text file and its' reading level\n"<<endl;
			cout<<"Option 3:\n"<<endl;
			cout<<"	Command line argument: ./BookCheck textfileExample.txt filesToCompare.txt 0.0 100.0"<<endl; 
			cout<<"	textfileExample.txt is the name of the file to check"<<endl;
			cout<<"	filesToCompare is the text file containing the names of the files to compare against"<<endl;
			cout<<"	0.0 is an example of the lower bound of the range of reading level desired"<<endl;
			cout<<"	100.0 is an example of the upper bound of the range of reading level desired"<<endl;
			cout<<" The Program will print out the file in your list that is most like the 1st argument text file within the reading level desired and its' reading level\n"<<endl;
			return -1;
	}	
    return 0;
}
