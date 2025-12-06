#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <algorithm>

using namespace std;

bool comparePair(const pair<intmax_t,intmax_t>& a, const pair<intmax_t,intmax_t>& b) {
    return a.first < b.first;
}

int main(){
    string filename;
    fstream file;
    vector<pair<intmax_t,intmax_t>> ranges;
    intmax_t sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        while(getline(file,line)){

            if(line.empty()) break;

            intmax_t low, high;
            size_t delimiter = line.find('-');

            low = stoll(line.substr(0, delimiter));
            high = stoll(line.substr(delimiter + 1));

            ranges.push_back(make_pair(low, high));
        }

    }

    file.close();

    std::sort(ranges.begin(), ranges.end(), comparePair);

    for(size_t i = 0; i < ranges.size() - 1; i++){
        if(ranges[i + 1].first <= ranges[i].second){
            ranges[i].second = max(ranges[i].second, ranges[i + 1].second);
            ranges.erase(ranges.begin() + i + 1);
            i--;
        }

        //cout << ranges[i].first << "-" << ranges[i].second << endl;
    }

    for(auto range : ranges){
        sum += range.second - range.first + 1;
    }

    cout << sum << endl;

    exit(0);
}