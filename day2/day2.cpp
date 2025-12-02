#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

bool isInvalid(int64_t num){
    string s = to_string(num);
    int length = s.size();
    if(length % 2 != 0){
        return false;
    }
    for(int i = 0, j = length/2; i < length/2; i++, j++){
        if(s[i] != s[j]){
            return false;
        }
    }
    return true;
}

int main(){
    string filename;
    fstream file;
    vector<pair<int64_t,int64_t>> ranges;
    int64_t sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        //Read line by line through file
        string line;

        while(getline(file,line,',')){
            int64_t first = stoll(line.substr(0,line.find('-')));
            int64_t second = stoll(line.substr(line.find('-')+1));
            ranges.push_back(make_pair(first, second));
        }

        for(auto p : ranges){
            for(int64_t i = p.first; i <= p.second; i++){
                //cout << "Checking " << i << endl;
                //cout << s.substr(0, s.size()/2) << ":" << s.substr(s.size()/2) << endl;
                if(isInvalid(i)){
                    sum += i;
                }
            }
        }
    }

    file.close();

    /*
    for(auto p : ranges){
        cout << p.first << "-" << p.second << endl;
    }
    */

    cout << sum << endl;

    exit(0);
}