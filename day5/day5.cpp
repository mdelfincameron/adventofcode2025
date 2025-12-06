#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <algorithm>

using namespace std;

bool comparePair(const pair<int64_t,int64_t>& a, const pair<int64_t,int64_t>& b) {
    return a.first < b.first;
}

int main(){
    string filename;
    fstream file;
    vector<pair<int64_t,int64_t>> ranges;
    int sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        while(getline(file,line)){

            if(line.empty()) break;

            int64_t low, high;
            size_t delimiter = line.find('-');

            low = stoll(line.substr(0, delimiter));
            high = stoll(line.substr(delimiter + 1));

            ranges.push_back(make_pair(low, high));
        }

        std::sort(ranges.begin(), ranges.end(), comparePair);

        while(getline(file,line)){
            int64_t num = stoll(line);

            for(auto range : ranges){
                if(num >= range.first && num <= range.second){
                    sum++;
                    break;
                }
            }
        }

    }

    file.close();

    cout << sum << endl;

    exit(0);
}