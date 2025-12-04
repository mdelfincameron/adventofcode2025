#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <math.h>
#include <algorithm>

using namespace std;

int main(){
    string filename;
    fstream file;
    int64_t sum = 0;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        while(getline(file,line)){

            vector<int> maxes(12, 9); 
            size_t pos = 0;
            
            for(size_t i = 0; i < maxes.size(); i++){
                int max = maxes[i]; 
                string substr = line.substr(pos, line.size() - (11 - i) - pos);
                //cout << substr << endl;
                vector<char> temp(substr.begin(), substr.end());
                auto it = std::max_element(temp.begin(), temp.end());
                maxes[i] = *it - '0';
                pos += std::distance(temp.begin(), it + 1);
                //cout << "Found digit " << maxes[i] << " for position " << i << " at string position " << pos << endl;
            }

            for(size_t i = 0; i < maxes.size(); i++){
                sum += maxes[i] * pow(10, maxes.size() - i - 1);
                //cout << maxes[i] << " ";
            }
            //cout << endl;
        }

    }

    file.close();

    cout << sum << endl;

    exit(0);
}