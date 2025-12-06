#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>
#include <regex>

using namespace std;

vector<int64_t> extractNums(const string& line) {
    vector<int64_t> nums;

    stringstream ss(line);

    string temp;

    while (ss >> temp) {
        nums.push_back(stoll(temp));
    }
    
    return nums;
}

vector<char> extractOps(const string& line) {
    vector<char> ops;

    stringstream ss(line);

    string temp;

    while (ss >> temp) {
        ops.push_back(temp[0]);
    }

    return ops;
}

int main(){
    string filename;
    fstream file;
    vector<vector<int64_t>> nums;
    vector<char> ops;
    regex digit("\\d+");
    int64_t sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        while(getline(file,line)){
            smatch m;
            if(regex_search(line,m,digit)){
                nums.push_back(extractNums(line));
            } else {
                ops = extractOps(line);
            }
        }

    }

    file.close();

    for(size_t i = 0; i < ops.size(); i++){
        int64_t result;
        if(ops[i] == '+'){
            result = 0;
            for(auto numSet : nums){
                result += numSet[i];
            }
        } 
        else{
            result = 1;
             for(auto numSet : nums){
                result *= numSet[i];
            }
        }
        sum += result;
    }

    cout << sum << endl;

    exit(0);
}