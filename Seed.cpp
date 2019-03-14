#include "Seed.h"
/**
 * Check to see where suffix is located in word (if suffix is the whole word, close to the end of the word, or at the end)
 * @param word string to check
 * @param suffix suffix inside the word
 * @return 0,1,or 2 depending on the location of the suffix
 */
int Seed::suffInRegion(string &word, string suffix){
    if(word.length()<=suffix.length()){
        return 0;
    }
    else{
        int count=0;
        for(unsigned i = 0;i<word.length()-suffix.length();i++){
            if(i!=0&&!isVowel(word,i)){//if nonvowel and index -1 isn't out of bounds
                if(isVowel(word,i-1)&&i+1<word.length()){//if previous char is vowel
                    count++;
                }
                if(count>2){
                    return 2;
                }
            }
        }
        return count;
    }
}
/**
 * trivial method to overwrite global var
 * @param word string to set as new seed
 */
void Seed::overwriteSeed(string &word){
    seed=word;
}
/**
 * Checks to see if the char at that index is a vowel
 * @param word string to check
 * @param index the index of the char
 * @return returns true if char is a vowel, false if not
 */
bool Seed::isVowel(string &word, unsigned index){
    switch(word.at(index)){
        case 'a':return true;
        case 'e':return true;
        case 'i':return true;
        case 'o':return true;
        case 'u':return true;
        case 'y':
            if(index!=0){
                if(!isVowel(word,index-1)){
                    return true;
                }
            }
        default: return false;
    }
}
/**
 * Checks to see if the word contains any vowels
 * @param word string to check
 * @return returns true if word has a vowel char in it, false if not
 */
bool Seed::containsVowel(string &word){
    if(word!=""){
        for(unsigned i = 0;i<word.length();i++){
            if(isVowel(word,i)){
            return true;
            }
        }
    }
    return false;
}
/**
 * Check to see if a word ends with bb dd ff gg mm nn pp rr or tt
 * @param word string to check
 * @return returns true if it ends in specific double letter, false if not
 */
bool Seed::endsDouble(string &word){
    if(word.length()>1){
        if(word.at(word.length()-1)=='b'&&word.at(word.length()-2)=='b')return true;
        if(word.at(word.length()-1)=='d'&&word.at(word.length()-2)=='d')return true;
        if(word.at(word.length()-1)=='f'&&word.at(word.length()-2)=='f')return true;
        if(word.at(word.length()-1)=='g'&&word.at(word.length()-2)=='g')return true;
        if(word.at(word.length()-1)=='m'&&word.at(word.length()-2)=='m')return true;
        if(word.at(word.length()-1)=='n'&&word.at(word.length()-2)=='n')return true;
        if(word.at(word.length()-1)=='p'&&word.at(word.length()-2)=='p')return true;
        if(word.at(word.length()-1)=='r'&&word.at(word.length()-2)=='r')return true;
        if(word.at(word.length()-1)=='t'&&word.at(word.length()-2)=='t')return true;
    }
return false;
}
/**
 * Checks if word length is = 2 and ends in vowel char then non vowel char, or if ends with non vowel char vowel char
 * non vowel char
 * @param word string to check
 * @return returns true if word is a short syllable, false if not
 */
bool Seed::isShortSyll(string &word){
    if(word.length()==2){
            if(isVowel(word,0)&&!isVowel(word,1)){
             return true;   
            }
        }
    if(word.length()>2){
        if(!isVowel(word,word.length()-3)&&isVowel(word,word.length()-2)&&!isVowel(word,word.length()-1)){
            if(word.at(word.length()-1)!='w'&&word.at(word.length()-1)!='x'&&word.at(word.length()-1)!='y'){
                    return true;
            }
        }
    }
    return false;
}
/**
 * Checks if suffix can't be broken down
 * @param word string to check
 * @return returns true if suffix is in region 0, false if not
 */
bool Seed::isShort(string &word){
    if(suffInRegion(word,"")==0){
        if(isShortSyll(word)){
            return true;
        }
    }
    return false;
}
/**
 * Makes a substring without the provided suffix and passes it back
 * @param word string to edit
 * @param suffix string to be clipped out of end of word
 * @return return a prefix substring of word
 */
string& Seed::prefix(string &word, string suffix){
    setPrefix(word.substr(0,word.length()-suffix.length()));
        return prefixToSeed;
}
/**
 * Checks to see if the word end in the matching suffix
 * @param word string to check
 * @param suffix string to match with end of word
 * @return returns true if word ends with the suffix, false if not
 */
bool Seed::suffixMatches(string &word, string suffix){
        if(word.length()>=suffix.length()){
            if(word.compare(word.length()-suffix.length(),suffix.length(),suffix)==0){
                return true;
            }
        }
    return false;
}
/**
 * Helper method to replace the end of a string
 * @param word string to edit
 * @param sizeToRemove number of chars to cut off end off string
 * @param suffix string to add to the end of the string after it has been chopped
 * @return returns the new word after it has been edited
 */
string Seed::replaceSuffix(string &word, unsigned sizeToRemove, string suffix){
return word.replace(word.length()-sizeToRemove,sizeToRemove,suffix);
}
/**
 * Checks to see if string has matching suffix
 * @param word string to check
 * @return returns edited word if suffix matches correctly otherwise returns the word back
 */
string Seed::replaceCond(string &word){
    if(suffixMatches(word,"at")||suffixMatches(word,"bl")||suffixMatches(word,"iz")){
        return replaceSuffix(word,0,"e");
    }
    if(endsDouble(word)){
        return replaceSuffix(word,1,"");
    }
    if(isShort(word)){
        return replaceSuffix(word,0,"e");
    }
 return word;   
}
/**
 * If word ends in li it checks the char before the li and cuts the word if the char is c d e g h k m n r t
 * @param word the string to check
 * @return returns a word without li ending if conditions match, if not returns the same word back
 */
string Seed::liCond(string &word){
    if(word.length()>2){
            switch(word.at(word.length()-3)){
                case 'c':
                case 'd':
                case 'e':
                case 'g':
                case 'h':
                case 'k':
                case 'm':
                case 'n':
                case 'r':
                case 't':return replaceSuffix(word,2,"");
            }
    }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepOne(string &word){
    if(word!=""){
        if(word.at(0)=='\''){//if string starts with '
            word=word.substr(1,string::npos);//chop off ' from front of string
        }
    }
    if(suffixMatches(word,"'s'")){//if suffix is 's'
        return word.substr(0,word.length()-3);//chop off 's'
    }
    if(suffixMatches(word,"'s")){//if suffix is 's
        return word.substr(0,word.length()-2);//chop off 's
    }
    if(suffixMatches(word,"'")){//if suffix is '
        return word.substr(0,word.length()-1);//chop off '
    }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepTwo(string &word){
        if(suffixMatches(word,"sses")){//if suffix is sses
            return word.substr(0,word.length()-2);//chop off es
        }
        if(suffixMatches(word,"ied")||suffixMatches(word,"ies")){//if suffix is ied or ies
            if(prefix(word,"ied").length()>1){
                return word.substr(0,word.length()-2);//chop off last 2
            }
            else{
                return word.substr(0,word.length()-1);//chop off last 1
            }
        }
        if(suffixMatches(word,"us")||suffixMatches(word,"ss")){//if suffix is us or ss
            return word;//return without changing
        }
        if(suffixMatches(word,"s")&&containsVowel(prefix(word," s"))){//check prefix not including end char for vowel
            return replaceSuffix(word,1,"");//replace with nothing
        }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepThree(string &word){//careful of order using longest end that matches first
    if(suffixMatches(word,"eed")){
        if(suffInRegion(word,"eed")>0){
            return replaceSuffix(word,3,"ee");//place with ee
        }
    }
    else if(suffixMatches(word,"eedly")){
        if(suffInRegion(word,"eedly")>0){
            return replaceSuffix(word,3,"");//replace ee
        }
    }
    else if(suffixMatches(word,"ed")){
        if(containsVowel(prefix(word,"ed"))){//check prefix for vowel and ends with ed
            word=replaceSuffix(word,2,"");//remove ed
            return replaceCond(word);//check preceder for conditions
        }
    }
    else if(suffixMatches(word,"edly")){
        if(containsVowel(prefix(word,"edly"))){//check prefix for vowel and ends with edly
            word=replaceSuffix(word,4,"");//remove edly
            return replaceCond(word);//check preceder for conditions
        }
    }
    else if(suffixMatches(word,"ing")){
        if(containsVowel(prefix(word,"ing"))){//check prefix for vowel and ends with ing
            word=replaceSuffix(word,3,"");//remove ing
            return replaceCond(word);//check preceder for conditions
        }
    }
        else if(suffixMatches(word,"ingly")){
            if(containsVowel(prefix(word,"ingly"))){//check prefix for vowel and ends with ingly
                word=replaceSuffix(word,5,"");//remove ingly
                return replaceCond(word);//check preceder for conditions
            }
    }
    return word;   
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepFour(string &word){
    if(suffixMatches(word,"y")){
        string pre = prefix(word, "y");
        if(pre.length()>1){
            if(!isVowel(pre,pre.length()-1)){
                return replaceSuffix(word,1,"i");
            }
        }
    }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepFive(string &word){
    if(suffixMatches(word,"ization")){
        return replaceSuffix(word,7,"ize");
    }
    if(suffixMatches(word,"ational")){
        return replaceSuffix(word,7,"ate");
    }
    if(suffixMatches(word,"fulness")){
        return replaceSuffix(word,7,"ful");
    }
    if(suffixMatches(word,"ousness")){
        return replaceSuffix(word,7,"ous");
    }
    if(suffixMatches(word,"iveness")){
        return replaceSuffix(word,7,"ive");
    }
    if(suffixMatches(word,"tional")){
        return replaceSuffix(word,6,"tion");
    }
    if(suffixMatches(word,"biliti")){
        return replaceSuffix(word,6,"ble");
    }
    if(suffixMatches(word,"lessli")){
        return replaceSuffix(word,6,"less");
    }
    if(suffixMatches(word,"entli")){
        return replaceSuffix(word,5,"ent");
    }
    if(suffixMatches(word,"ation")){
        return replaceSuffix(word,5,"ate");
    }
    if(suffixMatches(word,"alism")){
        return replaceSuffix(word,5,"al");
    }
    if(suffixMatches(word,"aliti")){
        return replaceSuffix(word,5,"al");
    }
    if(suffixMatches(word,"ousli")){
        return replaceSuffix(word,5,"ous");
    }
    if(suffixMatches(word,"iviti")){
        return replaceSuffix(word,5,"ive");
    }
    if(suffixMatches(word,"fulli")){
        return replaceSuffix(word,5,"ful");
    }
    if(suffixMatches(word,"enci")){
        return replaceSuffix(word,4,"ence");
    }
    if(suffixMatches(word,"anci")){
        return replaceSuffix(word,4,"ance");
    }
    if(suffixMatches(word,"abli")){
        return replaceSuffix(word,4,"able");
    }
    if(suffixMatches(word,"izer")){
        return replaceSuffix(word,4,"ize");
    }
    if(suffixMatches(word,"ator")){
        return replaceSuffix(word,4,"ate");
    }
    if(suffixMatches(word,"alli")){
        return replaceSuffix(word,4,"al");
    }
    if(suffixMatches(word,"bli")){
        return replaceSuffix(word,3,"ble");
    }
    if(suffixMatches(word,"ogi")){
        string pre = prefix(word,"ogi");
        if(pre.length()>0&&pre.at(pre.length()-1)=='l'){
        return replaceSuffix(word,3,"og");
        }
    }
    if(suffixMatches(word,"li")){
        return liCond(word);
    }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepSix(string &word){
    if(suffixMatches(word,"ational")){
        if(suffInRegion(word,"ational")>0){
            return replaceSuffix(word,7,"ate");
        }
    }
    else if(suffixMatches(word,"tional")){
        if(suffInRegion(word,"tional")>0){
            return replaceSuffix(word,6,"tion");
        }
    }
    else if(suffixMatches(word,"alize")){
        if(suffInRegion(word,"alize")>0){
            return replaceSuffix(word,5,"al");
        }
    }
    else if(suffixMatches(word,"icate")){
        if(suffInRegion(word,"icate")>0){
            return replaceSuffix(word,5,"ic");
        }
    }
    else if(suffixMatches(word,"iciti")){
        if(suffInRegion(word,"iciti")>0){
            return replaceSuffix(word,5,"ic");
        }
    }
    else if(suffixMatches(word,"ical")){
        if(suffInRegion(word,"ical")>0){
            return replaceSuffix(word,4,"ic");
        }
    }
    else if(suffixMatches(word,"ful")){
        if(suffInRegion(word,"ful")>0){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ness")){
        if(suffInRegion(word,"ness")>0){
            return replaceSuffix(word,4,"");
        }
    }
    else if(suffixMatches(word,"ative")){
        if(suffInRegion(word,"ative")==2){
            return replaceSuffix(word,5,"");
        }
    }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepSeven(string &word){
    if(suffixMatches(word,"al")){
        if(suffInRegion(word,"al")==2){
            return replaceSuffix(word,2,"");
        }
    }
    else if(suffixMatches(word,"ance")){
        if(suffInRegion(word,"ance")==2){
            return replaceSuffix(word,4,"");
        }
    }
    else if(suffixMatches(word,"ence")){
        if(suffInRegion(word,"ence")==2){
            return replaceSuffix(word,4,"");
        }
    }
    else if(suffixMatches(word,"er")){
        if(suffInRegion(word,"er")==2){
            return replaceSuffix(word,2,"");
        }
    }
    else if(suffixMatches(word,"ic")){
        if(suffInRegion(word,"ic")==2){
            return replaceSuffix(word,2,"");
        }
    }
    else if(suffixMatches(word,"able")){
        if(suffInRegion(word,"able")==2){
            return replaceSuffix(word,4,"");
        }
    }
    else if(suffixMatches(word,"ible")){
        if(suffInRegion(word,"ible")==2){
            return replaceSuffix(word,4,"");
        }
    }
    else if(suffixMatches(word,"ant")){
        if(suffInRegion(word,"ant")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ement")){
        if(suffInRegion(word,"ement")==2){
            return replaceSuffix(word,5,"");
        }
    }
    else if(suffixMatches(word,"ment")){
        if(suffInRegion(word,"ment")==2){
            return replaceSuffix(word,4,"");
        }
    }
    else if(suffixMatches(word,"ent")){
        if(suffInRegion(word,"ent")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ism")){
        if(suffInRegion(word,"ism")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ate")){
        if(suffInRegion(word,"ate")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"iti")){
        if(suffInRegion(word,"iti")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ous")){
        if(suffInRegion(word,"ous")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ive")){
        if(suffInRegion(word,"ive")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ize")){
        if(suffInRegion(word,"ize")==2){
            return replaceSuffix(word,3,"");
        }
    }
    else if(suffixMatches(word,"ion")){
        if(suffInRegion(word,"ion")==2){
            if(word.length()>3){
                if(word.at(word.length()-4)=='s'||word.at(word.length()-4)=='t'){
                    return replaceSuffix(word,3,"");
                }
            }
        }
    }
    return word;
}
/**
 * Checks for certain conditions in the word and edits accordingly
 * @param word the string to check
 * @return returns edited word if conditions match, if not returns word back
 */
string Seed::stepEight(string &word){
    if(suffixMatches(word,"e")){
        if(suffInRegion(word,"e")==2||(suffInRegion(word,"e")>0&&!isShortSyll(prefix(word,"e")))){
            return replaceSuffix(word,1,"");
        }
    }
    if(suffixMatches(word,"l")){
        if(suffInRegion(word,"l")==2){
            if(word.at(word.length()-2)=='l'){
                return replaceSuffix(word,1,"");
            }
        }
    }
    return word;
}
/**
 * Converts a word into it's stem(reading becomes read, darkness becomes dark)
 * @return the word after it has been stemmed correctly
 */
string Seed::convertToSeed(){
    seed=stepOne(seed);
    seed=stepTwo(seed);
    seed=stepThree(seed);
    seed=stepFour(seed);
    seed=stepFive(seed);
    seed=stepSix(seed);
    seed=stepSeven(seed);
    seed=stepEight(seed);
    
return seed;
}


