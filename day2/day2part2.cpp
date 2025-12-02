#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

bool isInvalid(string num, int div){
    int length = num.size();
    if(length % div != 0){
        return false;
    }
    for(int i = 0; i < length/div; i++){
        for(int j = i; j < length; j += length/div){
            if(num[i] != num[j]){
                return false;
            }
        }
    }
    //cout << "Found invalid number: " << num << " with division " << div << endl;
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

        string line;

        while(getline(file,line,',')){
            int64_t first = stoll(line.substr(0,line.find('-')));
            int64_t second = stoll(line.substr(line.find('-')+1));
            ranges.push_back(make_pair(first, second));
        }

        //Bruteforce check every integer in ranges, every possible subdivision of integer as well
        for(auto p : ranges){
            for(int64_t i = p.first; i <= p.second; i++){
                //cout << "Checking " << i << endl;
                string s = to_string(i);
                for(int n = 2; n <= s.size(); n++){    
                    if(isInvalid(s, n)){
                        sum += i;
                        break;
                    }
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