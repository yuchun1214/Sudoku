// The function members contents of DS


#ifndef __DS_CPP__
#define __DS_CPP__
#include "DS.hpp"

using namespace DS;


template<class T>
T deque<T>::pop_front(){
    if(vector<T>::size() > 0){
        T object = *(vector<T>::begin());
        vector<T>::erase(vector<T>::begin());
        return object;
    }
    else throw "pop_front raise exception: There has no elements in deque object to pop_front";
}

template<class T>
T deque<T>::pop_back(){
    if(vector<T>::size() > 0){
        T object = *(vector<T>::end()-1);
        vector<T>::pop_back();
        return object;
    }
    else throw "pop_back raise exception: There has no elements in deque object to pop_back";
}

template<class T>
void deque<T>::push_back(const T & object){
    vector<T>::push_back(object);
}


template<class T>
void deque<T>::push_front(const T & object){
    vector<T>::insert(vector<T>::begin(),object);
}

template<class T>
T deque<T>::operator=(T & object){
    (*this).clear();
    vector<T>::operator=(object);
}

template <class T>
void deque<T>::pop_front(unsigned int num) {
    if(num > vector<T>::size()){
        out_of_range e(to_string(num) + " is larger than its size");
        throw e;
    }
    vector<T>::erase(vector<T>::begin() , vector<T>::begin() + num);
}

template <class T>
void deque<T>::pop_back(unsigned int num) {
    if(num > vector<T>::size()){
        out_of_range s(to_string(num) + " is larger than its size");
        throw s;
    }
    vector<T>::erase(vector<T>::end() - num, vector<T>::end());
}


template <class T>
deque<T> deque<T>::operator+=(deque<T> &obj) {
    for(int i = 0; i < obj.size(); i++){
        push_back(obj[i]);
    }
    return  *this;
}

template <class T>
deque<T> deque<T>::operator+(deque<T> &obj) {
    deque<T> temp = *this;
    for(int i = 0 ; i < obj.size(); i++){
        temp.push_back(obj[i]);
    }
    return  temp;
}




// DS::String

String::String(const char chr):string(1,chr){

}

String::String():string(){

}

String::String(int i):string(to_string(i)){
    
}

String::String(string &ns):string(ns){

}

String::String(const char * str):string(str){

}

String::String(size_t n, char c):string(n,c){

}

String::String(const string & str, size_t pos, size_t len):string(str,pos,len){

}


String::String(const String & ns):string(ns.c_str()){

}

String String::operator=(const char * s){
    string::operator=(s);
    return *this;
}

String String::operator=(const string& str){
    string::operator=(str);
    return *this;
}


String String::operator=(const char chr){
    string::operator=(chr);
    return *this;
}

int String::operator==(const char * s){
    return !strcmp(this->c_str(),s);
}

int String::operator==(const string& str){
    return !strcmp(this->c_str(), str.c_str());
}

int String::operator==(const String & str){
    return !strcmp(this->c_str(), str.c_str());
}

int String::operator==(const char chr){
    String s = chr;
    return !strcmp(this->c_str(),s.c_str());
}

String String::operator*(unsigned int num){
    String s;
    for(int i = 0; i < num; i++){
        s+=(*this);
    }
    return s;
}

String String::operator*=(unsigned int num) {
    String s;
    for(int i = 0; i < num; i++){
        s+=*this;
    }
    *this = s;
    return s;
}

string String::sData(){
    string s = c_str();
    return s;
}

// Split String
deque<String> String::split(const char * sub){
    deque<String> tokens;

    String token = sub;
    String s = *this;
    String substring;
    int tlength = s.length();
    int started_pos = 0;
    int fpos;// find pos
    fpos = s.find(sub);
    while(fpos != s.npos){
        substring = s.substr(started_pos, fpos);
        tokens.push_back(substring);
        started_pos += substring.length() + token.length();
        s = s.substr(started_pos,s.length());
        s.find(sub);
        started_pos = 0;
        fpos = s.find(sub);
    }
    tokens.push_back(s);
    return tokens;
}


#endif



// DS's unit test : 
// #define __DS_UNIT_TEST__
#ifdef __DS_UNIT_TEST__
int main(){

    // Test deque
    // deque<int> di;
    // for(int i = 0; i < 10; i++){
    //     di.push_back(i);
    // }

    // di.pop_front();
    // for(int i = 0; i < di.size(); i++){
    //     cout<<di[i]<<endl;
    // }
    cout<<"------------------------------"<<endl;
    cout<<"==========Round 2============="<<endl;

    vector<String> ds;
    // String temp = "Temp1";
    
    String temp("Fuck You man");
    String temp2('5');
    temp = temp2;
    ds.push_back(temp);
    // ds.push_back(temp);
    ds.push_back(temp2);
    ds.erase(ds.begin());

    


    // Test String
    String str = "This is ";
    String str2 = str;
    str = "10";
    // str2.append("1010");
    cout<<(str == str)<<endl;
    cout<<stoi(str)<<endl;

    // conversion:
    cout<<"Conversion"<<endl;
    string s("This is string");
    String S = s;
    cout<<S<<endl;

    // substring
    cout<<"Substring"<<endl;
    String sstr = "This is my house";
    cout<<"sstr.find(\"is\")"<<sstr.find("is")<<endl;
    cout<<"sstr.sub(sstr.find(\"is\") + 2, sstr.length())"<<sstr.substr(sstr.find("is") + 2, sstr.length())<<endl;

    cout<<"sstr.find('no')"<<sstr.find("no")<<endl;
    cout<<"sstr.find('no') == string::npos ? "<< ((sstr.find("no") == sstr.npos )? "True" : "False")<<endl;

    // test split
    cout<<"---------------------------"<<endl;
    cout<<"Test split"<<endl;
    deque<String> stringsplit;
    stringsplit = sstr.split("is");
    for(int i = 0, length = stringsplit.size();i < length; i++){
        cout<<"'"<<stringsplit[i]<<"'"<<endl;
    }
    cout<<"\nTest Split part 2"<<endl;
    cout<<"---------------------------"<<endl;
    sstr = "I am very proud of being a Taiwanese. I was born and grow in Taiwan. Taiwan is a country not part of bull shit China";
    cout<<sstr<<endl;
    // stringsplit.clear();
    stringsplit = sstr.split("I");
    for(int i = 0, length = stringsplit.size();i < length; i++){
        cout<<"'"<<stringsplit[i]<<"'"<<endl;
    }
}

#endif