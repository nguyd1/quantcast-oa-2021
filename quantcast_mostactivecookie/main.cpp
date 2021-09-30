#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

void printError(string);

int main(int argc, const char* argv[]){
    // parse cookie log file
    // format cookie,timestamp
    // parse each line.substr(0,line.find(',')) for cookie
    // parse each line.substr(line.find(',')+1,10) for date
    // put into map if date matches with string cookie as key and count as value
    // highest count is output to console

    // cmd error checking
    // cmd must be ./a.out filename.csv -d yyyy-mm-dd
    if(argc!=4) 
        printError("cmd");

    // input file error checking
    // input file must exist in working directory
    ifstream inFile;
    inFile.open(argv[1]);
    if(!inFile.is_open()) 
        printError("file");

    // date error checking
    // date must be yyyy-mm-dd
    string date=argv[3];
    if(date.size()!=10)
        printError("date");
    if(date[4]!='-' || date[7]!='-')
        printError("date");
    for(int i=0;i<date.size();i++){
        if(i==4 || i==7) 
            continue;
        if(!isdigit(date[i])) 
            printError("date");
    }

    // parse each line in input file
    // if date matches, put cookie into map and count its freq
    string line;
    unordered_map<string,int> cookieCount;
    while(getline(inFile,line)){
        if(line.substr(line.find(',')+1,10)==date){
            string cookie=line.substr(0,line.find(','));
            cookieCount[cookie]++;
        }
    }

    // gets the highest occuring cookie in the map
    int highestCookieCount=0;
    string highestCookie;
    for(auto& cookie:cookieCount){
        if(highestCookieCount<cookie.second){
            highestCookieCount=cookie.second;
            highestCookie=cookie.first;
        }
    }

    // outputs all cookies in map that have the same count as the highest
    for(auto& cookie:cookieCount){
        if(highestCookieCount==cookie.second)
            cout<<cookie.first<<endl;
    }

    return 0;
}

void printError(string errorType){
    if(errorType=="cmd")
        cout<<"Invalid command line prompt. Usage: ./a.out filename.csv -d yyyy-mm-dd"<<endl;
    else if(errorType=="file")
        cout<<"Could not open file."<<endl;
    else
        cout<<"Date is invalid"<<endl;

    exit(0);
}