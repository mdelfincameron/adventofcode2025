#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

int main(){
    string filename;
    fstream file;
    int64_t sum = 0;
    vector<int64_t> timelineCount;

    //Get filename, open file
    cout << "Please input filename: ";
    cin >> filename;

    file.open(filename,ios::in);

    if(file.is_open()){

        string line;

        getline(file,line);
        timelineCount.resize(line.size(), 0);
        timelineCount[line.find('S')]++;

        while(getline(file,line)){
            size_t splitter = line.find('^');
            while(splitter != string::npos){
                if(timelineCount[splitter]){
                    timelineCount[splitter - 1] += timelineCount[splitter];
                    timelineCount[splitter + 1] += timelineCount[splitter];
                    timelineCount[splitter] = 0;
                }
                splitter = line.find('^', splitter + 1);
            }
            //cout << timelineCount << endl;

        }

    }

    file.close();

    for(auto timeline : timelineCount){
        sum += timeline;
    }

    cout << sum << endl;

    exit(0);
}